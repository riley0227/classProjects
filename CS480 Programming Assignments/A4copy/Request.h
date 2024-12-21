#ifndef REQUEST_H
#define REQUEST_H

#include <string>
class Broker; // Forward declaration of Broker

class Request {
public:
    std::string type;  // Type of the request, e.g., "Pizza" or "Sandwich"
    int sleep; 
    Broker* broker; // Forward declaration is enough for pointers

    Request(const std::string& type, int sleep, Broker* broker)
        : type(type), sleep(sleep), broker(broker) {}

    // Additional methods relevant to request handling could be added here
};

#endif // REQUEST_H
