#include "http_request.h"
#include <sstream>

HttpRequest HttpRequestParser::parse(const std::string& rawRequest) {
    HttpRequest request;

    // Split the request into lines
    std::istringstream requestStream(rawRequest);
    std::string line;
    std::getline(requestStream, line);  // First line contains method, path, and HTTP version
    std::istringstream firstLineStream(line);
    firstLineStream >> request.method >> request.path;

    // Parse headers
    while (std::getline(requestStream, line) && !line.empty()) {
        size_t separatorPos = line.find(":");
        if (separatorPos != std::string::npos) {
            std::string key = line.substr(0, separatorPos);
            std::string value = line.substr(separatorPos + 2); // Skip ": "
            request.headers[key] = value;
        }
    }

    // Parse body
    std::getline(requestStream, request.body, '\0');

    return request;
}
