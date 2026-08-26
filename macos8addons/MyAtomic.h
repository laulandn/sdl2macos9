#ifndef ATOMIC_INTERRUPTS_H
#define ATOMIC_INTERRUPTS_H


#include <MacTypes.h>


static inline UInt16 DisableInterrupts(void) {
#ifdef __POWERPC__
  return 0;
#else
/**
 * Disables all maskable interrupts by raising the 68k IPL to level 7.
 * @return The original 16-bit Status Register (SR) value.
 */
    UInt16 oldSR;
    
    __asm__ __volatile__(
        "move.w %%sr, %0\n\t"  // 1. Save current Status Register to oldSR
        "ori.w  #0x0700, %%sr" // 2. Set IPL bits to 7 (bits 8-10) to mask IRQs
        : "=d" (oldSR)         // Output: target data register mapped to oldSR
        :                      // No inputs
        : "cc"                 // Clobber: Condition Codes are modified by ORI
    );
    
    return oldSR;
#endif
}


static inline void RestoreInterrupts(UInt16 oldSR) {
#ifdef __POWERPC__
#else
/**
 * Restores the 68k Status Register to its previous state.
 * @param oldSR The 16-bit SR value returned by DisableInterrupts().
 */
    __asm__ __volatile__(
        "move.w %0, %%sr"      // Restore saved status register (including old IPL)
        :                      // No outputs
        : "d" (oldSR)          // Input: pass oldSR via a data register
        : "cc"                 // Clobber: Condition Codes overridden by old SR
    );
#endif
}


#endif // ATOMIC_INTERRUPTS_H
