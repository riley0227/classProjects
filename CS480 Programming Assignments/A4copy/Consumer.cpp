#ifndef CONSUMER_H
#define CONSUMER_H

#include <string>
#include <semaphore.h>
#include <unistd.h>  // for usleep
#include "Broker.h"
#include "Request.h"

class Consumer {
public:
    Consumer(Broker* broker, sem_t* sem_empty, sem_t* sem_full, sem_t* sem_mutex, int delay)
        : broker(broker), sem_empty(sem_empty), sem_full(sem_full), sem_mutex(sem_mutex), sleep(delay * 1000) {}

    void consume() {
        while (true) { // Condition based on application logic
            sem_wait(sem_full);   // Wait until there's something in the buffer
            sem_wait(sem_mutex);  // Lock the buffer access

            // Remove the item from the broker
            // Request* request = broker->remove();
            sem_post(sem_mutex); // Release buffer access
            sem_post(sem_empty); // Signal that there's space in the buffer

            usleep(sleep); // Simulate delay in processing the request

            // Potentially break out or continue based on the application logic
        }
    }
    Broker* broker;
    sem_t* sem_empty;
    sem_t* sem_full;
    sem_t* sem_mutex;
    int sleep;
private:
    
};

#endif // CONSUMER_H
