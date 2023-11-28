/*
 * Version 5 - Basic Async
 */

#include <iostream>
#include <future>

#include "Connection.h"
#include "HTTPRequest.h"
#include "HTTPResponse.h"

const uint16_t DefaultPort = 8136; 

int main(int argc, char* argv[]) {
    uint16_t port = argc > 1 ? std::stol(argv[1]) : DefaultPort;

    std::cout << "SERVER RUNNING\n";

    Connection connection(port);

    while (connection) {

        int client = connection.accept();

        auto future = std::async(std::launch::async, [&]() {
            Session session(client);
            std::string msg;
            session >> msg;
            HTTPRequest request(msg);
            const char* root = "/home/faculty/shreiner/public_html/03";
            HTTPResponse response(request, root);
            session << response;
        });
    }
}
