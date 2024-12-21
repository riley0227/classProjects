// Request.h
#ifndef REQUEST_H
#define REQUEST_H

#include <string>

class Request {
public:
    std::string type; // Type of the request, e.g., "Pizza" or "Sandwich"
    std::string details; // Detailed description or other relevant information

    // Constructor to initialize a Request object
    Request(const std::string& type, const std::string& details) : type(type), details(details) {}

    // You miaght want to add other functions relevant to request handling here
};

#endif
