/*

I the undersigned promise that the submitted assignment is my own work. While I was
free to discuss ideas with others, the work contained is my own. I recognize that
should this not be the case; I will be subject to penalties as outlined in the course
syllabus.
Name: Riley Thompson
Red ID: 826526487

*/
#ifndef BROKER_H
#define BROKER_H

#include <queue>
#include <semaphore.h>
#include "fooddelivery.h"
#include <array>
using namespace std;

class Broker {
public:
    /**
     * constructor for broker class
     * @param totalRequestsToProcess total number of requests broker handles
     */
    Broker(int totalRequestsToProcess);
    // destructor
    ~Broker();

    // total number of delivery reqeusts to process
    int totalRequestsToProcess;
    // queue storing pointers to request objects(the buffer)
    queue<RequestType*> requestQueue;
    // Semaphore for total available slots in the queue, tracks the number of items unconsumed, and mutual exclusion for accessing and changing shared resources.
    sem_t availableSlotsTotal, unconsumed, mutex, availableSandoSlots, endMain, countMutex;

    // track the number of requests produced and consumed of each typ(havaez), then number of each type of request currently in the queue.
    array<unsigned int, RequestTypeN> produced;
    array<unsigned int, RequestTypeN> consumedA;
    array<unsigned int, RequestTypeN> consumedB;
    array<unsigned int, RequestTypeN> consumedAB;
    array<unsigned int, RequestTypeN> inQueue;

    // counts for total number of reqeusts produced and consumed
    int producedCount;
    int consumedCount;
    
};

#endif 
