#include "server.h"
#include "connection.h"

HttpServer::HttpServer(boost::asio::io_service& io_service, short port)
    : io_service_(io_service), acceptor_(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port), true) {
    startAccept();
}

void HttpServer::startAccept() {
    auto newConnection = Connection::create(io_service_);
    acceptor_.async_accept(newConnection->socket(),
                           boost::bind(&HttpServer::handleAccept, this, newConnection,
                                       boost::asio::placeholders::error));
}

void HttpServer::handleAccept(const std::shared_ptr<Connection>& newConnection, const boost::system::error_code& error) {
    if (!error) {
        newConnection->start();
    }

    startAccept();
}
