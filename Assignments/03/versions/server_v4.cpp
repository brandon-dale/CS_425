/*
 * v04 - Multiple Producers, Single Consumer, No Async
*/

#include <iostream>
#include <semaphore>
#include <mutex>
#include <thread>
#include <atomic>

#include "Connection.h"
#include "HTTPRequest.h"
#include "HTTPResponse.h"


const uint16_t DefaultPort = 8136; 


/*
 * Class holds a ring buffer for producer consumer model
 */
template <typename Data, ptrdiff_t MaxDataSlots = 8>
class RingBuffer {

    std::vector<Data> buffer;
        
    using size_type = std::vector<Data>::size_type;

    struct Index : std::atomic<size_type> {
        Index(auto i) {
            this->store(i);
        }

        void operator ++ () {
            auto v = this->load();
            ++v %= MaxDataSlots;
            this->store(v);
        }
    };

    Index nextStorable = 0;
    Index nextReadable = 0;

    std::counting_semaphore<MaxDataSlots> storable{MaxDataSlots};
    std::counting_semaphore<MaxDataSlots> readable{0};

    std::mutex storedMutex;
    std::mutex readMutex;

public:
    // RingBuffer(size_t count = MaxDataSlots) : std::vector<Data>(count, 0) { 
        
    // }
    RingBuffer() { 
        auto count = MaxDataSlots;
        buffer = std::vector<Data>(count, -1);
    }

    void store(const Data& t) {
        storable.acquire();
        {
            std::lock_guard{storedMutex};
            this->buffer.at(nextStorable) = t;
            //this->assign(nextStorable, t);
            ++nextStorable;
        }
        readable.release();
    }

    Data read() {
        Data t;
        readable.acquire();
        {
            std::lock_guard{readMutex};
            //t = this->at(nextReadable);
            t = this->buffer.at(nextReadable);
            ++nextReadable;
        }
        storable.release();
        return t;
    }
};


int main(int argc, char* argv[]) {
    uint16_t port = argc > 1 ? std::stol(argv[1]) : DefaultPort;

    // Print out a banner message
    std::cout << "SERVER RUNNING\n";

    // Setup Ring Buffer
    RingBuffer<int, 200> ringBuffer;

    Connection connection(port);

    // Specify Number of Producers and Consumers
    size_t NUM_PRODUCERS = 2;
    size_t NUM_CONSUMERS = 1;

    // Create producers
    for (auto prodId = 0; prodId < NUM_PRODUCERS; ++prodId) {
        std::jthread{[&]() {
            while (connection) {
                auto client = connection.accept();
                ringBuffer.store(client);
            }
        }}.detach();
    }

    std::cout << std::endl;
    
    // Create Consumer
    for (auto consId = 0; consId < NUM_CONSUMERS; ++consId) {
        std::jthread{[&]() {
            while (connection) {
                auto client = ringBuffer.read();
                Session session(client);
                std::string msg;
                session >> msg;
                HTTPRequest request(msg);
                const char* root = "/home/faculty/shreiner/public_html/03";
                HTTPResponse response(request, root);
                session << response;
            }
        }};
    }
    
}
