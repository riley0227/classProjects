#ifndef PRODUCER_H
#define PRODUCER_H

#include <string>
#include <semaphore.h>
#include <unistd.h>  // for usleep
#include "Broker.h"
#include "Request.h"

class Producer {
public:
    Producer(Broker* broker, sem_t* sem_empty, sem_t* sem_full, sem_t* sem_mutex, const std::string& requestType, int delay)
        : broker(broker), sem_empty(sem_empty), sem_full(sem_full), sem_mutex(sem_mutex), requestType(requestType), sleep(delay * 1000) {}

    void produce() {
        while (true) { // You might have some condition to stop producing based on your application logic
            usleep(sleep); // Simulate delay in producing the request

            sem_wait(sem_empty); // Wait for space in the buffer
            sem_wait(sem_mutex); // Lock the buffer access

            // Produce the item and add to the broker
            Request* request = new Request(requestType, 0, broker); // Assume no additional sleep delay needed for request
            broker->add(request);

            sem_post(sem_mutex); // Release buffer access
            sem_post(sem_full);  // Signal that there's a new item in the buffer

            // Potentially break out or continue based on the application logic
        }
    }
    Broker* broker;
    sem_t* sem_empty;
    sem_t* sem_full;
    sem_t* sem_mutex;
    std::string requestType;
    int sleep;
};

#endif // PRODUCER_H
