/* OPENSTEP 4.2 / NeXT cc-744.13 configuration bootstrap.
   This is intentionally limited to target-verified Phase 0/core facts. */
#ifndef SDL_config_openstep_h_
#define SDL_config_openstep_h_
#define SDL_config_h_

#define HAVE_SYS_TYPES_H 1
#define HAVE_STDIO_H 1
#define HAVE_STDARG_H 1
#define HAVE_STDDEF_H 1
#define HAVE_SYS_STAT_H 1
#define HAVE_STDLIB_H 1
#define HAVE_STRING_H 1
#define HAVE_STRINGS_H 1
#define HAVE_CTYPE_H 1
#define HAVE_MATH_H 1
#define HAVE_FLOAT_H 1
#define HAVE_MALLOC 1
#define HAVE_GETENV 1
#define STDC_HEADERS 1
#define SDL_DISABLE_ANALYZE_MACROS 1

/* OPENSTEP 4.2 has neither <stdint.h> nor <inttypes.h>, but its BSD system
   types provide signed intN_t and u_intN_t. */
#include <sys/types.h>
typedef u_int8_t uint8_t;
typedef u_int16_t uint16_t;
typedef u_int32_t uint32_t;
typedef u_int64_t uint64_t;
typedef signed int intptr_t;
typedef unsigned int uintptr_t;

/* OPENSTEP's <sys/stat.h> supplies the POSIX file-type bits but predates
   these convenient predicates, which SDL_RWops uses for safe file handling. */
#ifndef S_ISREG
#define S_ISREG(mode) (((mode) & S_IFMT) == S_IFREG)
#endif
#ifndef S_ISFIFO
#define S_ISFIFO(mode) (((mode) & S_IFMT) == S_IFIFO)
#endif

/* Phase 0 proved that __sync builtins and __thread cannot be used. */
#define SDL_OPENSTEP_CTHREAD_ATOMICS 1
#define SDL_OPENSTEP_CTHREAD_TLS 1
#define SDL_THREAD_OPENSTEP 1
#define SDL_VIDEO_DRIVER_OPENSTEP 1
/* Mesa 3.4.2 supplies the target-verified, statically linked OpenGL 1.2
   OSMesa implementation used by the native video backend. */
#define SDL_VIDEO_OPENGL 1
/* Upstream dummy audio remains an explicit standard fallback while the
   SoundKit driver is brought up as the normal OPENSTEP backend. */
#define SDL_AUDIO_DRIVER_OPENSTEP 1
#define SDL_AUDIO_DRIVER_DUMMY 1
/* Preserve the public sensor API with the upstream no-device driver. */
#define SDL_SENSOR_DUMMY 1

/* GCC 2.7 cpp does not accept an empty macro argument. The video-core
   overlay supplies this nonempty token where upstream uses `..., )`; it
   expands back to an empty return expression. */
#define SDL_OPENSTEP_VOID_RETURN

/* Keep every standard input API available. Until an OPENSTEP device driver is
   added, use SDL's upstream no-device implementations instead of compiling
   the joystick/haptic subsystems out. */
#define SDL_HIDAPI_DISABLED 1
#define SDL_HAPTIC_DUMMY 1
#define SDL_JOYSTICK_DUMMY 1
/* SDL's upstream dummy implementations retain these public APIs and return
   SDL_Unsupported() where OPENSTEP 4.2 lacks the host facility. */
#define SDL_LOADSO_DUMMY 1
#define SDL_FILESYSTEM_DUMMY 1
#define SDL_LOCALE_DUMMY 1
/* OPENSTEP does not have a verified URL-launch service yet. Keep SDL_OpenURL
   in the ABI with SDL's upstream standard unsupported fallback. */
#define SDL_MISC_DUMMY 1
/* There is no upstream power dummy; its generic public implementation returns
   SDL_POWERSTATE_UNKNOWN with -1 fields when platform probes are disabled. */
#define SDL_POWER_DISABLED 1

#endif
