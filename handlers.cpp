#include "handlers.h"
#include <boost/beast/http.hpp>

namespace Handlers {
    std::tuple<std::string, std::string> handleHello(const HttpRequest& httpRequest) {
        std::tuple<std::string, std::string> result;
        std::get<0>(result) = "200 OK";
        std::get<1>(result) = "Hello World!";
        return result;
    }

    std::tuple<std::string, std::string> handleHi(const HttpRequest& httpRequest) {
        std::tuple<std::string, std::string> result;
        std::get<0>(result) = "200 OK";
        std::get<1>(result) = "Hi World!";
        return result;
    }

    std::tuple<std::string, std::string> handleTest(const HttpRequest& httpRequest) {
        std::tuple<std::string, std::string> result;
        std::get<0>(result) = "200 OK";
        std::get<1>(result) = "Test";
        return result;
    }

    std::tuple<std::string, std::string> handleJson(const HttpRequest& httpRequest) {
        std::tuple<std::string, std::string> result;
        std::get<0>(result) = "200 OK";
        std::get<1>(result) = "{\"code\":0,\"msg\":\"success\"}";
        return result;
    }

    std::tuple<std::string, std::string> handleRoot(const HttpRequest& httpRequest) {
        std::tuple<std::string, std::string> result;
        std::get<0>(result) = "200 OK";
        std::get<1>(result) = "C++ Webserver";
        return result;
    }
}
