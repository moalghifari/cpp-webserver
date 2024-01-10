#pragma once

#include <string>
#include <boost/asio.hpp>
#include <boost/beast/http.hpp>
#include "http_request.h"
#include <tuple>

namespace Handlers {
    std::tuple<std::string, std::string> handleHello(const HttpRequest& httpRequest);
    std::tuple<std::string, std::string> handleHi(const HttpRequest& httpRequest);
    std::tuple<std::string, std::string> handleTest(const HttpRequest& httpRequest);
    std::tuple<std::string, std::string> handleJson(const HttpRequest& httpRequest);
    std::tuple<std::string, std::string> handleRoot(const HttpRequest& httpRequest);
}
