
#include <ConditionalMacros.h>


#if TARGET_CPU_68K && !TARGET_RT_MAC_CFM
#include "./MacThreads_m68k.h"
#else
#include "./MacThreads_modern.h"
#endif
