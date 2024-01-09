#pragma once

#include <string>
#include <unordered_map>

class HttpRequest {
public:
    std::string method;
    std::string path;
    std::unordered_map<std::string, std::string> headers;
    std::string body;
};

class HttpRequestParser {
public:
    static HttpRequest parse(const std::string& rawRequest);
};
