/*
 * populatetree.h
 */

#ifndef POPULATETREE_H
#define	POPULATETREE_H

/*
 * void * populateTree(void *)
 * Thread entry point.  Argument must be a pointer to a SHARED_DATA structure
 * which contains the communication channel and thread parameters.
 *
 * See populatetree.cpp for details.
 */

extern "C" void * populateTree(void *);

#endif
