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
#include "Broker.h"
#include "Producer.h"
#include "Consumer.h"

using namespace std;

#define NORMAL_EXIT 0
#define DEFAULT_REQUESTS 100
#define DEFAULT_MILLISECONDS 0

void* producer(void* arg) {
    Producer* p = static_cast<Producer*>(arg);
    p->produce();
    return nullptr;
}

void* consumer(void* arg) {
    Consumer* c = static_cast<Consumer*>(arg);
    c->consume();
    return nullptr;
}

int main(int argc, char **argv) {
    int totalDelRequests = DEFAULT_REQUESTS; // Total number of delivery requests
    int timeConsDelivA = DEFAULT_MILLISECONDS;   // Time to process request by service A
    int timeConsDelivB = DEFAULT_MILLISECONDS;   // Time to process request by service B
    int timeProducePizza = DEFAULT_MILLISECONDS;   // Time to produce a pizza request
    int timeProduceSando = DEFAULT_MILLISECONDS;   // Time to produce a sandwich request
    Broker *broker = new Broker();

    // getopt loop to process command line arguments
    int opt;
    while ((opt = getopt(argc, argv, "n:a:b:p:s:")) != -1) {
        switch (opt) {
            case 'n': // Total number of delivery requests
                totalDelRequests = stoi(optarg);
                break;
            case 'a': // Time for service A
                timeConsDelivA = stoi(optarg);
                break;
            case 'b': // Time for service B
                timeConsDelivB = stoi(optarg);
                break;
            case 'p': // Time to produce a pizza request
                timeProducePizza = stoi(optarg);
                break;
            case 's': // Time to produce a sandwich request
                timeProduceSando = stoi(optarg);
                break;
            default: // Incorrect usage
                cout << "Usage: " << argv[0] << " [-n total_requests] [-a time_ms_A] [-b time_ms_B] [-p time_ms_P] [-s time_ms_S]" << endl;
                return 1;
        }
    }

    Producer* producerPizza = new Producer(broker, "Pizza", timeProducePizza);
    Producer* producerSando = new Producer(broker, "Sandwich", timeProduceSando);
    Consumer* consumerPizza = new Consumer(broker, "Pizza", timeConsDelivA);
    Consumer* consumerSando = new Consumer(broker, "Sandwich", timeConsDelivB);
    //const std::string& type, int sleep, Broker* broker

    pthread_t prodSando, prodPizza, consSando, consPizza;
    

    pthread_create(&prodPizza, nullptr, producer, producerPizza);
    pthread_create(&prodSando, nullptr, producer, producerSando);
    pthread_create(&consPizza, nullptr, consumer, consumerPizza);
    pthread_create(&consSando, nullptr, consumer, consumerSando);

    cout << "Total Requests: " << totalDelRequests << endl;
    cout << "Time for Service A: " << timeConsDelivA << " ms" << endl;
    cout << "Time for Service B: " << timeConsDelivB << " ms" << endl;
    cout << "Time to Produce Pizza Request: " << timeProducePizza << " ms" << endl;
    cout << "Time to Produce Sandwich Request: " << timeProduceSando << " ms" << endl;

    delete broker;
    delete producerPizza;
    delete producerSando;
    delete consumerPizza;
    delete consumerSando;
//,ending main., mutex, availible slots, unconsumed, unconsumed items, availbel sandwhcih slots
    return 0;
}
