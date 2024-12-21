#include <stdio.h>
#include "readprefix.h"
#include "shared.h"
#include <string.h>
#include <cstring>
#include <string>
#include <ctype.h> 
#include <fstream>
#include <iostream>
#include <unordered_map>

using namespace std;

/*
 * void * readPrefixToQueue(void *)
 * Thread entry point.  Argument must be a pointer to a SHARED_DATA structure
 * which contains the communication channel and thread parameters.
 *
 * readPrefixToQueue thread is responsible for reading words/prefix from a file (file
 * name passed from the shared buffer); and putting each prefix in a queue.
 */

void *readPrefixToQueue(void *voidPtr)
{
  SHARED_DATA *shared = (SHARED_DATA *)voidPtr;

  if (shared == NULL)
    return NULL;

  // for tokenizing the words
  const char *separators = "\n\r !\"#$%&()*+,./0123456789:;<=>?@[\\]^`{|}~";

  // busy wait for the dictionary tree to be populated 
  // .....

  // read the file that contains prefixes
  ifstream textstream(shared->filePath[EMULATEREQUESTSFILEINDEX]); 
  string line;

  // iterate over file line by line
  while (getline(textstream, line))
  {
    //.....

    // Get first token, remember strtok is NOT thread safe
    char *token = strtok(..., separators);
    while (token != nullptr)
    {
      string token_s = token;

      sem_wait(&(shared->queue_mutex));

      // queue each requested word
      // need to use a mutex to lock the queue for pushing
      // to avoid potential race condition while the queue 
      // could be popped for counting prefix 
      shared->prefixQueue.push(token_s);
      
      // update the number of words read
      shared->wordCountInFile[EMULATEREQUESTSFILEINDEX] ++;

      sem_post(&(shared->queue_mutex));

      token = strtok(NULL, separators);
    }
      
  }

  // set task completion for reading and queuing prefix 
  //......

  textstream.close();

  // do not set the taskCompleted here
  // the taskCompleted flag will be set after 
  // the display of progress bar finishes

  return NULL;
}
