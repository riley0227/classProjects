#include "Broker.h"
#include "Request.h"

Broker::Broker() {
    sem_init(&full, 0, 0);             // Initialize 'full' semaphore to 0
    sem_init(&empty, 0, 10);           // Initialize 'empty' semaphore to 10 (assuming max queue size is 10)
    sem_init(&mutex, 0, 1);            // Initialize 'mutex' semaphore to 1 for mutual exclusion
}

Broker::~Broker() {
    sem_destroy(&full);
    sem_destroy(&empty);
    sem_destroy(&mutex);
}

void Broker::add(Request* request) {
    sem_wait(&empty);                  // Wait for space to be available
    sem_wait(&mutex);                  // Lock the queue for exclusive access
    queue.push(request);               // Push the new request onto the queue
    sem_post(&mutex);                  // Unlock the queue
    sem_post(&full);                   // Signal that there is a new item in the queue
}

Request* Broker::remove() {
    sem_wait(&full);                   // Wait for an item to be available
    sem_wait(&mutex);                  // Lock the queue for exclusive access
    Request* request = queue.front();  // Get the front request
    queue.pop();                       // Remove the request from the queue
    sem_post(&mutex);                  // Unlock the queue
    sem_post(&empty);                  // Signal that there is now space available
    return request;                    // Return the request pointer
}
