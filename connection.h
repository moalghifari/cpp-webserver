#pragma once

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <memory>
#include "http_request.h"
#include <map>
#include <tuple>

class Connection : public std::enable_shared_from_this<Connection> {
public:
    typedef std::shared_ptr<Connection> Pointer;

    static Pointer create(boost::asio::io_service& io_service);

    boost::asio::ip::tcp::socket& socket();

    void start();

private:
    Connection(boost::asio::io_service& io_service);

    void handleRead(const boost::system::error_code& error, std::size_t bytesTransferred);

    void handleWrite(const boost::system::error_code& error, std::size_t /* bytesTransferred */);

    void sendResponse(const std::string& status, const std::string& responseBody);

    std::map<std::string, std::function<std::tuple<std::string, std::string>(const HttpRequest&)>> routeHandlers;
    boost::asio::ip::tcp::socket socket_;
    boost::asio::streambuf buffer_;
};
