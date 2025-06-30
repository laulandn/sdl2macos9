// Pipeline.c
//
// Copyright (C) 6th March 1994  Stuart Cheshire <cheshire@cs.stanford.edu>
//
// See PipeLine.h for usage instructions.

#include "PipeLine.h"

#define next(x) (((x)+1 < p->data_end) ? (x)+1 : p->data)
#define isfull()    (next(p->inptr) == p->outptr)
#define isempty()   (p->inptr == p->outptr)

// Normally chars counts the number of characters in the pipeline,
// and spaces counts the number of spaces. However, when there are
// NO ACTIVE WRITERS, chars is set to one greater than it should be.
// When the PipeLineGetData tries to read this phantom character,
// it recognises that there are no more writers, and returns -1 to
// indicate this fact. This is why in PipeLineInit, chars is initialized
// to one, because writers is initialized to zero.

void PipeLineInit(PipeLine *p, unsigned char *buffer, unsigned long size)
	{
	p->inptr = p->outptr = p->data = buffer;
	p->data_end = buffer + size;
	p->writers = 0;
	SemaphoreInit(&p->mutex, 1);
	SemaphoreInit(&p->chars, 1);
	SemaphoreInit(&p->spaces, size-1);
	}

void PipeLineOpen(PipeLine *p)
	{
	SemaphoreP(&p->mutex);
	if (p->writers++ == 0) SemaphoreP(&p->chars);
	SemaphoreV(&p->mutex);
	}

void PipeLineClose(PipeLine *p)
	{
	SemaphoreP(&p->mutex);
	if (--p->writers == 0) SemaphoreV(&p->chars);
	SemaphoreV(&p->mutex);
	}

void PipeLinePutData(PipeLine *p, unsigned char x)
	{
	SemaphoreP(&p->spaces);			// Wait until we have a space
	SemaphoreP(&p->mutex);			// Grab the lock
	*p->inptr = x;					// Put the character in
	p->inptr = next(p->inptr);		// Advance pointer to the next slot
	SemaphoreV(&p->mutex);			// Release the lock
	SemaphoreV(&p->chars);			// Indicate that we have another character
	}

short PipeLineGetData(PipeLine *p)
	{
	int x;
	SemaphoreP(&p->chars);			// Wait until we have a character
	SemaphoreP(&p->mutex);			// Grab the lock
	if (isempty())					// If the buffer is empty,
		{							// then there are no active writers, so
		SemaphoreV(&p->mutex);		// Release the lock
		SemaphoreV(&p->chars);		// Put the 'fake' character back
		return(NO_WRITERS);			// Return -1 to the reader
		}
	x = *p->outptr;					// Get the character out
	p->outptr = next(p->outptr);	// Advance pointer to the next slot
	SemaphoreV(&p->mutex);			// Release the lock
	SemaphoreV(&p->spaces);			// Indicate that we have another space
	return(x);
	}
