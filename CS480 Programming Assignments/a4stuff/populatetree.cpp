#include <stdio.h>
#include <string.h>
#include <cstring>
#include <string>
#include <fstream>
#include <iostream>
#include "populatetree.h"
#include "shared.h"

using namespace std;

/*
 * void * populateTree(void *)
 * Thread entry point.  Argument must be a pointer to a SHARED_DATA structure
 * which contains the communication channel and process parameters.
 *
 * populatetree thread is responsible for reading words from a file (file name
 * passed from a shared buffer), and inserting those words into a dictionary
 * tree which is also part of a shared buffer.
 */

void *populateTree(void *voidPtr)
{

  SHARED_DATA *shared = (SHARED_DATA *) voidPtr;

  if (shared == NULL)
    return NULL;

  /* for tokenizing the words */
  const char *separators = "\n\r !\"#$%&()*+,./0123456789:;<=>?@[\\]^`{|}~";

  // build the dictionary
  ifstream dictstream(shared->filePath[DICTSRCFILEINDEX]); // open file for parsing
  string line;

  // iterate over dictionary file line by line
  while (std::getline(dictstream, line))
  {
    // tokenize words from line and add them to the dictionary tree
  }

  dictstream.close();

  // do not set the taskCompleted here
  // the taskCompleted flag will be set after 
  // the display of progress bar finishes

  return NULL;
}
