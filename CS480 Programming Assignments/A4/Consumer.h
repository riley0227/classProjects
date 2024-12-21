/*

I the undersigned promise that the submitted assignment is my own work. While I was
free to discuss ideas with others, the work contained is my own. I recognize that
should this not be the case; I will be subject to penalties as outlined in the course
syllabus.
Name: Riley Thompson
Red ID: 826526487

*/
#ifndef CONSUMER_H
#define CONSUMER_H

#include "Broker.h"  
#include "fooddelivery.h"

class Consumer {
public:
    // pointer to the broker object
    Broker* broker;
    // the type of consumer and the type of request
    ConsumerType cType;
    RequestType rType;
    // time in milliseconds the consumer waits after processing a request
    int sleep;

    /**
     * constructor for the consumer class
     * @param broker Pointer to broker object
     * @param cType type of consumer
     * @param sleep time consumer waits after processing a request(delivering)
     */
    Consumer(Broker* broker, ConsumerType cType, int sleep);

    /**
     * static function for consumer threads and is how they consume requests and the fucntion is passed through thread to consume requests
     * @param ptr void pointer(will be cast to point of type consumer)
     * @return returns NULL after completing
     */
    static void *consumeFood(void *ptr);

};

#endif 