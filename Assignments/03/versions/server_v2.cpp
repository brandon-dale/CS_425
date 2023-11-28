/*
 * v02 - Basic Threading
 * Truly awful, mostly for fun
*/

#include <iostream>
#include <thread>

#include "Connection.h"
#include "HTTPRequest.h"
#include "HTTPResponse.h"


const uint16_t DefaultPort = 8136; 

int main(int argc, char* argv[]) {
    uint16_t port = argc > 1 ? std::stol(argv[1]) : DefaultPort;

    Connection connection(port);

    while (connection) {

        int clinet = connection.accept();

        std::thread t{ [=]() {
            Session session(clinet);
            std::string msg;
            session >> msg;
            HTTPRequest request(msg);
            const char* root = "/home/faculty/shreiner/public_html/03";
            HTTPResponse response(request, root);
            session << response;
        }};

        t.detach();
    }
}
