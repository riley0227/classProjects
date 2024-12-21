#include <queue>
#include "request.h" // Include the Request class definition
// Broker.h
#ifndef BROKER_H
#define BROKER_H

class Broker {
private:
    std::queue<Request> queue; // Queue to store requests

public:
    void add(const Request& request);
    Request remove();
};

#endif

// Broker.cpp
#include "Broker.h"
#include <semaphore.h>

extern sem_t full, empty, mutex;

void Broker::add(const Request& request) {
    sem_wait(&empty);
    sem_wait(&mutex);
    queue.push(request);
    sem_post(&mutex);
    sem_post(&full);
}

Request Broker::remove() {
    sem_wait(&full);
    sem_wait(&mutex);
    Request request = queue.front();
    queue.pop();
    sem_post(&mutex);
    sem_post(&empty);
    return request;
}
