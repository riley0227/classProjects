#ifndef PRODUCER_H
#define PRODUCER_H

#include <string>
#include "semaphore.h"
#include <unistd.h>  // for usleep
#include "Broker.h"
#include "Request.h"

class Producer {
public:
    Broker* broker;
    sem_t sem_empty;
    sem_t sem_full;
    sem_t sem_mutex;
    std::string requestType;
    int sleep;

    Producer(Broker* broker, const std::string& requestType, int delay)
        : broker(broker), requestType(requestType), sleep(delay * 1000) {
        sem_init(&sem_empty, 0, 10);  // Assuming buffer size is 10 for example
        sem_init(&sem_full, 0, 0);
        sem_init(&sem_mutex, 0, 1);
    }

    ~Producer() {
        sem_destroy(&sem_empty);
        sem_destroy(&sem_full);
        sem_destroy(&sem_mutex);
    }

    void produce() {
        while (true) { // Implement a real stopping condition
            usleep(sleep); // Simulate delay in producing the request

            sem_wait(&sem_empty); // Wait for space in the buffer
            sem_wait(&sem_mutex); // Lock the buffer access

            // Produce the item and add to the broker
            Request* request = new Request(requestType, 0, broker); // Assuming no additional sleep delay needed for request
            broker->add(request);  // Assuming broker has an add method accepting Request*

            sem_post(&sem_mutex); // Release buffer access
            sem_post(&sem_full);  // Signal that there's a new item in the buffer
        }
    }
};

#endif // PRODUCER_H
