/*

I the undersigned promise that the submitted assignment is my own work. While I was
free to discuss ideas with others, the work contained is my own. I recognize that
should this not be the case; I will be subject to penalties as outlined in the course
syllabus.
Name: Riley Thompson
Red ID: 826526487

*/

#include <getopt.h>
#include <string>
#include "Broker.h"
#include "Producer.h"
#include "Consumer.h"
#include "log.h"
using namespace std;

#define NORMAL_EXIT 0
#define DEFAULT_REQUESTS 100
#define DEFAULT_MILLISECONDS 0

int main(int argc, char **argv) {
    // total number of delivery requests
    int totalDelRequests = DEFAULT_REQUESTS; 
    // time to process request by service A and B
    int timeConsDelivA = DEFAULT_MILLISECONDS;  
    int timeConsDelivB = DEFAULT_MILLISECONDS;
    // time to produce a pizza or sandwich request
    int timeProducePizza = DEFAULT_MILLISECONDS;  
    int timeProduceSando = DEFAULT_MILLISECONDS;

    // getopt loop to process command line arguments
    int opt;
    while ((opt = getopt(argc, argv, "n:a:b:p:s:")) != -1) {
        switch (opt) {
            // total number of delivery requests
            case 'n':
                totalDelRequests = stoi(optarg);
                break;
            // time for service A to consume a request
            case 'a': 
                timeConsDelivA = stoi(optarg);
                break;
            // time for service B to consume a request
            case 'b': 
                timeConsDelivB = stoi(optarg);
                break;
            // time to produce a pizza request
            case 'p': 
                timeProducePizza = stoi(optarg);
                break;
            // time to produce a sandwich request
            case 's':
                timeProduceSando = stoi(optarg);
                break;
            default: 
                // if unreconginzed option, returns 1
                return 1;
        }
    }
    // creates new broker with total number of delivery requests
    Broker *broker = new Broker(totalDelRequests);

    // creates producer objects for pizza and sandwich requests, specifying broker, request type, and production times.
    Producer* producerPizza = new Producer(broker, Pizza, timeProducePizza);
    Producer* producerSando = new Producer(broker, Sandwich, timeProduceSando);
    // creates consumer objects for pizza and sandwich requests, specifying broker, consumer type, and delivery/consumtion times.
    Consumer* consumerA = new Consumer(broker, DeliveryServiceA, timeConsDelivA);
    Consumer* consumerB = new Consumer(broker, DeliveryServiceB, timeConsDelivB);

    // thread identifiers for producers(produce sandwhiches and produce pizzas) and consumers(delivery service a and b)
    pthread_t prodSando, prodPizza, consA, consB;
    
    // Start the producer thread for pizza and sandwich requests.  Both will run produceFood function specifying producer Pizza or Producer Sandwhich
    pthread_create(&prodPizza, nullptr, Producer::produceFood, producerPizza);
    pthread_create(&prodSando, nullptr, Producer::produceFood, producerSando);
    // Start the consumer thread for delivery service a and delivery service b, called consumerA and B.  Both will run consumeFood function specifying as delivery service A or B
    pthread_create(&consA, nullptr, &Consumer::consumeFood, consumerA);
    pthread_create(&consB, nullptr, &Consumer::consumeFood, consumerB);

    // block the main thread until consumer threads say completed(sem_post(&(broker->endMain));)
    sem_wait(&broker->endMain);

    // Initialize an array of pointers to track consumption counts for each consumer type
    unsigned int *consumed[ConsumerTypeN];
    for (int i = 0; i < ConsumerTypeN; i++) {
        // pointer targets a different segment of the consumed array and corresponding with consumer type
        consumed[i] = broker->consumedA.data() + i * ConsumerTypeN;
    }

    // log the produced and consumed history
    log_production_history(broker->produced.data(), consumed);
    
    // delete objects to clean
    delete broker;
    delete producerPizza;
    delete producerSando;
    delete consumerA;
    delete consumerB;
    return 0;
}
