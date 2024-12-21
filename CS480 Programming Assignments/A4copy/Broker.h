#ifndef BROKER_H
#define BROKER_H

#include <queue>
#include <semaphore.h>

class Request; // Forward declaration of Request

class Broker {
public:
    Broker();
    ~Broker();

    void add(Request* request);  // Store pointers to Request objects
    Request* remove();           // Return pointers to Request objects

private:
    std::queue<Request*> queue; // Queue storing pointers to Request objects
    sem_t full, empty, mutex;   // Semaphores for full, empty, and mutual exclusion
};

#endif // BROKER_H
