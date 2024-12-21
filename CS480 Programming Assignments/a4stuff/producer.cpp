// // Producer.cpp
// // Implementation of the Producer class

// #include "Producer.h"
// #include "Broker.h"
// #include "log.h"
// #include <unistd.h>  // For usleep
// #include <semaphore.h>

// extern Broker broker;               // Assumes broker is defined elsewhere
// extern semaphore full, empty, mutex; // Assumes these semaphores are defined and initialized elsewhere

// // Constructor implementation
// Producer::Producer(int id, int productionTime, int maxRequests, std::string type) :
//     id(id), productionTime(productionTime), maxRequests(maxRequests), type(type) {}

// // Produce pizza method implementation
// void Producer::producePizza() {
//     for (int i = 0; i < maxRequests; ++i) {
//         sem_wait(&empty);         // Wait until there's space to add a new request
//         sem_wait(&mutex);         // Lock access to the queue

//         std::string request = "Pizza Request";  // Creating a pizza request
//         broker.add(request);
//         //log_added_request(id, request); // Log the addition of the request

//         sem_post(&mutex);         // Release mutex lock
//         sem_post(&full);          // Signal that there is a new item

//         // Simulate the production process
//         if (productionTime > 0) {
//             usleep(productionTime * 1000);  // Sleep to simulate time taken to produce the request
//         }
//     }
// }

// // Produce sandwich method implementation
// void Producer::produceSandwich() {
//     for (int i = 0; i < maxRequests; ++i) {
//         sem_wait(&empty);         // Wait until there's space to add a new request
//         sem_wait(&mutex);         // Lock access to the queue

//         std::string request = "Sandwich Request"; // Creating a sandwich request
//         broker.add(request);
//         //log_added_request(id, request); // Log the addition of the request

//         sem_post(&mutex);         // Release mutex lock
//         sem_post(&full);          // Signal that there is a new item

//         // Simulate the production process
//         if (productionTime > 0) {
//             usleep(productionTime * 1000);  // Sleep to simulate time taken to produce the request
//         }
//     }
// }
