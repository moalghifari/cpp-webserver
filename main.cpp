#include <iostream>
#include "server.h"

int main() {
    try {
        boost::asio::io_service io_service;
        HttpServer server(io_service, 7717);

        std::cout << "Server is running on port 7717..." << std::endl;

        io_service.run();
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
