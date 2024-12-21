// Broker.h
// Header file for the Broker class that manages a queue of Request objects.

#ifndef BROKER_H
#define BROKER_H

#include <queue>
#include "request.h"  // Include the Request class definition to use Request objects in the queue

class Broker {
private:
    std::queue<Request> queue;  // Queue to store Request objects

public:
    // Adds a request to the queue in a thread-safe manner
    void add(const Request& request);

    // Removes a request from the queue in a thread-safe manner and returns it
    Request remove();
};

#endif // BROKER_H
