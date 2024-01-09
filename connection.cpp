#include "connection.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include "http_request.h"

Connection::Pointer Connection::create(boost::asio::io_service& io_service) {
    return Pointer(new Connection(io_service));
}

Connection::Connection(boost::asio::io_service& io_service)
    : socket_(io_service) {}

boost::asio::ip::tcp::socket& Connection::socket() {
    return socket_;
}

void Connection::start() {
    boost::asio::async_read_until(socket_, buffer_, "\r\n\r\n",
                                  boost::bind(&Connection::handleRead, shared_from_this(),
                                              boost::asio::placeholders::error,
                                              boost::asio::placeholders::bytes_transferred));
}

void Connection::handleRead(const boost::system::error_code& error, std::size_t bytesTransferred) {
    if (!error) {
        std::istream request_stream(&buffer_);
        std::string request;
        request.resize(bytesTransferred);
        request_stream.read(&request[0], static_cast<std::streamsize>(bytesTransferred));

        std::map<std::string, std::string> responseMap = {
            {"/hello", "Hello World!"},
            {"/hi", "Hi World!"},
            {"/test", "Test"},
            {"/", "C++ Webserver"} 
        };

        HttpRequest httpRequest;
        HttpRequestParser httpRequestParser;
        httpRequest = httpRequestParser.parse(request);

        std::string response;
        auto it = responseMap.find(httpRequest.path);
        if (it != responseMap.end()) {
            std::string text = it->second;
            response = "HTTP/1.1 200 OK\r\nContent-Length: " + std::to_string(text.length()) + "\r\n\r\n" + text;
        } else {
            response = "HTTP/1.1 404 Not Found\r\nContent-Length: 9\r\n\r\nNot Found";
        }

        boost::asio::async_write(socket_, boost::asio::buffer(response),
                                 boost::bind(&Connection::handleWrite, shared_from_this(),
                                             boost::asio::placeholders::error,
                                             boost::asio::placeholders::bytes_transferred));
    }
}

void Connection::handleWrite(const boost::system::error_code& error, std::size_t /* bytesTransferred */) {
    // Close the connection after writing the response
    socket_.close();
}
