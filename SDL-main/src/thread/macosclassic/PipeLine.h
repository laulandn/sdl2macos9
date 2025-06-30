// Pipeline.h
// 
// (C) 6th March 1994  Stuart Cheshire <cheshire@cs.stanford.edu>
// 
// Any thread can read from a PipeLine.
// A thread that wishes to write should first declare its intention by
// calling PipeLineOpen, and should call PipeLineClose when it has finished.
// A pipeline keeps track of how many writers it has, and if there are no
// writers it returns error code -1 to any thread that tries to read from it,
// to indicate that there is no more data.
// If you wish to have readers block and wait for a future writer to come along
// and provide data, instead of getting an error code back, then immediately after
// initializing the pipeline with PipeLineInit, call PipeLineOpen. This will make
// the pipeline think that there is always at least one active writer, so it will
// never return the "no writers" indication.

#ifndef __PIPELINE__
#define __PIPELINE__

#include "ThreadSynch.h"

#define NO_WRITERS (-1)

typedef struct
	{
	unsigned char *data;			// pointer to the data buffer
	unsigned char *data_end;		// end data buffer
	unsigned char *inptr, *outptr;	// pointers to where data is going in and out
	int writers;					// number of clients writing into this buffer
	Semaphore mutex, chars, spaces;
	} PipeLine;

extern void  PipeLineInit(PipeLine *p, unsigned char *buffer, unsigned long size);
extern void  PipeLineOpen(PipeLine *p);
extern void  PipeLineClose(PipeLine *p);
extern void  PipeLinePutData(PipeLine *p, unsigned char x);
extern short PipeLineGetData(PipeLine *p);

#endif
