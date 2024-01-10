#include "http_request.h"
#include <sstream>
#include <iostream>

HttpRequest HttpRequestParser::parse(const std::string& rawRequest) {
    HttpRequest request;

    std::istringstream requestStream(rawRequest);
    std::string line;
    std::getline(requestStream, line); 
    std::istringstream firstLineStream(line);
    firstLineStream >> request.method >> request.path;

    while (std::getline(requestStream, line) && !line.empty()) {
        size_t separatorPos = line.find(":");
        if (line.length() == 1) {
            break;
        }
        if (separatorPos != std::string::npos) {
            std::string key = line.substr(0, separatorPos);
            std::string value = line.substr(separatorPos + 2); // Skip ": "
            request.headers[key] = value;
        }
    }
    std::getline(requestStream, request.body, '\0');
    return request;
}
