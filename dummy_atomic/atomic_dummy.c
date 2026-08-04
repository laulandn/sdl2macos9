
#include "SDL_stdinc.h"
#include "SDL_atomic.h"
#include <stdio.h>


#ifndef powerc
#include "atomic_interrupts.h"
#endif


/* This is just a placeholder, obviously not really atomic at all */
int _SDL_xchg_macosclassic(SDL_SpinLock *lock,int v)
{
    /*uint32_t oldintr;*/
    SDL_bool res = SDL_FALSE;
    /* disable interuption
    oldintr = DIntr();*/

    if (*lock == 0) {
        *lock = 1;
        res = SDL_TRUE;
    }
    /* enable interuption
    if (oldintr) {
        EIntr();
    }*/
    return res;
}


#ifndef powerc
UInt32 BitOrAtomic(UInt32 mask, UInt32 *address)
{
  short oldSR = DisableInterrupts();
  *address |= mask;
  UInt32 result = *address;
  RestoreInterrupts(oldSR);
  return result;
}
#endif


#ifndef powerc
UInt32 BitAndAtomic(UInt32 mask, UInt32 *address)
{
  short oldSR = DisableInterrupts();
  *address &= mask;
  UInt32 result = *address;
  RestoreInterrupts(oldSR);
  return result;
}
#endif


#ifndef powerc
SInt32 DecrementAtomic(SInt32 *address) 
{
  short oldSR = DisableInterrupts();
  SInt32 result=(*address)--;
  RestoreInterrupts(oldSR);
  return result;
}
#endif


#ifndef powerc
SInt32 IncrementAtomic(SInt32 *address) 
{
  short oldSR = DisableInterrupts();
  SInt32 result=(*address)++;  // Should this be ++(*address)?!?
  RestoreInterrupts(oldSR);
  return result;
}
#endif


#ifndef powerc
Boolean CompareAndSwap(UInt32 oldValue, UInt32 newValue, UInt32 *address) 
{
  short oldSR = DisableInterrupts();
  Boolean success = false;
  if (*address == oldValue) {
    *address = newValue;
    success = true;
  }
  RestoreInterrupts(oldSR);
  return success;
}
#endif
