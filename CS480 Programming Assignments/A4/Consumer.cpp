/*

I the undersigned promise that the submitted assignment is my own work. While I was
free to discuss ideas with others, the work contained is my own. I recognize that
should this not be the case; I will be subject to penalties as outlined in the course
syllabus.
Name: Riley Thompson
Red ID: 826526487

*/
#include <time.h>
#include "Consumer.h"
#include "Broker.h"
#include "log.h"
#include "fooddelivery.h"
#include <array>
using namespace std;

Consumer::Consumer(Broker* broker, ConsumerType cType, int sleep){
        // initializes consumer with broker, consumer type, and sleep time.
        this->broker = broker;
        this->cType = cType;
        this->sleep = sleep;
}

// for consumer thread
void *Consumer::consumeFood(void *ptr) {
    // Cast the void pointer to a Consumer pointer
    Consumer *consumer = (Consumer *)ptr;

    // sets up sleep time struct, Convert milliseconds to seconds then to nanoseconds
    struct timespec sleepTime;
    sleepTime.tv_sec = consumer->sleep / 1000;
    sleepTime.tv_nsec = (consumer->sleep % 1000) * 1000000L;

    // gets broker instance from the consumer
    Broker* broker = consumer->broker;

    array<unsigned int, RequestTypeN>* consumedCounter;

    while(true) {
        // Check if all requests are consumed and the queue is empty, then exit loop
        if(((broker->consumedCount) >= (broker->totalRequestsToProcess ) - 1) && (broker->requestQueue.empty())) {
            break;
        }

        // Wait if there are no unconsumed items in the queue
        sem_wait(&(broker->unconsumed));

        // gets mutex to ensure exclusive access to shared resources
        sem_wait(&(broker->mutex));

        // gets request from front of queue and removes from queue, and sets consumers current reqeust type
        RequestType* req = broker->requestQueue.front();
        broker->requestQueue.pop();
        consumer->rType = *req;

        // determinines counter to use based on consumer type
        if (consumer->cType == DeliveryServiceA) {
            consumedCounter = &broker->consumedA;
        } else {
            consumedCounter = &broker->consumedB;
        }
        
        // increments the consumedCounter for the request type
        (*consumedCounter)[*req]++;

        //broker->consumedAB[index]++;
        // decriment whats in queue
        broker->inQueue[*req]--;

        // puts in the information for RequestRemoved
        RequestRemoved requestRemoved;
        requestRemoved.consumer = consumer->cType;
        requestRemoved.type = consumer->rType;
        requestRemoved.consumed = consumedCounter->data();
        requestRemoved.inBrokerQueue = broker->inQueue.data();

        // logs the removed request
        log_removed_request(requestRemoved);

        // releases the mutex and update the available slots in the queue
        sem_post(&(broker->mutex));

        // another availble slot ready
        sem_post(&(broker->availableSlotsTotal));
        
        // if consumed item is a sandwich post to the sandwich semaphore
        if (consumer->rType == Sandwich) {
            sem_post(&(broker->availableSandoSlots));
        }
        
        // free memory of request object and increment consumed requests
        delete req;
        broker->consumedCount++;

        // Sleep for the specified amount of time
        nanosleep(&sleepTime, nullptr);
    }
    // Post to the endMain semaphore which means consumer is done processing and main thread can stop
    sem_post(&(broker->endMain));
    return NULL;
}