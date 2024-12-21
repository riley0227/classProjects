/*

I the undersigned promise that the submitted assignment is my own work. While I was
free to discuss ideas with others, the work contained is my own. I recognize that
should this not be the case; I will be subject to penalties as outlined in the course
syllabus.
Name: Riley Thompson
Red ID: 826526487

*/
#ifndef PRODUCER_H
#define PRODUCER_H

#include "Broker.h"  
#include "fooddelivery.h"

class Producer {
public:
    // pointer to the broker object
    Broker* broker;
    // the type of request
    RequestType rType;
    // time in milliseconds the producer waits before processing a request(making food)
    int sleep;

    /**
     * constructor for the producer class
     * @param broker pointer to broker object
     * @param rType type of request to produce
     * @param sleep time to sleep between producing requests(making)
     */
    Producer(Broker* broker, RequestType rType, int sleep);

    /**
     * static function for producer threads and is how they produce requests and the fucntion is passed through thread to produce requests
     * @param ptr void pointer(will be cast to point of type producer)
     * @return returns NULL after completing
     */
    static void *produceFood(void *ptr);

};

#endif
