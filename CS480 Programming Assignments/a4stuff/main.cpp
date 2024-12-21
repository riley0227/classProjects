//
// Created by Riley Thompson
// RedID: 82607182
//

#include <cstdio>
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include <getopt.h>

using namespace std;

#define NORMAL_EXIT 0
#define DEFAULT_REQUESTS 100
#define DEFAULT_MILLISECONDS 0

int main(int argc, char **argv) {
    int totalRequests = DEFAULT_REQUESTS; // Total number of delivery requests
    int timeMsA = DEFAULT_MILLISECONDS;   // Time to process request by service A
    int timeMsB = DEFAULT_MILLISECONDS;   // Time to process request by service B
    int timeMsP = DEFAULT_MILLISECONDS;   // Time to produce a pizza request
    int timeMsS = DEFAULT_MILLISECONDS;   // Time to produce a sandwich request

    // getopt loop to process command line arguments
    int opt;
    while ((opt = getopt(argc, argv, "n:a:b:p:s:")) != -1) {
        switch (opt) {
            case 'n': // Total number of delivery requests
                totalRequests = stoi(optarg);
                break;
            case 'a': // Time for service A
                timeMsA = stoi(optarg);
                break;
            case 'b': // Time for service B
                timeMsB = stoi(optarg);
                break;
            case 'p': // Time to produce a pizza request
                timeMsP = stoi(optarg);
                break;
            case 's': // Time to produce a sandwich request
                timeMsS = stoi(optarg);
                break;
            default: // Incorrect usage
                cout << "Usage: " << argv[0] << " [-n total_requests] [-a time_ms_A] [-b time_ms_B] [-p time_ms_P] [-s time_ms_S]" << endl;
                return 1;
        }
    }

    
//     // Create producer threads
//     for (int i = 0; i < PRODUCER_COUNT; i++) {
//         pthread_create(&producers[i], NULL, producer_routine, NULL);
//     }

//     // Create consumer threads
//     for (int i = 0; i < CONSUMER_COUNT; i++) {
//         pthread_create(&consumers[i], NULL, consumer_routine, NULL);
//     }

//     // Wait for all producer threads to complete
//     for (int i = 0; i < PRODUCER_COUNT; i++) {
//         pthread_join(producers[i], NULL);
//     }

//     // Wait for all consumer threads to complete
//     for (int i = 0; i < CONSUMER_COUNT; i++) {
//         pthread_join(consumers[i], NULL);
//     }

//     // Cleanup semaphores
//     sem_destroy(&empty);
//     sem_destroy(&full);
//     sem_destroy(&mutex);

//     // Exit the program
//     return NORMAL_EXIT;
// }

// // Producer thread routine
// void* producer_routine(void* arg) {
//     // Produce requests
//     while (production not completed) {
//         produce_request();
//     }
//     return NULL;
// }

// // Consumer thread routine
// void* consumer_routine(void* arg) {
//     // Consume requests
//     while (requests still available) {
//         consume_request();
//     }
//     return NULL;
// }
    // Output the configured values to verify they're set correctly
    cout << "Total Requests: " << totalRequests << endl;
    cout << "Time for Service A: " << timeMsA << " ms" << endl;
    cout << "Time for Service B: " << timeMsB << " ms" << endl;
    cout << "Time to Produce Pizza Request: " << timeMsP << " ms" << endl;
    cout << "Time to Produce Sandwich Request: " << timeMsS << " ms" << endl;

    return 0;
}
