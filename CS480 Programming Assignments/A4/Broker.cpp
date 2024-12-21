/*

I the undersigned promise that the submitted assignment is my own work. While I was
free to discuss ideas with others, the work contained is my own. I recognize that
should this not be the case; I will be subject to penalties as outlined in the course
syllabus.
Name: Riley Thompson
Red ID: 826526487

*/
#include "Broker.h"

Broker::Broker(int totalRequestsToProcess) {
    // initializes semaphores, mutual exclusion, availibleSlotsTotal with 20 empty slots to start, available sandwich slots with limit of 8, and one to control end of main thread
    sem_init(&mutex, 0, 1);
    sem_init(&countMutex, 0, 1);
    sem_init(&availableSlotsTotal, 0, 20);
    sem_init(&unconsumed, 0, 0);
    sem_init(&availableSandoSlots, 0, 8); 
    sem_init(&endMain, 0, 0);

    // Set initial counts of produced and consumed requests to 0, and total reuests to the value passed in.
    this->producedCount = 0;
    this->consumedCount = 0;
    this->totalRequestsToProcess = totalRequestsToProcess;
}

Broker::~Broker() {
    // destroys initialized semaphores
    sem_destroy(&mutex);
    sem_destroy(&availableSlotsTotal);
    sem_destroy(&unconsumed);
    sem_destroy(&availableSandoSlots);
    sem_destroy(&countMutex);
}