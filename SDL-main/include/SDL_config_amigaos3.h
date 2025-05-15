/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2025 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

#ifndef SDL_config_amigaos3_h_
#define SDL_config_amigaos3_h_
#define SDL_config_h_

#include "SDL_platform.h"
/**
 *  \file SDL_config_minimal.h
 *
 *  This is the minimal configuration that can be used to build SDL.
 */

#define SDL_BYTEORDER 4321

#define STDC_HEADERS 1
/*#define HAVE_ALLOCA_H 1*/
#define HAVE_CTYPE_H 1
#define HAVE_ICONV_H 1
#define HAVE_INTTYPES_H 1
#define HAVE_LIMITS_H 1
#define HAVE_MALLOC_H 1
#define HAVE_MATH_H 1
#define HAVE_MEMORY_H 1
#define HAVE_SIGNAL_H 1
#define HAVE_STDARG_H 1
#define HAVE_STDINT_H 1
#define HAVE_STDIO_H 1
#define HAVE_STDLIB_H 1
/*#define HAVE_STRINGS_H 1*/
#define HAVE_STRING_H 1
/*#define HAVE_SYS_TYPES_H 1*/

#define HAVE_DLOPEN 1
#define HAVE_MALLOC 1
#define HAVE_CALLOC 1
#define HAVE_REALLOC 1
#define HAVE_FREE 1
/*#define HAVE_ALLOCA 1*/
/*#define HAVE_GETENV 1
#define HAVE_SETENV 1
#define HAVE_PUTENV 1
#define HAVE_UNSETENV 1*/
#define HAVE_QSORT 1
#define HAVE_BSEARCH 1
#define HAVE_ABS 1
#define HAVE_BCOPY 1
#define HAVE_MEMSET 1
#define HAVE_MEMCPY 1
#define HAVE_MEMMOVE 1
#define HAVE_STRLEN 1
#define HAVE_STRCHR 1
#define HAVE_STRRCHR 1
#define HAVE_STRSTR 1
#define HAVE_STRTOL 1
#define HAVE_STRTOUL 1
#define HAVE_STRTOLL 1
#define HAVE_STRTOULL 1
#define HAVE_ATOI 1
#define HAVE_ATOF 1
#define HAVE_STRCMP 1
#define HAVE_STRNCMP 1
/*#define HAVE_STRCASECMP 1
#define HAVE_STRNCASECMP 1*/
#define HAVE_VSSCANF 1
#define HAVE_VSNPRINTF 1
#define HAVE_M_PI 1
#define HAVE_CEIL 1
#define HAVE_COPYSIGN 1
#define HAVE_COS 1
#define HAVE_COSF 1
#define HAVE_EXP 1
#define HAVE_FABS 1
#define HAVE_FLOOR 1
#define HAVE_LOG 1
#define HAVE_LOG10 1
#define HAVE_LROUND 1
#define HAVE_LROUNDF 1
#define HAVE_ROUND 1
#define HAVE_ROUNDF 1
#define HAVE_SCALBN 1
#define HAVE_SIN 1
#define HAVE_SINF 1
#define HAVE_SQRT 1
#define HAVE_SQRTF 1
#define HAVE_TAN 1
#define HAVE_TANF 1
#define HAVE_TRUNC 1
#define HAVE_TRUNCF 1
/*#define HAVE_SIGACTION 1*/
#define HAVE_SETJMP 1
/*#define HAVE_NANOSLEEP 1*/

#define LACKS_SYS_PARAM_H
#define LACKS_SYS_MMAN_H 1

/*#undef HAVE_MALLOC*/


#if !defined(HAVE_STDINT_H) && !defined(_STDINT_H_)
/* Most everything except Visual Studio 2008 and earlier has stdint.h now */
#if defined(_MSC_VER) && (_MSC_VER < 1600)
typedef signed __int8 int8_t;
typedef unsigned __int8 uint8_t;
typedef signed __int16 int16_t;
typedef unsigned __int16 uint16_t;
typedef signed __int32 int32_t;
typedef unsigned __int32 uint32_t;
typedef signed __int64 int64_t;
typedef unsigned __int64 uint64_t;
#ifndef _UINTPTR_T_DEFINED
#ifdef  _WIN64
typedef unsigned __int64 uintptr_t;
#else
typedef unsigned int uintptr_t;
#endif
#define _UINTPTR_T_DEFINED
#endif
#else
#define HAVE_STDINT_H 1
#endif /* Visual Studio 2008 */
#endif /* !_STDINT_H_ && !HAVE_STDINT_H */

#ifdef __GNUC__
#define HAVE_GCC_SYNC_LOCK_TEST_AND_SET 1
#endif

/* Enable the dummy audio driver (src/audio/dummy/\*.c) */
#define SDL_AUDIO_DRIVER_DUMMY  1
#define SDL_AUDIO_DRIVER_DISK  1

/* Enable the stub joystick driver (src/joystick/dummy/\*.c) */
/*#define SDL_JOYSTICK_DISABLED   1*/
#define SDL_JOYSTICK_DUMMY   1
#define SDL_JOYSTICK_VIRTUAL   1

/* Enable the stub haptic driver (src/haptic/dummy/\*.c) */
/*#define SDL_HAPTIC_DISABLED 1*/
#define SDL_HAPTIC_DUMMY 1

/* Enable the stub HIDAPI */
/*#define SDL_HIDAPI_DISABLED 1*/
#define SDL_HIDAPI_DUMMY 1

/* Enable the stub sensor driver (src/sensor/dummy/\*.c) */
/*#define SDL_SENSOR_DISABLED 1*/
#define SDL_SENSOR_DUMMY 1

/* Enable the stub shared object loader (src/loadso/dummy/\*.c) */
/*#define SDL_LOADSO_DISABLED 1*/
#define SDL_LOADSO_DUMMY 1

/* Enable the stub thread support (src/thread/generic/\*.c) */
#define SDL_THREADS_DISABLED    1

/* Enable the stub timer support (src/timer/dummy/\*.c) */
/*#define SDL_TIMERS_DISABLED 1*/
#define SDL_TIMER_DUMMY 1

/* Enable the dummy video driver (src/video/dummy/\*.c) */
/*#define SDL_VIDEO_DRIVER_DUMMY  1*/
#define SDL_VIDEO_DRIVER_AMIGAOS3  1

/* Enable OpenGL support */
#define SDL_VIDEO_OPENGL 1
#define SDL_VIDEO_RENDER_OGL 1

/* Enable the dummy filesystem driver (src/filesystem/dummy/\*.c) */
/*#define SDL_FILESYSTEM_DUMMY  1*/
#define SDL_FILESYSTEM_AMIGAOS3  1

#endif /* SDL_config_amigaos3_h_ */
