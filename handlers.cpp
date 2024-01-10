#include "handlers.h"
#include <boost/beast/http.hpp>
#include "libs/nlohmann/json.hpp"
#include <iostream>

namespace Handlers {

    using json = nlohmann::json;

    struct Book {
        std::string id;
        std::string title;
        std::string author;
    };

    std::vector<Book> bookDatabase;

    std::tuple<std::string, std::string> handleCreateBook(const HttpRequest& httpRequest) {
        std::string requestBody(httpRequest.body.begin(), httpRequest.body.end());
        std::string response = createBook(requestBody);
        std::tuple<std::string, std::string> result;
        std::get<0>(result) = "200 OK";
        std::get<1>(result) = response;
        return result;
    }

    std::tuple<std::string, std::string> handleReadBooks(const HttpRequest& httpRequest) {
        std::string response = readBooks();
        std::tuple<std::string, std::string> result;
        std::get<0>(result) = "200 OK";
        std::get<1>(result) = response;
        return result;
    }

    std::tuple<std::string, std::string> handleReadBook(const HttpRequest& httpRequest) {
        std::string bookId = httpRequest.path.substr(6); 
        std::string response = readBook(bookId);
        std::tuple<std::string, std::string> result;
        std::get<0>(result) = "200 OK";
        std::get<1>(result) = response;
        return result;
    }

    std::tuple<std::string, std::string> handleUpdateBook(const HttpRequest& httpRequest) {
        std::string requestBody(httpRequest.body.begin(), httpRequest.body.end());
        std::string response = updateBook(requestBody);
        std::tuple<std::string, std::string> result;
        std::get<0>(result) = "200 OK";
        std::get<1>(result) = response;
        return result;
    }

    std::tuple<std::string, std::string> handleDeleteBook(const HttpRequest& httpRequest) {
        std::string bookId = httpRequest.path.substr(6); 
        std::string response = deleteBook(bookId);
        std::tuple<std::string, std::string> result;
        std::get<0>(result) = "200 OK";
        std::get<1>(result) = response;
        return result;
    }

    std::string createBook(const std::string& requestBody) {
        try {
            auto jsonBody = json::parse(requestBody);
            Book newBook{
                jsonBody["id"].get<std::string>(),
                jsonBody["title"].get<std::string>(),
                jsonBody["author"].get<std::string>()
            };
            bookDatabase.push_back(newBook);
            return "{\"code\": 0, \"msg\": \"Book created successfully\"}";
        } catch (const std::exception& e) {
            return "{\"code\": 1, \"msg\": \"Error creating book\", \"error\": \"" + std::string(e.what()) + "\" + \"requestBody\": \"" + requestBody + "\"}";
        }
    }

    std::string readBooks() {
        json responseArray;
        for (const auto& book : bookDatabase) {
            responseArray.push_back({
                {"id", book.id},
                {"title", book.title},
                {"author", book.author}
            });
        }
        return responseArray.dump();
    }

    std::string readBook(const std::string& bookId) {
        auto it = std::find_if(bookDatabase.begin(), bookDatabase.end(),
                               [bookId](const Book& book) { return book.id == bookId; });
        if (it != bookDatabase.end()) {
            json responseObject = {
                {"id", it->id},
                {"title", it->title},
                {"author", it->author}
            };
            return responseObject.dump();
        } else {
            return "{\"code\": 1, \"msg\": \"Book not found\"}";
        }
    }

    std::string updateBook(const std::string& requestBody) {
        auto jsonBody = json::parse(requestBody);
        std::string bookId = jsonBody["id"].get<std::string>();
        auto it = std::find_if(bookDatabase.begin(), bookDatabase.end(),
                               [bookId](const Book& book) { return book.id == bookId; });

        if (it != bookDatabase.end()) {
            try {
                it->title = jsonBody["title"].get<std::string>();
                it->author = jsonBody["author"].get<std::string>();
                return "{\"code\": 0, \"msg\": \"Book updated successfully\"}";
            } catch (const std::exception& e) {
                return "{\"code\": 1, \"msg\": \"Error updating book\", \"error\": \"" + std::string(e.what()) + "\"}";
            }
        } else {
            return "{\"code\": 1, \"msg\": \"Book not found\"}";
        }
    }

    std::string deleteBook(const std::string& bookId) {
        auto it = std::find_if(bookDatabase.begin(), bookDatabase.end(),
                               [bookId](const Book& book) { return book.id == bookId; });

        if (it != bookDatabase.end()) {
            bookDatabase.erase(it);
            return "{\"code\": 0, \"msg\": \"Book deleted successfully\"}";
        } else {
            return "{\"code\": 1, \"msg\": \"Book not found\"}";
        }
    }

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
