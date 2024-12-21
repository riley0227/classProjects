/*

I the undersigned promise that the submitted assignment is my own work. While I was
free to discuss ideas with others, the work contained is my own. I recognize that
should this not be the case; I will be subject to penalties as outlined in the course
syllabus.
Name: Riley Thompson
Red ID: 826526487

*/
#include <time.h>
#include "Producer.h"
#include "Broker.h"
#include "log.h"
#include "fooddelivery.h"

Producer::Producer(Broker* broker, RequestType rType, int sleep){
    // initializes producer with broker, request type, and sleep time.
    this->broker = broker;
    this->rType = rType;
    this->sleep = sleep;
}

void *Producer::produceFood(void *ptr) {
    // Cast the void pointer to a producer pointer
    Producer *producer = (Producer *)ptr;

    // sets up sleep time struct, Convert milliseconds to seconds then to nanoseconds
    struct timespec sleepTime;
    sleepTime.tv_sec = producer->sleep / 1000;
    sleepTime.tv_nsec = (producer->sleep % 1000) * 1000000L;

    // gets broker instance from the producer
    Broker* broker = producer->broker;

    while(true) {
        // check if all requests are produced, then exit loop
        if((broker->producedCount) >= (broker->/*testreq*/totalRequestsToProcess) - 1) {
            break;
        }

        // sleep for the specified amount of time
        nanosleep(&sleepTime, nullptr);
        
        // wait for the available sandwich slots if the reqeust type is sandwich
        if (producer->rType == Sandwich) {
            sem_wait(&(broker->availableSandoSlots));
        }
        
        // wait if the queue is full
        sem_wait(&(broker->availableSlotsTotal));
        

        // gets mutex to ensure exclusive access to shared resources
        sem_wait(&(broker->mutex));

        // creates a new request from producer request type and adds it to queue
        RequestType* req = new RequestType(producer->rType);
        broker->requestQueue.push(req);

        // increment the produced to add the produced type and increment whats in queue
        broker->produced[producer->rType]++;
        broker->inQueue[producer->rType]++;

        // puts in the information for RequestAdded
        RequestAdded requestAdded;
        requestAdded.type = producer->rType;
        requestAdded.produced = broker->produced.data();
        requestAdded.inBrokerQueue = broker->inQueue.data();

        // logs the added request
        log_added_request(requestAdded);

        // releases the mutex and update so show been added to the unconsumed queue
        sem_post(&(broker->mutex));
        sem_post(&(broker->unconsumed));
        
        // increment produced requests
        broker->producedCount++;

    }
    return NULL;
}