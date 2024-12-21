#ifndef CONSUMER_H
#define CONSUMER_H

#include <string>
#include <semaphore.h>
#include <unistd.h>  // for usleep
#include "Broker.h"
#include "Request.h"

class Consumer {
public:
    Consumer(Broker* broker, const std::string& requestType, int delay)
        : broker(broker), requestType(requestType), sleep(delay * 1000) {
        sem_init(&sem_empty, 0, 10);  // Buffer size should match Producer or broker capacity
        sem_init(&sem_full, 0, 0);
        sem_init(&sem_mutex, 0, 1);
    }

    ~Consumer() {
        sem_destroy(&sem_empty);
        sem_destroy(&sem_full);
        sem_destroy(&sem_mutex);
    }

    void consume() {
        while (true) { // Condition to stop consuming could be implemented
            sem_wait(&sem_full);   // Wait until there's something in the buffer
            sem_wait(&sem_mutex);  // Lock the buffer access

            Request* request = broker->remove(); // Assumes remove returns a Request*
            if (request) {
                processRequest(request);
                delete request; // Clean up after processing
            }

            sem_post(&sem_mutex); // Release buffer access
            sem_post(&sem_empty); // Signal that there's space in the buffer

            usleep(sleep); // Simulate delay in processing the request
        }
    }

    void processRequest(Request* request) {
        // Implement request processing logic here
        // This function simulates the consumption and handling of a request
    }

private:
    Broker* broker;
    sem_t sem_empty;
    sem_t sem_full;
    sem_t sem_mutex;
    std::string requestType;
    int sleep;
};

#endif // CONSUMER_H
