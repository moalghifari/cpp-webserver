#include "connection.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include "http_request.h"
#include "handlers.h"

Connection::Pointer Connection::create(boost::asio::io_service& io_service) {
    return Pointer(new Connection(io_service));
}

Connection::Connection(boost::asio::io_service& io_service) : socket_(io_service) {
    routeHandlers["/hello"] = &Handlers::handleHello;
    routeHandlers["/hi"] = &Handlers::handleHi;
    routeHandlers["/test"] = &Handlers::handleTest;
    routeHandlers["/json"] = &Handlers::handleJson;
    routeHandlers["/"] = &Handlers::handleRoot;
}

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
        HttpRequestParser httpRequestParser;
        HttpRequest httpRequest = httpRequestParser.parse(request);
        std::string response;
        auto it = routeHandlers.find(httpRequest.path);
        if (it != routeHandlers.end()) {
            auto [status, response] = it->second(httpRequest);
            sendResponse(status, response);
        } else {
            sendResponse("404 Not Found", "Not Found");
        }
    }
}

void Connection::handleWrite(const boost::system::error_code& error, std::size_t) {
    socket_.close();
}

void Connection::sendResponse(const std::string& status, const std::string& responseBody) {
    std::string response = "HTTP/1.1 " + status + "\r\nContent-Type: application/json\r\nContent-Length: " +
                            std::to_string(responseBody.length()) + "\r\n\r\n" + responseBody;
    boost::asio::async_write(socket_, boost::asio::buffer(response),
                                boost::bind(&Connection::handleWrite, shared_from_this(),
                                            boost::asio::placeholders::error,
                                            boost::asio::placeholders::bytes_transferred));
}