#pragma once

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <memory>
#include "connection.h"

class HttpServer {
public:
    HttpServer(boost::asio::io_service& io_service, short port);

private:
    void startAccept();

    void handleAccept(const std::shared_ptr<Connection>& newConnection, const boost::system::error_code& error);

    boost::asio::io_service& io_service_;
    boost::asio::ip::tcp::acceptor acceptor_;
};
