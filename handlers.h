#pragma once

#include <string>
#include <boost/asio.hpp>
#include <boost/beast/http.hpp>
#include "http_request.h"
#include <tuple>

namespace Handlers {
    std::tuple<std::string, std::string> handleCreateBook(const HttpRequest& httpRequest);
    std::tuple<std::string, std::string> handleReadBooks(const HttpRequest& httpRequest);
    std::tuple<std::string, std::string> handleReadBook(const HttpRequest& httpRequest);
    std::tuple<std::string, std::string> handleUpdateBook(const HttpRequest& httpRequest);
    std::tuple<std::string, std::string> handleDeleteBook(const HttpRequest& httpRequest);

    std::string createBook(const std::string& requestBody);
    std::string readBooks();
    std::string readBook(const std::string& bookId);
    std::string updateBook(const std::string& bookId, const std::string& requestBody);
    std::string deleteBook(const std::string& bookId);

    std::tuple<std::string, std::string> handleHello(const HttpRequest& httpRequest);
    std::tuple<std::string, std::string> handleHi(const HttpRequest& httpRequest);
    std::tuple<std::string, std::string> handleTest(const HttpRequest& httpRequest);
    std::tuple<std::string, std::string> handleJson(const HttpRequest& httpRequest);
    std::tuple<std::string, std::string> handleRoot(const HttpRequest& httpRequest);
}
