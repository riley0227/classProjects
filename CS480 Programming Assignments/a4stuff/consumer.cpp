// // Consumer.cpp
// // Implementation of the Consumer class

// #include "Consumer.h"
// #include "Broker.h"
// #include "log.h"
// #include <unistd.h>   // For usleep
// #include <semaphore.h>

// extern Broker broker;               // Assumes broker is defined elsewhere
// extern semaphore full, empty, mutex;  // Assumes these semaphores are defined and initialized elsewhere

// // Constructor implementation
// Consumer::Consumer(int id, int consumeTime) : id(id), consumeTime(consumeTime) {}

// // Consume method implementation
// void Consumer::consume() {
//     while (true) {
//         sem_wait(&full);           // Wait until there's something to consume
//         sem_wait(&mutex);          // Lock access to the queue

//         // Attempt to remove an item from the broker's queue
//         std::string request = broker.remove();
//         if (request.empty()) {     // Check if there is no request (optional based on your queue logic)
//             sem_post(&mutex);      // Release mutex lock
//             sem_post(&full);       // Incorrectly signaling full here; adjust as needed for your logic
//             break;                 // Exit if no requests are to be processed (signal to stop consuming)
//         }

//         log_removed_request(id, request);  // Log the removal of the request

//         sem_post(&mutex);          // Release mutex lock
//         sem_post(&empty);          // Signal that there is an empty space

//         // Simulate the consumption process
//         if (consumeTime > 0) {
//             usleep(consumeTime * 1000);  // Sleep to simulate time taken to process the request
//         }
//     }
// }
