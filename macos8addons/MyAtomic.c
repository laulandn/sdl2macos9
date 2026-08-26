#include <stdio.h>


#include "SDL_stdinc.h"
#include "SDL_atomic.h"


#include "MyAtomic.h"


UInt32 BitOrAtomic(UInt32 mask, UInt32 *address)
{
  short oldSR = DisableInterrupts();
  *address |= mask;
  UInt32 result = *address;
  RestoreInterrupts(oldSR);
  return result;
}


UInt32 BitAndAtomic(UInt32 mask, UInt32 *address)
{
  short oldSR = DisableInterrupts();
  *address &= mask;
  UInt32 result = *address;
  RestoreInterrupts(oldSR);
  return result;
}


SInt32 DecrementAtomic(SInt32 *address) 
{
  short oldSR = DisableInterrupts();
  SInt32 result=(*address)--;
  RestoreInterrupts(oldSR);
  return result;
}


SInt32 IncrementAtomic(SInt32 *address) 
{
  short oldSR = DisableInterrupts();
  SInt32 result=(*address)++;  // Should this be ++(*address)?!?
  RestoreInterrupts(oldSR);
  return result;
}


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
