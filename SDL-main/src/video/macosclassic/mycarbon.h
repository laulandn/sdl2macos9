#if TARGET_API_MAC_CARBON
#ifdef __MACH__
#include <Carbon/Carbon.h>
#else
#undef SIGHUP
#undef SIGURG
#undef SIGPOLL
#include <Carbon.h>
#endif
#else
#error dont include this!
#endif

