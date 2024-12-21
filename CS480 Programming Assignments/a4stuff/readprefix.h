/*
 * readprefix.h
 */

#ifndef READ_PREFIX_H
#define READ_PREFIX_H

/*
 * void * readPrefixToQueue(void *)
 * Thread entry point. Argument must be a pointer to a SHARED_DATA 
 * structure which contains the communication channel and 
 * thread parameters.
 *
 * readPrefixToQueue thread is for reading words from a file (file 
 * name passed from the shared SHARED_DATA); and storing words into
 * a request queue.
 */

extern "C" void * readPrefixToQueue(void *);

#endif
