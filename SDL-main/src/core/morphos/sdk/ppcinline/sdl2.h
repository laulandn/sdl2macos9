/* Automatically generated header! Do not edit! */

#ifndef _PPCINLINE_SDL2_H
#define _PPCINLINE_SDL2_H

#ifndef __PPCINLINE_MACROS_H
#include <ppcinline/macros.h>
#endif /* !__PPCINLINE_MACROS_H */

#ifndef SDL2_BASE_NAME
#define SDL2_BASE_NAME SDL2Base
#endif /* !SDL2_BASE_NAME */

#define SDL_InitTGL(__p0, __p1) \
	(((void (*)(void *, void **, struct Library **))*(void**)((long)(SDL2_BASE_NAME) - 28))((void*)(SDL2_BASE_NAME), __p0, __p1))

#define SDL_InitTGL2(__p0, __p1, __p2) \
	(((void (*)(void *, void **, struct Library **, unsigned int (*)(struct Library *TinyGLBase)))*(void**)((long)(SDL2_BASE_NAME) - 4816))((void*)(SDL2_BASE_NAME), __p0, __p1, __p2))

#define SDL_SetExitPointer(__p0) \
	(((void (*)(void *, void (*)(int)))*(void**)((long)(SDL2_BASE_NAME) - 34))((void*)(SDL2_BASE_NAME), __p0))

#define SDL_RWFromFP_clib(__p0, __p1, __p2, __p3, __p4, __p5, __p6) \
	({ \
		void * __t__p0 = __p0;\
		int  __t__p1 = __p1;\
		Sint64 (* __t__p2)(struct SDL_RWops *) = __p2;\
		Sint64 (* __t__p3)(struct SDL_RWops *, Sint64, int) = __p3;\
		size_t (* __t__p4)(struct SDL_RWops *, void *, size_t, size_t) = __p4;\
		size_t (* __t__p5)(struct SDL_RWops *, const void *, size_t, size_t) = __p5;\
		int (* __t__p6)(struct SDL_RWops *) = __p6;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_RWops *(*)(void *, int , Sint64 (*)(struct SDL_RWops *), Sint64 (*)(struct SDL_RWops *, Sint64, int), size_t (*)(struct SDL_RWops *, void *, size_t, size_t), size_t (*)(struct SDL_RWops *, const void *, size_t, size_t), int (*)(struct SDL_RWops *)))*(void**)(__base - 1762))(__t__p0, __t__p1, __t__p2, __t__p3, __t__p4, __t__p5, __t__p6));\
	})

#define SDL_VSetError(__p0, __p1) \
	({ \
		const char * __t__p0 = __p0;\
		va_list __t__p1;\
		va_copy(__t__p1, __p1);\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(const char *, va_list ))*(void**)(__base - 40))(__t__p0, __t__p1));\
	})

#define SDL_GetPlatform() \
	({ \
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((const char *(*)(void))*(void**)(__base - 46))());\
	})

#define SDL_Init(__p0) \
	({ \
		Uint32  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(Uint32 ))*(void**)(__base - 52))(__t__p0));\
	})

#define SDL_InitSubSystem(__p0) \
	({ \
		Uint32  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(Uint32 ))*(void**)(__base - 58))(__t__p0));\
	})

#define SDL_QuitSubSystem(__p0) \
	({ \
		Uint32  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(Uint32 ))*(void**)(__base - 64))(__t__p0));\
	})

#define SDL_WasInit(__p0) \
	({ \
		Uint32  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((Uint32 (*)(Uint32 ))*(void**)(__base - 70))(__t__p0));\
	})

#define SDL_Quit() \
	({ \
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(void))*(void**)(__base - 76))());\
	})

#define SDL_SetMainReady() \
	({ \
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(void))*(void**)(__base - 82))());\
	})

#define SDL_malloc(__p0) \
	({ \
		size_t  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void *(*)(size_t ))*(void**)(__base - 88))(__t__p0));\
	})

#define SDL_calloc(__p0, __p1) \
	({ \
		size_t  __t__p0 = __p0;\
		size_t  __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void *(*)(size_t , size_t ))*(void**)(__base - 94))(__t__p0, __t__p1));\
	})

#define SDL_realloc(__p0, __p1) \
	({ \
		void * __t__p0 = __p0;\
		size_t  __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void *(*)(void *, size_t ))*(void**)(__base - 100))(__t__p0, __t__p1));\
	})

#define SDL_free(__p0) \
	({ \
		void * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(void *))*(void**)(__base - 106))(__t__p0));\
	})

#define SDL_qsort(__p0, __p1, __p2, __p3) \
	({ \
		void * __t__p0 = __p0;\
		size_t  __t__p1 = __p1;\
		size_t  __t__p2 = __p2;\
		SDL_CompareCallback  __t__p3 = __p3;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(void *, size_t , size_t , SDL_CompareCallback ))*(void**)(__base - 112))(__t__p0, __t__p1, __t__p2, __t__p3));\
	})

#define SDL_abs(__p0) \
	({ \
		int  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(int ))*(void**)(__base - 118))(__t__p0));\
	})

#define SDL_isdigit(__p0) \
	({ \
		int  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(int ))*(void**)(__base - 124))(__t__p0));\
	})

#define SDL_isspace(__p0) \
	({ \
		int  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(int ))*(void**)(__base - 130))(__t__p0));\
	})

#define SDL_toupper(__p0) \
	({ \
		int  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(int ))*(void**)(__base - 136))(__t__p0));\
	})

#define SDL_tolower(__p0) \
	({ \
		int  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(int ))*(void**)(__base - 142))(__t__p0));\
	})

#define SDL_memset(__p0, __p1, __p2) \
	({ \
		void * __t__p0 = __p0;\
		int  __t__p1 = __p1;\
		size_t  __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void *(*)(void *, int , size_t ))*(void**)(__base - 148))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_memcpy(__p0, __p1, __p2) \
	({ \
		void * __t__p0 = __p0;\
		const void * __t__p1 = __p1;\
		size_t  __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void *(*)(void *, const void *, size_t ))*(void**)(__base - 154))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_memmove(__p0, __p1, __p2) \
	({ \
		void * __t__p0 = __p0;\
		const void * __t__p1 = __p1;\
		size_t  __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void *(*)(void *, const void *, size_t ))*(void**)(__base - 160))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_memcmp(__p0, __p1, __p2) \
	({ \
		const void * __t__p0 = __p0;\
		const void * __t__p1 = __p1;\
		size_t  __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(const void *, const void *, size_t ))*(void**)(__base - 166))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_wcslen(__p0) \
	({ \
		const wchar_t * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((size_t (*)(const wchar_t *))*(void**)(__base - 172))(__t__p0));\
	})

#define SDL_wcslcpy(__p0, __p1, __p2) \
	({ \
		wchar_t * __t__p0 = __p0;\
		const wchar_t * __t__p1 = __p1;\
		size_t  __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((size_t (*)(wchar_t *, const wchar_t *, size_t ))*(void**)(__base - 178))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_wcslcat(__p0, __p1, __p2) \
	({ \
		wchar_t * __t__p0 = __p0;\
		const wchar_t * __t__p1 = __p1;\
		size_t  __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((size_t (*)(wchar_t *, const wchar_t *, size_t ))*(void**)(__base - 184))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_strlen(__p0) \
	({ \
		const char * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((size_t (*)(const char *))*(void**)(__base - 190))(__t__p0));\
	})

#define SDL_strlcpy(__p0, __p1, __p2) \
	({ \
		char * __t__p0 = __p0;\
		const char * __t__p1 = __p1;\
		size_t  __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((size_t (*)(char *, const char *, size_t ))*(void**)(__base - 196))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_utf8strlcpy(__p0, __p1, __p2) \
	({ \
		char * __t__p0 = __p0;\
		const char * __t__p1 = __p1;\
		size_t  __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((size_t (*)(char *, const char *, size_t ))*(void**)(__base - 202))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_strlcat(__p0, __p1, __p2) \
	({ \
		char * __t__p0 = __p0;\
		const char * __t__p1 = __p1;\
		size_t  __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((size_t (*)(char *, const char *, size_t ))*(void**)(__base - 208))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_strdup(__p0) \
	({ \
		const char * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((char *(*)(const char *))*(void**)(__base - 214))(__t__p0));\
	})

#define SDL_strrev(__p0) \
	({ \
		char * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((char *(*)(char *))*(void**)(__base - 220))(__t__p0));\
	})

#define SDL_strupr(__p0) \
	({ \
		char * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((char *(*)(char *))*(void**)(__base - 226))(__t__p0));\
	})

#define SDL_strlwr(__p0) \
	({ \
		char * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((char *(*)(char *))*(void**)(__base - 232))(__t__p0));\
	})

#define SDL_strchr(__p0, __p1) \
	({ \
		const char * __t__p0 = __p0;\
		int  __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((char *(*)(const char *, int ))*(void**)(__base - 238))(__t__p0, __t__p1));\
	})

#define SDL_strrchr(__p0, __p1) \
	({ \
		const char * __t__p0 = __p0;\
		int  __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((char *(*)(const char *, int ))*(void**)(__base - 244))(__t__p0, __t__p1));\
	})

#define SDL_strstr(__p0, __p1) \
	({ \
		const char * __t__p0 = __p0;\
		const char * __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((char *(*)(const char *, const char *))*(void**)(__base - 250))(__t__p0, __t__p1));\
	})

#define SDL_itoa(__p0, __p1, __p2) \
	({ \
		int  __t__p0 = __p0;\
		char * __t__p1 = __p1;\
		int  __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((char *(*)(int , char *, int ))*(void**)(__base - 256))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_uitoa(__p0, __p1, __p2) \
	({ \
		unsigned int  __t__p0 = __p0;\
		char * __t__p1 = __p1;\
		int  __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((char *(*)(unsigned int , char *, int ))*(void**)(__base - 262))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_ltoa(__p0, __p1, __p2) \
	({ \
		long  __t__p0 = __p0;\
		char * __t__p1 = __p1;\
		int  __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((char *(*)(long , char *, int ))*(void**)(__base - 268))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_ultoa(__p0, __p1, __p2) \
	({ \
		unsigned long  __t__p0 = __p0;\
		char * __t__p1 = __p1;\
		int  __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((char *(*)(unsigned long , char *, int ))*(void**)(__base - 274))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_lltoa(__p0, __p1, __p2) \
	({ \
		Sint64  __t__p0 = __p0;\
		char * __t__p1 = __p1;\
		int  __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((char *(*)(Sint64 , char *, int ))*(void**)(__base - 280))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_ulltoa(__p0, __p1, __p2) \
	({ \
		Uint64  __t__p0 = __p0;\
		char * __t__p1 = __p1;\
		int  __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((char *(*)(Uint64 , char *, int ))*(void**)(__base - 286))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_atoi(__p0) \
	({ \
		const char * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(const char *))*(void**)(__base - 292))(__t__p0));\
	})

#define SDL_atof(__p0) \
	({ \
		const char * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((double (*)(const char *))*(void**)(__base - 298))(__t__p0));\
	})

#define SDL_strtol(__p0, __p1, __p2) \
	({ \
		const char * __t__p0 = __p0;\
		char ** __t__p1 = __p1;\
		int  __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((long (*)(const char *, char **, int ))*(void**)(__base - 304))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_strtoul(__p0, __p1, __p2) \
	({ \
		const char * __t__p0 = __p0;\
		char ** __t__p1 = __p1;\
		int  __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((unsigned long (*)(const char *, char **, int ))*(void**)(__base - 310))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_strtoll(__p0, __p1, __p2) \
	({ \
		const char * __t__p0 = __p0;\
		char ** __t__p1 = __p1;\
		int  __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((Sint64 (*)(const char *, char **, int ))*(void**)(__base - 316))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_strtoull(__p0, __p1, __p2) \
	({ \
		const char * __t__p0 = __p0;\
		char ** __t__p1 = __p1;\
		int  __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((Uint64 (*)(const char *, char **, int ))*(void**)(__base - 322))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_strtod(__p0, __p1) \
	({ \
		const char * __t__p0 = __p0;\
		char ** __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((double (*)(const char *, char **))*(void**)(__base - 328))(__t__p0, __t__p1));\
	})

#define SDL_strcmp(__p0, __p1) \
	({ \
		const char * __t__p0 = __p0;\
		const char * __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(const char *, const char *))*(void**)(__base - 334))(__t__p0, __t__p1));\
	})

#define SDL_strncmp(__p0, __p1, __p2) \
	({ \
		const char * __t__p0 = __p0;\
		const char * __t__p1 = __p1;\
		size_t  __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(const char *, const char *, size_t ))*(void**)(__base - 340))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_strcasecmp(__p0, __p1) \
	({ \
		const char * __t__p0 = __p0;\
		const char * __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(const char *, const char *))*(void**)(__base - 346))(__t__p0, __t__p1));\
	})

#define SDL_strncasecmp(__p0, __p1, __p2) \
	({ \
		const char * __t__p0 = __p0;\
		const char * __t__p1 = __p1;\
		size_t  __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(const char *, const char *, size_t ))*(void**)(__base - 352))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_vsscanf(__p0, __p1, __p2) \
	({ \
		const char * __t__p0 = __p0;\
		const char * __t__p1 = __p1;\
		va_list __t__p2;\
		va_copy(__t__p2, __p2);\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(const char *, const char *, va_list ))*(void**)(__base - 358))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_vsnprintf(__p0, __p1, __p2, __p3) \
	({ \
		char * __t__p0 = __p0;\
		size_t  __t__p1 = __p1;\
		const char * __t__p2 = __p2;\
		va_list __t__p3;\
		va_copy(__t__p3, __p3);\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(char *, size_t , const char *, va_list ))*(void**)(__base - 364))(__t__p0, __t__p1, __t__p2, __t__p3));\
	})

#define SDL_acos(__p0) \
	({ \
		double  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((double (*)(double ))*(void**)(__base - 370))(__t__p0));\
	})

#define SDL_asin(__p0) \
	({ \
		double  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((double (*)(double ))*(void**)(__base - 376))(__t__p0));\
	})

#define SDL_atan(__p0) \
	({ \
		double  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((double (*)(double ))*(void**)(__base - 382))(__t__p0));\
	})

#define SDL_atan2(__p0, __p1) \
	({ \
		double  __t__p0 = __p0;\
		double  __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((double (*)(double , double ))*(void**)(__base - 388))(__t__p0, __t__p1));\
	})

#define SDL_ceil(__p0) \
	({ \
		double  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((double (*)(double ))*(void**)(__base - 394))(__t__p0));\
	})

#define SDL_copysign(__p0, __p1) \
	({ \
		double  __t__p0 = __p0;\
		double  __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((double (*)(double , double ))*(void**)(__base - 400))(__t__p0, __t__p1));\
	})

#define SDL_cos(__p0) \
	({ \
		double  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((double (*)(double ))*(void**)(__base - 406))(__t__p0));\
	})

#define SDL_cosf(__p0) \
	({ \
		float  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((float (*)(float ))*(void**)(__base - 412))(__t__p0));\
	})

#define SDL_fabs(__p0) \
	({ \
		double  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((double (*)(double ))*(void**)(__base - 418))(__t__p0));\
	})

#define SDL_floor(__p0) \
	({ \
		double  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((double (*)(double ))*(void**)(__base - 424))(__t__p0));\
	})

#define SDL_log(__p0) \
	({ \
		double  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((double (*)(double ))*(void**)(__base - 430))(__t__p0));\
	})

#define SDL_pow(__p0, __p1) \
	({ \
		double  __t__p0 = __p0;\
		double  __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((double (*)(double , double ))*(void**)(__base - 436))(__t__p0, __t__p1));\
	})

#define SDL_scalbn(__p0, __p1) \
	({ \
		double  __t__p0 = __p0;\
		int  __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((double (*)(double , int ))*(void**)(__base - 442))(__t__p0, __t__p1));\
	})

#define SDL_sin(__p0) \
	({ \
		double  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((double (*)(double ))*(void**)(__base - 448))(__t__p0));\
	})

#define SDL_sinf(__p0) \
	({ \
		float  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((float (*)(float ))*(void**)(__base - 454))(__t__p0));\
	})

#define SDL_sqrt(__p0) \
	({ \
		double  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((double (*)(double ))*(void**)(__base - 460))(__t__p0));\
	})

#define SDL_iconv_open(__p0, __p1) \
	({ \
		const char * __t__p0 = __p0;\
		const char * __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_iconv_t (*)(const char *, const char *))*(void**)(__base - 466))(__t__p0, __t__p1));\
	})

#define SDL_iconv_close(__p0) \
	({ \
		SDL_iconv_t  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_iconv_t ))*(void**)(__base - 472))(__t__p0));\
	})

#define SDL_iconv(__p0, __p1, __p2, __p3, __p4) \
	({ \
		SDL_iconv_t  __t__p0 = __p0;\
		const char ** __t__p1 = __p1;\
		size_t * __t__p2 = __p2;\
		char ** __t__p3 = __p3;\
		size_t * __t__p4 = __p4;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((size_t (*)(SDL_iconv_t , const char **, size_t *, char **, size_t *))*(void**)(__base - 478))(__t__p0, __t__p1, __t__p2, __t__p3, __t__p4));\
	})

#define SDL_iconv_string(__p0, __p1, __p2, __p3) \
	({ \
		const char * __t__p0 = __p0;\
		const char * __t__p1 = __p1;\
		const char * __t__p2 = __p2;\
		size_t  __t__p3 = __p3;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((char *(*)(const char *, const char *, const char *, size_t ))*(void**)(__base - 484))(__t__p0, __t__p1, __t__p2, __t__p3));\
	})

#define SDL_ReportAssertion(__p0, __p1, __p2, __p3) \
	({ \
		SDL_AssertData * __t__p0 = __p0;\
		const char * __t__p1 = __p1;\
		const char * __t__p2 = __p2;\
		int  __t__p3 = __p3;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_AssertData (*)(SDL_AssertData *, const char *, const char *, int ))*(void**)(__base - 490))(__t__p0, __t__p1, __t__p2, __t__p3));\
	})

#define SDL_SetAssertionHandler(__p0, __p1) \
	({ \
		SDL_AssertionHandler  __t__p0 = __p0;\
		void * __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(SDL_AssertionHandler , void *))*(void**)(__base - 496))(__t__p0, __t__p1));\
	})

#define SDL_GetDefaultAssertionHandler() \
	({ \
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_AssertionHandler (*)(void))*(void**)(__base - 502))());\
	})

#define SDL_GetAssertionHandler(__p0) \
	({ \
		void ** __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_AssertionHandler (*)(void **))*(void**)(__base - 508))(__t__p0));\
	})

#define SDL_GetAssertionReport() \
	({ \
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((const SDL_AssertData *(*)(void))*(void**)(__base - 514))());\
	})

#define SDL_ResetAssertionReport() \
	({ \
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(void))*(void**)(__base - 520))());\
	})

#define SDL_AtomicTryLock(__p0) \
	({ \
		SDL_SpinLock * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_bool (*)(SDL_SpinLock *))*(void**)(__base - 526))(__t__p0));\
	})

#define SDL_AtomicLock(__p0) \
	({ \
		SDL_SpinLock * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(SDL_SpinLock *))*(void**)(__base - 532))(__t__p0));\
	})

#define SDL_AtomicUnlock(__p0) \
	({ \
		SDL_SpinLock * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(SDL_SpinLock *))*(void**)(__base - 538))(__t__p0));\
	})

#define SDL_AtomicCAS(__p0, __p1, __p2) \
	({ \
		SDL_atomic_t * __t__p0 = __p0;\
		int  __t__p1 = __p1;\
		int  __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_bool (*)(SDL_atomic_t *, int , int ))*(void**)(__base - 544))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_AtomicSet(__p0, __p1) \
	({ \
		SDL_atomic_t * __t__p0 = __p0;\
		int  __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_atomic_t *, int ))*(void**)(__base - 550))(__t__p0, __t__p1));\
	})

#define SDL_AtomicGet(__p0) \
	({ \
		SDL_atomic_t * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_atomic_t *))*(void**)(__base - 556))(__t__p0));\
	})

#define SDL_AtomicAdd(__p0, __p1) \
	({ \
		SDL_atomic_t * __t__p0 = __p0;\
		int  __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_atomic_t *, int ))*(void**)(__base - 562))(__t__p0, __t__p1));\
	})

#define SDL_AtomicCASPtr(__p0, __p1, __p2) \
	({ \
		void ** __t__p0 = __p0;\
		void * __t__p1 = __p1;\
		void * __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_bool (*)(void **, void *, void *))*(void**)(__base - 568))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_AtomicSetPtr(__p0, __p1) \
	({ \
		void ** __t__p0 = __p0;\
		void * __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void *(*)(void **, void *))*(void**)(__base - 574))(__t__p0, __t__p1));\
	})

#define SDL_AtomicGetPtr(__p0) \
	({ \
		void ** __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void *(*)(void **))*(void**)(__base - 580))(__t__p0));\
	})

#define SDL_GetNumAudioDrivers() \
	({ \
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(void))*(void**)(__base - 586))());\
	})

#define SDL_GetAudioDriver(__p0) \
	({ \
		int  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((const char *(*)(int ))*(void**)(__base - 592))(__t__p0));\
	})

#define SDL_AudioInit(__p0) \
	({ \
		const char * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(const char *))*(void**)(__base - 598))(__t__p0));\
	})

#define SDL_AudioQuit() \
	({ \
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(void))*(void**)(__base - 604))());\
	})

#define SDL_GetCurrentAudioDriver() \
	({ \
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((const char *(*)(void))*(void**)(__base - 610))());\
	})

#define SDL_OpenAudio(__p0, __p1) \
	({ \
		SDL_AudioSpec * __t__p0 = __p0;\
		SDL_AudioSpec * __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_AudioSpec *, SDL_AudioSpec *))*(void**)(__base - 616))(__t__p0, __t__p1));\
	})

#define SDL_GetNumAudioDevices(__p0) \
	({ \
		int  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(int ))*(void**)(__base - 622))(__t__p0));\
	})

#define SDL_GetAudioDeviceName(__p0, __p1) \
	({ \
		int  __t__p0 = __p0;\
		int  __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((const char *(*)(int , int ))*(void**)(__base - 628))(__t__p0, __t__p1));\
	})

#define SDL_OpenAudioDevice(__p0, __p1, __p2, __p3, __p4) \
	({ \
		const char * __t__p0 = __p0;\
		int  __t__p1 = __p1;\
		const SDL_AudioSpec * __t__p2 = __p2;\
		SDL_AudioSpec * __t__p3 = __p3;\
		int  __t__p4 = __p4;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_AudioDeviceID (*)(const char *, int , const SDL_AudioSpec *, SDL_AudioSpec *, int ))*(void**)(__base - 634))(__t__p0, __t__p1, __t__p2, __t__p3, __t__p4));\
	})

#define SDL_GetAudioStatus() \
	({ \
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_AudioStatus (*)(void))*(void**)(__base - 640))());\
	})

#define SDL_GetAudioDeviceStatus(__p0) \
	({ \
		SDL_AudioDeviceID  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_AudioStatus (*)(SDL_AudioDeviceID ))*(void**)(__base - 646))(__t__p0));\
	})

#define SDL_PauseAudio(__p0) \
	({ \
		int  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(int ))*(void**)(__base - 652))(__t__p0));\
	})

#define SDL_PauseAudioDevice(__p0, __p1) \
	({ \
		SDL_AudioDeviceID  __t__p0 = __p0;\
		int  __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(SDL_AudioDeviceID , int ))*(void**)(__base - 658))(__t__p0, __t__p1));\
	})

#define SDL_LoadWAV_RW(__p0, __p1, __p2, __p3, __p4) \
	({ \
		SDL_RWops * __t__p0 = __p0;\
		int  __t__p1 = __p1;\
		SDL_AudioSpec * __t__p2 = __p2;\
		Uint8 ** __t__p3 = __p3;\
		Uint32 * __t__p4 = __p4;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_AudioSpec *(*)(SDL_RWops *, int , SDL_AudioSpec *, Uint8 **, Uint32 *))*(void**)(__base - 664))(__t__p0, __t__p1, __t__p2, __t__p3, __t__p4));\
	})

#define SDL_FreeWAV(__p0) \
	({ \
		Uint8 * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(Uint8 *))*(void**)(__base - 670))(__t__p0));\
	})

#define SDL_BuildAudioCVT(__p0, __p1, __p2, __p3, __p4, __p5, __p6) \
	({ \
		SDL_AudioCVT * __t__p0 = __p0;\
		SDL_AudioFormat  __t__p1 = __p1;\
		Uint8  __t__p2 = __p2;\
		int  __t__p3 = __p3;\
		SDL_AudioFormat  __t__p4 = __p4;\
		Uint8  __t__p5 = __p5;\
		int  __t__p6 = __p6;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_AudioCVT *, SDL_AudioFormat , Uint8 , int , SDL_AudioFormat , Uint8 , int ))*(void**)(__base - 676))(__t__p0, __t__p1, __t__p2, __t__p3, __t__p4, __t__p5, __t__p6));\
	})

#define SDL_ConvertAudio(__p0) \
	({ \
		SDL_AudioCVT * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_AudioCVT *))*(void**)(__base - 682))(__t__p0));\
	})

#define SDL_MixAudio(__p0, __p1, __p2, __p3) \
	({ \
		Uint8 * __t__p0 = __p0;\
		const Uint8 * __t__p1 = __p1;\
		Uint32  __t__p2 = __p2;\
		int  __t__p3 = __p3;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(Uint8 *, const Uint8 *, Uint32 , int ))*(void**)(__base - 688))(__t__p0, __t__p1, __t__p2, __t__p3));\
	})

#define SDL_MixAudioFormat(__p0, __p1, __p2, __p3, __p4) \
	({ \
		Uint8 * __t__p0 = __p0;\
		const Uint8 * __t__p1 = __p1;\
		SDL_AudioFormat  __t__p2 = __p2;\
		Uint32  __t__p3 = __p3;\
		int  __t__p4 = __p4;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(Uint8 *, const Uint8 *, SDL_AudioFormat , Uint32 , int ))*(void**)(__base - 694))(__t__p0, __t__p1, __t__p2, __t__p3, __t__p4));\
	})

#define SDL_LockAudio() \
	({ \
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(void))*(void**)(__base - 700))());\
	})

#define SDL_LockAudioDevice(__p0) \
	({ \
		SDL_AudioDeviceID  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(SDL_AudioDeviceID ))*(void**)(__base - 706))(__t__p0));\
	})

#define SDL_UnlockAudio() \
	({ \
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(void))*(void**)(__base - 712))());\
	})

#define SDL_UnlockAudioDevice(__p0) \
	({ \
		SDL_AudioDeviceID  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(SDL_AudioDeviceID ))*(void**)(__base - 718))(__t__p0));\
	})

#define SDL_CloseAudio() \
	({ \
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(void))*(void**)(__base - 724))());\
	})

#define SDL_CloseAudioDevice(__p0) \
	({ \
		SDL_AudioDeviceID  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(SDL_AudioDeviceID ))*(void**)(__base - 730))(__t__p0));\
	})

#define SDL_SetClipboardText(__p0) \
	({ \
		const char * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(const char *))*(void**)(__base - 736))(__t__p0));\
	})

#define SDL_GetClipboardText() \
	({ \
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((char *(*)(void))*(void**)(__base - 742))());\
	})

#define SDL_HasClipboardText() \
	({ \
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_bool (*)(void))*(void**)(__base - 748))());\
	})

#define SDL_GetCPUCount() \
	({ \
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(void))*(void**)(__base - 754))());\
	})

#define SDL_GetCPUCacheLineSize() \
	({ \
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(void))*(void**)(__base - 760))());\
	})

#define SDL_HasRDTSC() \
	({ \
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_bool (*)(void))*(void**)(__base - 766))());\
	})

#define SDL_HasAltiVec() \
	({ \
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_bool (*)(void))*(void**)(__base - 772))());\
	})

#define SDL_HasMMX() \
	({ \
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_bool (*)(void))*(void**)(__base - 778))());\
	})

#define SDL_Has3DNow() \
	({ \
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_bool (*)(void))*(void**)(__base - 784))());\
	})

#define SDL_HasSSE() \
	({ \
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_bool (*)(void))*(void**)(__base - 790))());\
	})

#define SDL_HasSSE2() \
	({ \
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_bool (*)(void))*(void**)(__base - 796))());\
	})

#define SDL_HasSSE3() \
	({ \
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_bool (*)(void))*(void**)(__base - 802))());\
	})

#define SDL_HasSSE41() \
	({ \
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_bool (*)(void))*(void**)(__base - 808))());\
	})

#define SDL_HasSSE42() \
	({ \
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_bool (*)(void))*(void**)(__base - 814))());\
	})

#define SDL_HasAVX() \
	({ \
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_bool (*)(void))*(void**)(__base - 820))());\
	})

#define SDL_GetSystemRAM() \
	({ \
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(void))*(void**)(__base - 826))());\
	})

#define SDL_GetError() \
	({ \
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((const char *(*)(void))*(void**)(__base - 832))());\
	})

#define SDL_ClearError() \
	({ \
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(void))*(void**)(__base - 838))());\
	})

#define SDL_Error(__p0) \
	({ \
		SDL_errorcode  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_errorcode ))*(void**)(__base - 844))(__t__p0));\
	})

#define SDL_PumpEvents() \
	({ \
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(void))*(void**)(__base - 850))());\
	})

#define SDL_PeepEvents(__p0, __p1, __p2, __p3, __p4) \
	({ \
		SDL_Event * __t__p0 = __p0;\
		int  __t__p1 = __p1;\
		SDL_eventaction  __t__p2 = __p2;\
		Uint32  __t__p3 = __p3;\
		Uint32  __t__p4 = __p4;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Event *, int , SDL_eventaction , Uint32 , Uint32 ))*(void**)(__base - 856))(__t__p0, __t__p1, __t__p2, __t__p3, __t__p4));\
	})

#define SDL_HasEvent(__p0) \
	({ \
		Uint32  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_bool (*)(Uint32 ))*(void**)(__base - 862))(__t__p0));\
	})

#define SDL_HasEvents(__p0, __p1) \
	({ \
		Uint32  __t__p0 = __p0;\
		Uint32  __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_bool (*)(Uint32 , Uint32 ))*(void**)(__base - 868))(__t__p0, __t__p1));\
	})

#define SDL_FlushEvent(__p0) \
	({ \
		Uint32  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(Uint32 ))*(void**)(__base - 874))(__t__p0));\
	})

#define SDL_FlushEvents(__p0, __p1) \
	({ \
		Uint32  __t__p0 = __p0;\
		Uint32  __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(Uint32 , Uint32 ))*(void**)(__base - 880))(__t__p0, __t__p1));\
	})

#define SDL_PollEvent(__p0) \
	({ \
		SDL_Event * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Event *))*(void**)(__base - 886))(__t__p0));\
	})

#define SDL_WaitEvent(__p0) \
	({ \
		SDL_Event * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Event *))*(void**)(__base - 892))(__t__p0));\
	})

#define SDL_WaitEventTimeout(__p0, __p1) \
	({ \
		SDL_Event * __t__p0 = __p0;\
		int  __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Event *, int ))*(void**)(__base - 898))(__t__p0, __t__p1));\
	})

#define SDL_PushEvent(__p0) \
	({ \
		SDL_Event * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Event *))*(void**)(__base - 904))(__t__p0));\
	})

#define SDL_SetEventFilter(__p0, __p1) \
	({ \
		SDL_EventFilter  __t__p0 = __p0;\
		void * __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(SDL_EventFilter , void *))*(void**)(__base - 910))(__t__p0, __t__p1));\
	})

#define SDL_GetEventFilter(__p0, __p1) \
	({ \
		SDL_EventFilter * __t__p0 = __p0;\
		void ** __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_bool (*)(SDL_EventFilter *, void **))*(void**)(__base - 916))(__t__p0, __t__p1));\
	})

#define SDL_AddEventWatch(__p0, __p1) \
	({ \
		SDL_EventFilter  __t__p0 = __p0;\
		void * __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(SDL_EventFilter , void *))*(void**)(__base - 922))(__t__p0, __t__p1));\
	})

#define SDL_DelEventWatch(__p0, __p1) \
	({ \
		SDL_EventFilter  __t__p0 = __p0;\
		void * __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(SDL_EventFilter , void *))*(void**)(__base - 928))(__t__p0, __t__p1));\
	})

#define SDL_FilterEvents(__p0, __p1) \
	({ \
		SDL_EventFilter  __t__p0 = __p0;\
		void * __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(SDL_EventFilter , void *))*(void**)(__base - 934))(__t__p0, __t__p1));\
	})

#define SDL_EventState(__p0, __p1) \
	({ \
		Uint32  __t__p0 = __p0;\
		int  __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((Uint8 (*)(Uint32 , int ))*(void**)(__base - 940))(__t__p0, __t__p1));\
	})

#define SDL_RegisterEvents(__p0) \
	({ \
		int  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((Uint32 (*)(int ))*(void**)(__base - 946))(__t__p0));\
	})

#define SDL_GetBasePath() \
	({ \
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((char *(*)(void))*(void**)(__base - 952))());\
	})

#define SDL_GetPrefPath(__p0, __p1) \
	({ \
		const char * __t__p0 = __p0;\
		const char * __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((char *(*)(const char *, const char *))*(void**)(__base - 958))(__t__p0, __t__p1));\
	})

#define SDL_NumJoysticks() \
	({ \
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(void))*(void**)(__base - 964))());\
	})

#define SDL_JoystickNameForIndex(__p0) \
	({ \
		int  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((const char *(*)(int ))*(void**)(__base - 970))(__t__p0));\
	})

#define SDL_JoystickOpen(__p0) \
	({ \
		int  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_Joystick *(*)(int ))*(void**)(__base - 976))(__t__p0));\
	})

#define SDL_JoystickName(__p0) \
	({ \
		SDL_Joystick * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((const char *(*)(SDL_Joystick *))*(void**)(__base - 982))(__t__p0));\
	})

#define SDL_JoystickGetDeviceGUID(__p0) \
	({ \
		int  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_JoystickGUID (*)(int ))*(void**)(__base - 988))(__t__p0));\
	})

#define SDL_JoystickGetGUID(__p0) \
	({ \
		SDL_Joystick * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_JoystickGUID (*)(SDL_Joystick *))*(void**)(__base - 994))(__t__p0));\
	})

#define SDL_JoystickGetGUIDString(__p0, __p1, __p2) \
	({ \
		SDL_JoystickGUID  __t__p0 = __p0;\
		char * __t__p1 = __p1;\
		int  __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(SDL_JoystickGUID , char *, int ))*(void**)(__base - 1000))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_JoystickGetGUIDFromString(__p0) \
	({ \
		const char * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_JoystickGUID (*)(const char *))*(void**)(__base - 1006))(__t__p0));\
	})

#define SDL_JoystickGetAttached(__p0) \
	({ \
		SDL_Joystick * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_bool (*)(SDL_Joystick *))*(void**)(__base - 1012))(__t__p0));\
	})

#define SDL_JoystickInstanceID(__p0) \
	({ \
		SDL_Joystick * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_JoystickID (*)(SDL_Joystick *))*(void**)(__base - 1018))(__t__p0));\
	})

#define SDL_JoystickNumAxes(__p0) \
	({ \
		SDL_Joystick * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Joystick *))*(void**)(__base - 1024))(__t__p0));\
	})

#define SDL_JoystickNumBalls(__p0) \
	({ \
		SDL_Joystick * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Joystick *))*(void**)(__base - 1030))(__t__p0));\
	})

#define SDL_JoystickNumHats(__p0) \
	({ \
		SDL_Joystick * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Joystick *))*(void**)(__base - 1036))(__t__p0));\
	})

#define SDL_JoystickNumButtons(__p0) \
	({ \
		SDL_Joystick * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Joystick *))*(void**)(__base - 1042))(__t__p0));\
	})

#define SDL_JoystickUpdate() \
	({ \
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(void))*(void**)(__base - 1048))());\
	})

#define SDL_JoystickEventState(__p0) \
	({ \
		int  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(int ))*(void**)(__base - 1054))(__t__p0));\
	})

#define SDL_JoystickGetAxis(__p0, __p1) \
	({ \
		SDL_Joystick * __t__p0 = __p0;\
		int  __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((Sint16 (*)(SDL_Joystick *, int ))*(void**)(__base - 1060))(__t__p0, __t__p1));\
	})

#define SDL_JoystickGetHat(__p0, __p1) \
	({ \
		SDL_Joystick * __t__p0 = __p0;\
		int  __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((Uint8 (*)(SDL_Joystick *, int ))*(void**)(__base - 1066))(__t__p0, __t__p1));\
	})

#define SDL_JoystickGetBall(__p0, __p1, __p2, __p3) \
	({ \
		SDL_Joystick * __t__p0 = __p0;\
		int  __t__p1 = __p1;\
		int * __t__p2 = __p2;\
		int * __t__p3 = __p3;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Joystick *, int , int *, int *))*(void**)(__base - 1072))(__t__p0, __t__p1, __t__p2, __t__p3));\
	})

#define SDL_JoystickGetButton(__p0, __p1) \
	({ \
		SDL_Joystick * __t__p0 = __p0;\
		int  __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((Uint8 (*)(SDL_Joystick *, int ))*(void**)(__base - 1078))(__t__p0, __t__p1));\
	})

#define SDL_JoystickClose(__p0) \
	({ \
		SDL_Joystick * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(SDL_Joystick *))*(void**)(__base - 1084))(__t__p0));\
	})

#define SDL_GameControllerAddMappingsFromRW(__p0, __p1) \
	({ \
		SDL_RWops * __t__p0 = __p0;\
		int  __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_RWops *, int ))*(void**)(__base - 1090))(__t__p0, __t__p1));\
	})

#define SDL_GameControllerAddMapping(__p0) \
	({ \
		const char * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(const char *))*(void**)(__base - 1096))(__t__p0));\
	})

#define SDL_GameControllerMappingForGUID(__p0) \
	({ \
		SDL_JoystickGUID  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((char *(*)(SDL_JoystickGUID ))*(void**)(__base - 1102))(__t__p0));\
	})

#define SDL_GameControllerMapping(__p0) \
	({ \
		SDL_GameController * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((char *(*)(SDL_GameController *))*(void**)(__base - 1108))(__t__p0));\
	})

#define SDL_IsGameController(__p0) \
	({ \
		int  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_bool (*)(int ))*(void**)(__base - 1114))(__t__p0));\
	})

#define SDL_GameControllerNameForIndex(__p0) \
	({ \
		int  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((const char *(*)(int ))*(void**)(__base - 1120))(__t__p0));\
	})

#define SDL_GameControllerOpen(__p0) \
	({ \
		int  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_GameController *(*)(int ))*(void**)(__base - 1126))(__t__p0));\
	})

#define SDL_GameControllerName(__p0) \
	({ \
		SDL_GameController * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((const char *(*)(SDL_GameController *))*(void**)(__base - 1132))(__t__p0));\
	})

#define SDL_GameControllerGetAttached(__p0) \
	({ \
		SDL_GameController * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_bool (*)(SDL_GameController *))*(void**)(__base - 1138))(__t__p0));\
	})

#define SDL_GameControllerGetJoystick(__p0) \
	({ \
		SDL_GameController * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_Joystick *(*)(SDL_GameController *))*(void**)(__base - 1144))(__t__p0));\
	})

#define SDL_GameControllerEventState(__p0) \
	({ \
		int  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(int ))*(void**)(__base - 1150))(__t__p0));\
	})

#define SDL_GameControllerUpdate() \
	({ \
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(void))*(void**)(__base - 1156))());\
	})

#define SDL_GameControllerGetAxisFromString(__p0) \
	({ \
		const char * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_GameControllerAxis (*)(const char *))*(void**)(__base - 1162))(__t__p0));\
	})

#define SDL_GameControllerGetStringForAxis(__p0) \
	({ \
		SDL_GameControllerAxis  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((const char *(*)(SDL_GameControllerAxis ))*(void**)(__base - 1168))(__t__p0));\
	})

#define SDL_GameControllerGetBindForAxis(__p0, __p1) \
	({ \
		SDL_GameController * __t__p0 = __p0;\
		SDL_GameControllerAxis  __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_GameControllerButtonBind (*)(SDL_GameController *, SDL_GameControllerAxis ))*(void**)(__base - 1174))(__t__p0, __t__p1));\
	})

#define SDL_GameControllerGetAxis(__p0, __p1) \
	({ \
		SDL_GameController * __t__p0 = __p0;\
		SDL_GameControllerAxis  __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((Sint16 (*)(SDL_GameController *, SDL_GameControllerAxis ))*(void**)(__base - 1180))(__t__p0, __t__p1));\
	})

#define SDL_GameControllerGetButtonFromString(__p0) \
	({ \
		const char * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_GameControllerButton (*)(const char *))*(void**)(__base - 1186))(__t__p0));\
	})

#define SDL_GameControllerGetStringForButton(__p0) \
	({ \
		SDL_GameControllerButton  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((const char *(*)(SDL_GameControllerButton ))*(void**)(__base - 1192))(__t__p0));\
	})

#define SDL_GameControllerGetBindForButton(__p0, __p1) \
	({ \
		SDL_GameController * __t__p0 = __p0;\
		SDL_GameControllerButton  __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_GameControllerButtonBind (*)(SDL_GameController *, SDL_GameControllerButton ))*(void**)(__base - 1198))(__t__p0, __t__p1));\
	})

#define SDL_GameControllerGetButton(__p0, __p1) \
	({ \
		SDL_GameController * __t__p0 = __p0;\
		SDL_GameControllerButton  __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((Uint8 (*)(SDL_GameController *, SDL_GameControllerButton ))*(void**)(__base - 1204))(__t__p0, __t__p1));\
	})

#define SDL_GameControllerClose(__p0) \
	({ \
		SDL_GameController * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(SDL_GameController *))*(void**)(__base - 1210))(__t__p0));\
	})

#define SDL_NumHaptics() \
	({ \
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(void))*(void**)(__base - 3748))());\
	})

#define SDL_HapticName(__p0) \
	({ \
		int  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((const char *(*)(int ))*(void**)(__base - 3754))(__t__p0));\
	})

#define SDL_HapticOpen(__p0) \
	({ \
		int  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_Haptic *(*)(int ))*(void**)(__base - 3760))(__t__p0));\
	})

#define SDL_HapticOpened(__p0) \
	({ \
		int  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(int ))*(void**)(__base - 3766))(__t__p0));\
	})

#define SDL_HapticIndex(__p0) \
	({ \
		SDL_Haptic * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Haptic *))*(void**)(__base - 3772))(__t__p0));\
	})

#define SDL_MouseIsHaptic() \
	({ \
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(void))*(void**)(__base - 3778))());\
	})

#define SDL_HapticOpenFromMouse() \
	({ \
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_Haptic *(*)(void))*(void**)(__base - 3784))());\
	})

#define SDL_JoystickIsHaptic(__p0) \
	({ \
		SDL_Joystick * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Joystick *))*(void**)(__base - 3790))(__t__p0));\
	})

#define SDL_HapticOpenFromJoystick(__p0) \
	({ \
		SDL_Joystick * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_Haptic *(*)(SDL_Joystick *))*(void**)(__base - 3796))(__t__p0));\
	})

#define SDL_HapticClose(__p0) \
	({ \
		SDL_Haptic * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(SDL_Haptic *))*(void**)(__base - 3802))(__t__p0));\
	})

#define SDL_HapticNumEffects(__p0) \
	({ \
		SDL_Haptic * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Haptic *))*(void**)(__base - 3808))(__t__p0));\
	})

#define SDL_HapticNumEffectsPlaying(__p0) \
	({ \
		SDL_Haptic * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Haptic *))*(void**)(__base - 3814))(__t__p0));\
	})

#define SDL_HapticQuery(__p0) \
	({ \
		SDL_Haptic * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((unsigned int (*)(SDL_Haptic *))*(void**)(__base - 3820))(__t__p0));\
	})

#define SDL_HapticNumAxes(__p0) \
	({ \
		SDL_Haptic * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Haptic *))*(void**)(__base - 3826))(__t__p0));\
	})

#define SDL_HapticEffectSupported(__p0, __p1) \
	({ \
		SDL_Haptic * __t__p0 = __p0;\
		SDL_HapticEffect * __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Haptic *, SDL_HapticEffect *))*(void**)(__base - 3832))(__t__p0, __t__p1));\
	})

#define SDL_HapticNewEffect(__p0, __p1) \
	({ \
		SDL_Haptic * __t__p0 = __p0;\
		SDL_HapticEffect * __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Haptic *, SDL_HapticEffect *))*(void**)(__base - 3838))(__t__p0, __t__p1));\
	})

#define SDL_HapticUpdateEffect(__p0, __p1, __p2) \
	({ \
		SDL_Haptic * __t__p0 = __p0;\
		int  __t__p1 = __p1;\
		SDL_HapticEffect * __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Haptic *, int , SDL_HapticEffect *))*(void**)(__base - 3844))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_HapticRunEffect(__p0, __p1, __p2) \
	({ \
		SDL_Haptic * __t__p0 = __p0;\
		int  __t__p1 = __p1;\
		Uint32  __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Haptic *, int , Uint32 ))*(void**)(__base - 3850))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_HapticStopEffect(__p0, __p1) \
	({ \
		SDL_Haptic * __t__p0 = __p0;\
		int  __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Haptic *, int ))*(void**)(__base - 3856))(__t__p0, __t__p1));\
	})

#define SDL_HapticDestroyEffect(__p0, __p1) \
	({ \
		SDL_Haptic * __t__p0 = __p0;\
		int  __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(SDL_Haptic *, int ))*(void**)(__base - 3862))(__t__p0, __t__p1));\
	})

#define SDL_HapticGetEffectStatus(__p0, __p1) \
	({ \
		SDL_Haptic * __t__p0 = __p0;\
		int  __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Haptic *, int ))*(void**)(__base - 3868))(__t__p0, __t__p1));\
	})

#define SDL_HapticSetGain(__p0, __p1) \
	({ \
		SDL_Haptic * __t__p0 = __p0;\
		int  __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Haptic *, int ))*(void**)(__base - 3874))(__t__p0, __t__p1));\
	})

#define SDL_HapticSetAutocenter(__p0, __p1) \
	({ \
		SDL_Haptic * __t__p0 = __p0;\
		int  __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Haptic *, int ))*(void**)(__base - 3880))(__t__p0, __t__p1));\
	})

#define SDL_HapticPause(__p0) \
	({ \
		SDL_Haptic * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Haptic *))*(void**)(__base - 3886))(__t__p0));\
	})

#define SDL_HapticUnpause(__p0) \
	({ \
		SDL_Haptic * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Haptic *))*(void**)(__base - 3892))(__t__p0));\
	})

#define SDL_HapticStopAll(__p0) \
	({ \
		SDL_Haptic * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Haptic *))*(void**)(__base - 3898))(__t__p0));\
	})

#define SDL_HapticRumbleSupported(__p0) \
	({ \
		SDL_Haptic * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Haptic *))*(void**)(__base - 3904))(__t__p0));\
	})

#define SDL_HapticRumbleInit(__p0) \
	({ \
		SDL_Haptic * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Haptic *))*(void**)(__base - 3910))(__t__p0));\
	})

#define SDL_HapticRumblePlay(__p0, __p1, __p2) \
	({ \
		SDL_Haptic * __t__p0 = __p0;\
		float  __t__p1 = __p1;\
		Uint32  __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Haptic *, float , Uint32 ))*(void**)(__base - 3916))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_HapticRumbleStop(__p0) \
	({ \
		SDL_Haptic * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Haptic *))*(void**)(__base - 3922))(__t__p0));\
	})

#define SDL_SetHintWithPriority(__p0, __p1, __p2) \
	({ \
		const char * __t__p0 = __p0;\
		const char * __t__p1 = __p1;\
		SDL_HintPriority  __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_bool (*)(const char *, const char *, SDL_HintPriority ))*(void**)(__base - 1216))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_SetHint(__p0, __p1) \
	({ \
		const char * __t__p0 = __p0;\
		const char * __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_bool (*)(const char *, const char *))*(void**)(__base - 1222))(__t__p0, __t__p1));\
	})

#define SDL_GetHint(__p0) \
	({ \
		const char * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((const char *(*)(const char *))*(void**)(__base - 1228))(__t__p0));\
	})

#define SDL_AddHintCallback(__p0, __p1, __p2) \
	({ \
		const char * __t__p0 = __p0;\
		SDL_HintCallback  __t__p1 = __p1;\
		void * __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(const char *, SDL_HintCallback , void *))*(void**)(__base - 1234))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_DelHintCallback(__p0, __p1, __p2) \
	({ \
		const char * __t__p0 = __p0;\
		SDL_HintCallback  __t__p1 = __p1;\
		void * __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(const char *, SDL_HintCallback , void *))*(void**)(__base - 1240))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_ClearHints() \
	({ \
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(void))*(void**)(__base - 1246))());\
	})

#define SDL_LoadObject(__p0) \
	({ \
		const char * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void *(*)(const char *))*(void**)(__base - 1252))(__t__p0));\
	})

#define SDL_LoadFunction(__p0, __p1) \
	({ \
		void * __t__p0 = __p0;\
		const char * __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void *(*)(void *, const char *))*(void**)(__base - 1258))(__t__p0, __t__p1));\
	})

#define SDL_UnloadObject(__p0) \
	({ \
		void * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(void *))*(void**)(__base - 1264))(__t__p0));\
	})

#define SDL_LogSetAllPriority(__p0) \
	({ \
		SDL_LogPriority  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(SDL_LogPriority ))*(void**)(__base - 1270))(__t__p0));\
	})

#define SDL_LogSetPriority(__p0, __p1) \
	({ \
		int  __t__p0 = __p0;\
		SDL_LogPriority  __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(int , SDL_LogPriority ))*(void**)(__base - 1276))(__t__p0, __t__p1));\
	})

#define SDL_LogGetPriority(__p0) \
	({ \
		int  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_LogPriority (*)(int ))*(void**)(__base - 1282))(__t__p0));\
	})

#define SDL_LogResetPriorities() \
	({ \
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(void))*(void**)(__base - 1288))());\
	})

#define SDL_LogMessageV(__p0, __p1, __p2, __p3) \
	({ \
		int  __t__p0 = __p0;\
		SDL_LogPriority  __t__p1 = __p1;\
		const char * __t__p2 = __p2;\
		va_list __t__p3;\
		va_copy(__t__p3, __p3);\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(int , SDL_LogPriority , const char *, va_list ))*(void**)(__base - 1294))(__t__p0, __t__p1, __t__p2, __t__p3));\
	})

#define SDL_LogGetOutputFunction(__p0, __p1) \
	({ \
		SDL_LogOutputFunction * __t__p0 = __p0;\
		void ** __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(SDL_LogOutputFunction *, void **))*(void**)(__base - 1300))(__t__p0, __t__p1));\
	})

#define SDL_LogSetOutputFunction(__p0, __p1) \
	({ \
		SDL_LogOutputFunction  __t__p0 = __p0;\
		void * __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(SDL_LogOutputFunction , void *))*(void**)(__base - 1306))(__t__p0, __t__p1));\
	})

#define SDL_ShowMessageBox(__p0, __p1) \
	({ \
		const SDL_MessageBoxData * __t__p0 = __p0;\
		int * __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(const SDL_MessageBoxData *, int *))*(void**)(__base - 1312))(__t__p0, __t__p1));\
	})

#define SDL_ShowSimpleMessageBox(__p0, __p1, __p2, __p3) \
	({ \
		Uint32  __t__p0 = __p0;\
		const char * __t__p1 = __p1;\
		const char * __t__p2 = __p2;\
		SDL_Window * __t__p3 = __p3;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(Uint32 , const char *, const char *, SDL_Window *))*(void**)(__base - 1318))(__t__p0, __t__p1, __t__p2, __t__p3));\
	})

#define SDL_CreateMutex() \
	({ \
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_mutex *(*)(void))*(void**)(__base - 1324))());\
	})

#define SDL_LockMutex(__p0) \
	({ \
		SDL_mutex * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_mutex *))*(void**)(__base - 1330))(__t__p0));\
	})

#define SDL_TryLockMutex(__p0) \
	({ \
		SDL_mutex * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_mutex *))*(void**)(__base - 1336))(__t__p0));\
	})

#define SDL_UnlockMutex(__p0) \
	({ \
		SDL_mutex * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_mutex *))*(void**)(__base - 1342))(__t__p0));\
	})

#define SDL_DestroyMutex(__p0) \
	({ \
		SDL_mutex * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(SDL_mutex *))*(void**)(__base - 1348))(__t__p0));\
	})

#define SDL_CreateSemaphore(__p0) \
	({ \
		Uint32  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_sem *(*)(Uint32 ))*(void**)(__base - 1354))(__t__p0));\
	})

#define SDL_DestroySemaphore(__p0) \
	({ \
		SDL_sem * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(SDL_sem *))*(void**)(__base - 1360))(__t__p0));\
	})

#define SDL_SemWait(__p0) \
	({ \
		SDL_sem * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_sem *))*(void**)(__base - 1366))(__t__p0));\
	})

#define SDL_SemTryWait(__p0) \
	({ \
		SDL_sem * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_sem *))*(void**)(__base - 1372))(__t__p0));\
	})

#define SDL_SemWaitTimeout(__p0, __p1) \
	({ \
		SDL_sem * __t__p0 = __p0;\
		Uint32  __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_sem *, Uint32 ))*(void**)(__base - 1378))(__t__p0, __t__p1));\
	})

#define SDL_SemPost(__p0) \
	({ \
		SDL_sem * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_sem *))*(void**)(__base - 1384))(__t__p0));\
	})

#define SDL_SemValue(__p0) \
	({ \
		SDL_sem * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((Uint32 (*)(SDL_sem *))*(void**)(__base - 1390))(__t__p0));\
	})

#define SDL_CreateCond() \
	({ \
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_cond *(*)(void))*(void**)(__base - 1396))());\
	})

#define SDL_DestroyCond(__p0) \
	({ \
		SDL_cond * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(SDL_cond *))*(void**)(__base - 1402))(__t__p0));\
	})

#define SDL_CondSignal(__p0) \
	({ \
		SDL_cond * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_cond *))*(void**)(__base - 1408))(__t__p0));\
	})

#define SDL_CondBroadcast(__p0) \
	({ \
		SDL_cond * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_cond *))*(void**)(__base - 1414))(__t__p0));\
	})

#define SDL_CondWait(__p0, __p1) \
	({ \
		SDL_cond * __t__p0 = __p0;\
		SDL_mutex * __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_cond *, SDL_mutex *))*(void**)(__base - 1420))(__t__p0, __t__p1));\
	})

#define SDL_CondWaitTimeout(__p0, __p1, __p2) \
	({ \
		SDL_cond * __t__p0 = __p0;\
		SDL_mutex * __t__p1 = __p1;\
		Uint32  __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_cond *, SDL_mutex *, Uint32 ))*(void**)(__base - 1426))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_GetPowerInfo(__p0, __p1) \
	({ \
		int * __t__p0 = __p0;\
		int * __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_PowerState (*)(int *, int *))*(void**)(__base - 1432))(__t__p0, __t__p1));\
	})

#define SDL_GetNumRenderDrivers() \
	({ \
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(void))*(void**)(__base - 1438))());\
	})

#define SDL_GetRenderDriverInfo(__p0, __p1) \
	({ \
		int  __t__p0 = __p0;\
		SDL_RendererInfo * __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(int , SDL_RendererInfo *))*(void**)(__base - 1444))(__t__p0, __t__p1));\
	})

#define SDL_CreateWindowAndRenderer(__p0, __p1, __p2, __p3, __p4) \
	({ \
		int  __t__p0 = __p0;\
		int  __t__p1 = __p1;\
		Uint32  __t__p2 = __p2;\
		SDL_Window ** __t__p3 = __p3;\
		SDL_Renderer ** __t__p4 = __p4;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(int , int , Uint32 , SDL_Window **, SDL_Renderer **))*(void**)(__base - 1450))(__t__p0, __t__p1, __t__p2, __t__p3, __t__p4));\
	})

#define SDL_CreateRenderer(__p0, __p1, __p2) \
	({ \
		SDL_Window * __t__p0 = __p0;\
		int  __t__p1 = __p1;\
		Uint32  __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_Renderer *(*)(SDL_Window *, int , Uint32 ))*(void**)(__base - 1456))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_CreateSoftwareRenderer(__p0) \
	({ \
		SDL_Surface * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_Renderer *(*)(SDL_Surface *))*(void**)(__base - 1462))(__t__p0));\
	})

#define SDL_GetRenderer(__p0) \
	({ \
		SDL_Window * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_Renderer *(*)(SDL_Window *))*(void**)(__base - 1468))(__t__p0));\
	})

#define SDL_GetRendererInfo(__p0, __p1) \
	({ \
		SDL_Renderer * __t__p0 = __p0;\
		SDL_RendererInfo * __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Renderer *, SDL_RendererInfo *))*(void**)(__base - 1474))(__t__p0, __t__p1));\
	})

#define SDL_GetRendererOutputSize(__p0, __p1, __p2) \
	({ \
		SDL_Renderer * __t__p0 = __p0;\
		int * __t__p1 = __p1;\
		int * __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Renderer *, int *, int *))*(void**)(__base - 1480))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_CreateTexture(__p0, __p1, __p2, __p3, __p4) \
	({ \
		SDL_Renderer * __t__p0 = __p0;\
		Uint32  __t__p1 = __p1;\
		int  __t__p2 = __p2;\
		int  __t__p3 = __p3;\
		int  __t__p4 = __p4;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_Texture *(*)(SDL_Renderer *, Uint32 , int , int , int ))*(void**)(__base - 1486))(__t__p0, __t__p1, __t__p2, __t__p3, __t__p4));\
	})

#define SDL_CreateTextureFromSurface(__p0, __p1) \
	({ \
		SDL_Renderer * __t__p0 = __p0;\
		SDL_Surface * __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_Texture *(*)(SDL_Renderer *, SDL_Surface *))*(void**)(__base - 1492))(__t__p0, __t__p1));\
	})

#define SDL_QueryTexture(__p0, __p1, __p2, __p3, __p4) \
	({ \
		SDL_Texture * __t__p0 = __p0;\
		Uint32 * __t__p1 = __p1;\
		int * __t__p2 = __p2;\
		int * __t__p3 = __p3;\
		int * __t__p4 = __p4;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Texture *, Uint32 *, int *, int *, int *))*(void**)(__base - 1498))(__t__p0, __t__p1, __t__p2, __t__p3, __t__p4));\
	})

#define SDL_SetTextureColorMod(__p0, __p1, __p2, __p3) \
	({ \
		SDL_Texture * __t__p0 = __p0;\
		Uint8  __t__p1 = __p1;\
		Uint8  __t__p2 = __p2;\
		Uint8  __t__p3 = __p3;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Texture *, Uint8 , Uint8 , Uint8 ))*(void**)(__base - 1504))(__t__p0, __t__p1, __t__p2, __t__p3));\
	})

#define SDL_GetTextureColorMod(__p0, __p1, __p2, __p3) \
	({ \
		SDL_Texture * __t__p0 = __p0;\
		Uint8 * __t__p1 = __p1;\
		Uint8 * __t__p2 = __p2;\
		Uint8 * __t__p3 = __p3;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Texture *, Uint8 *, Uint8 *, Uint8 *))*(void**)(__base - 1510))(__t__p0, __t__p1, __t__p2, __t__p3));\
	})

#define SDL_SetTextureAlphaMod(__p0, __p1) \
	({ \
		SDL_Texture * __t__p0 = __p0;\
		Uint8  __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Texture *, Uint8 ))*(void**)(__base - 1516))(__t__p0, __t__p1));\
	})

#define SDL_GetTextureAlphaMod(__p0, __p1) \
	({ \
		SDL_Texture * __t__p0 = __p0;\
		Uint8 * __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Texture *, Uint8 *))*(void**)(__base - 1522))(__t__p0, __t__p1));\
	})

#define SDL_SetTextureBlendMode(__p0, __p1) \
	({ \
		SDL_Texture * __t__p0 = __p0;\
		SDL_BlendMode  __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Texture *, SDL_BlendMode ))*(void**)(__base - 1528))(__t__p0, __t__p1));\
	})

#define SDL_GetTextureBlendMode(__p0, __p1) \
	({ \
		SDL_Texture * __t__p0 = __p0;\
		SDL_BlendMode * __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Texture *, SDL_BlendMode *))*(void**)(__base - 1534))(__t__p0, __t__p1));\
	})

#define SDL_UpdateTexture(__p0, __p1, __p2, __p3) \
	({ \
		SDL_Texture * __t__p0 = __p0;\
		const SDL_Rect * __t__p1 = __p1;\
		const void * __t__p2 = __p2;\
		int  __t__p3 = __p3;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Texture *, const SDL_Rect *, const void *, int ))*(void**)(__base - 1540))(__t__p0, __t__p1, __t__p2, __t__p3));\
	})

#define SDL_UpdateYUVTexture(__p0, __p1, __p2, __p3, __p4, __p5, __p6, __p7) \
	({ \
		SDL_Texture * __t__p0 = __p0;\
		const SDL_Rect * __t__p1 = __p1;\
		const Uint8 * __t__p2 = __p2;\
		int  __t__p3 = __p3;\
		const Uint8 * __t__p4 = __p4;\
		int  __t__p5 = __p5;\
		const Uint8 * __t__p6 = __p6;\
		int  __t__p7 = __p7;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Texture *, const SDL_Rect *, const Uint8 *, int , const Uint8 *, int , const Uint8 *, int ))*(void**)(__base - 1546))(__t__p0, __t__p1, __t__p2, __t__p3, __t__p4, __t__p5, __t__p6, __t__p7));\
	})

#define SDL_LockTexture(__p0, __p1, __p2, __p3) \
	({ \
		SDL_Texture * __t__p0 = __p0;\
		const SDL_Rect * __t__p1 = __p1;\
		void ** __t__p2 = __p2;\
		int * __t__p3 = __p3;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Texture *, const SDL_Rect *, void **, int *))*(void**)(__base - 1552))(__t__p0, __t__p1, __t__p2, __t__p3));\
	})

#define SDL_UnlockTexture(__p0) \
	({ \
		SDL_Texture * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(SDL_Texture *))*(void**)(__base - 1558))(__t__p0));\
	})

#define SDL_RenderTargetSupported(__p0) \
	({ \
		SDL_Renderer * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_bool (*)(SDL_Renderer *))*(void**)(__base - 1564))(__t__p0));\
	})

#define SDL_SetRenderTarget(__p0, __p1) \
	({ \
		SDL_Renderer * __t__p0 = __p0;\
		SDL_Texture * __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Renderer *, SDL_Texture *))*(void**)(__base - 1570))(__t__p0, __t__p1));\
	})

#define SDL_GetRenderTarget(__p0) \
	({ \
		SDL_Renderer * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_Texture *(*)(SDL_Renderer *))*(void**)(__base - 1576))(__t__p0));\
	})

#define SDL_RenderSetLogicalSize(__p0, __p1, __p2) \
	({ \
		SDL_Renderer * __t__p0 = __p0;\
		int  __t__p1 = __p1;\
		int  __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Renderer *, int , int ))*(void**)(__base - 1582))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_RenderGetLogicalSize(__p0, __p1, __p2) \
	({ \
		SDL_Renderer * __t__p0 = __p0;\
		int * __t__p1 = __p1;\
		int * __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(SDL_Renderer *, int *, int *))*(void**)(__base - 1588))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_RenderSetViewport(__p0, __p1) \
	({ \
		SDL_Renderer * __t__p0 = __p0;\
		const SDL_Rect * __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Renderer *, const SDL_Rect *))*(void**)(__base - 1594))(__t__p0, __t__p1));\
	})

#define SDL_RenderGetViewport(__p0, __p1) \
	({ \
		SDL_Renderer * __t__p0 = __p0;\
		SDL_Rect * __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(SDL_Renderer *, SDL_Rect *))*(void**)(__base - 1600))(__t__p0, __t__p1));\
	})

#define SDL_RenderSetClipRect(__p0, __p1) \
	({ \
		SDL_Renderer * __t__p0 = __p0;\
		const SDL_Rect * __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Renderer *, const SDL_Rect *))*(void**)(__base - 1606))(__t__p0, __t__p1));\
	})

#define SDL_RenderGetClipRect(__p0, __p1) \
	({ \
		SDL_Renderer * __t__p0 = __p0;\
		SDL_Rect * __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(SDL_Renderer *, SDL_Rect *))*(void**)(__base - 1612))(__t__p0, __t__p1));\
	})

#define SDL_RenderSetScale(__p0, __p1, __p2) \
	({ \
		SDL_Renderer * __t__p0 = __p0;\
		float  __t__p1 = __p1;\
		float  __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Renderer *, float , float ))*(void**)(__base - 1618))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_RenderGetScale(__p0, __p1, __p2) \
	({ \
		SDL_Renderer * __t__p0 = __p0;\
		float * __t__p1 = __p1;\
		float * __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(SDL_Renderer *, float *, float *))*(void**)(__base - 1624))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_SetRenderDrawColor(__p0, __p1, __p2, __p3, __p4) \
	({ \
		SDL_Renderer * __t__p0 = __p0;\
		Uint8  __t__p1 = __p1;\
		Uint8  __t__p2 = __p2;\
		Uint8  __t__p3 = __p3;\
		Uint8  __t__p4 = __p4;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Renderer *, Uint8 , Uint8 , Uint8 , Uint8 ))*(void**)(__base - 1630))(__t__p0, __t__p1, __t__p2, __t__p3, __t__p4));\
	})

#define SDL_GetRenderDrawColor(__p0, __p1, __p2, __p3, __p4) \
	({ \
		SDL_Renderer * __t__p0 = __p0;\
		Uint8 * __t__p1 = __p1;\
		Uint8 * __t__p2 = __p2;\
		Uint8 * __t__p3 = __p3;\
		Uint8 * __t__p4 = __p4;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Renderer *, Uint8 *, Uint8 *, Uint8 *, Uint8 *))*(void**)(__base - 1636))(__t__p0, __t__p1, __t__p2, __t__p3, __t__p4));\
	})

#define SDL_SetRenderDrawBlendMode(__p0, __p1) \
	({ \
		SDL_Renderer * __t__p0 = __p0;\
		SDL_BlendMode  __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Renderer *, SDL_BlendMode ))*(void**)(__base - 1642))(__t__p0, __t__p1));\
	})

#define SDL_GetRenderDrawBlendMode(__p0, __p1) \
	({ \
		SDL_Renderer * __t__p0 = __p0;\
		SDL_BlendMode * __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Renderer *, SDL_BlendMode *))*(void**)(__base - 1648))(__t__p0, __t__p1));\
	})

#define SDL_RenderClear(__p0) \
	({ \
		SDL_Renderer * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Renderer *))*(void**)(__base - 1654))(__t__p0));\
	})

#define SDL_RenderDrawPoint(__p0, __p1, __p2) \
	({ \
		SDL_Renderer * __t__p0 = __p0;\
		int  __t__p1 = __p1;\
		int  __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Renderer *, int , int ))*(void**)(__base - 1660))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_RenderDrawPoints(__p0, __p1, __p2) \
	({ \
		SDL_Renderer * __t__p0 = __p0;\
		const SDL_Point * __t__p1 = __p1;\
		int  __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Renderer *, const SDL_Point *, int ))*(void**)(__base - 1666))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_RenderDrawLine(__p0, __p1, __p2, __p3, __p4) \
	({ \
		SDL_Renderer * __t__p0 = __p0;\
		int  __t__p1 = __p1;\
		int  __t__p2 = __p2;\
		int  __t__p3 = __p3;\
		int  __t__p4 = __p4;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Renderer *, int , int , int , int ))*(void**)(__base - 1672))(__t__p0, __t__p1, __t__p2, __t__p3, __t__p4));\
	})

#define SDL_RenderDrawLines(__p0, __p1, __p2) \
	({ \
		SDL_Renderer * __t__p0 = __p0;\
		const SDL_Point * __t__p1 = __p1;\
		int  __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Renderer *, const SDL_Point *, int ))*(void**)(__base - 1678))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_RenderDrawRect(__p0, __p1) \
	({ \
		SDL_Renderer * __t__p0 = __p0;\
		const SDL_Rect * __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Renderer *, const SDL_Rect *))*(void**)(__base - 1684))(__t__p0, __t__p1));\
	})

#define SDL_RenderDrawRects(__p0, __p1, __p2) \
	({ \
		SDL_Renderer * __t__p0 = __p0;\
		const SDL_Rect * __t__p1 = __p1;\
		int  __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Renderer *, const SDL_Rect *, int ))*(void**)(__base - 1690))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_RenderFillRect(__p0, __p1) \
	({ \
		SDL_Renderer * __t__p0 = __p0;\
		const SDL_Rect * __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Renderer *, const SDL_Rect *))*(void**)(__base - 1696))(__t__p0, __t__p1));\
	})

#define SDL_RenderFillRects(__p0, __p1, __p2) \
	({ \
		SDL_Renderer * __t__p0 = __p0;\
		const SDL_Rect * __t__p1 = __p1;\
		int  __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Renderer *, const SDL_Rect *, int ))*(void**)(__base - 1702))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_RenderCopy(__p0, __p1, __p2, __p3) \
	({ \
		SDL_Renderer * __t__p0 = __p0;\
		SDL_Texture * __t__p1 = __p1;\
		const SDL_Rect * __t__p2 = __p2;\
		const SDL_Rect * __t__p3 = __p3;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Renderer *, SDL_Texture *, const SDL_Rect *, const SDL_Rect *))*(void**)(__base - 1708))(__t__p0, __t__p1, __t__p2, __t__p3));\
	})

#define SDL_RenderCopyEx(__p0, __p1, __p2, __p3, __p4, __p5, __p6) \
	({ \
		SDL_Renderer * __t__p0 = __p0;\
		SDL_Texture * __t__p1 = __p1;\
		const SDL_Rect * __t__p2 = __p2;\
		const SDL_Rect * __t__p3 = __p3;\
		const double  __t__p4 = __p4;\
		const SDL_Point * __t__p5 = __p5;\
		const SDL_RendererFlip  __t__p6 = __p6;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Renderer *, SDL_Texture *, const SDL_Rect *, const SDL_Rect *, const double , const SDL_Point *, const SDL_RendererFlip ))*(void**)(__base - 1714))(__t__p0, __t__p1, __t__p2, __t__p3, __t__p4, __t__p5, __t__p6));\
	})

#define SDL_RenderReadPixels(__p0, __p1, __p2, __p3, __p4) \
	({ \
		SDL_Renderer * __t__p0 = __p0;\
		const SDL_Rect * __t__p1 = __p1;\
		Uint32  __t__p2 = __p2;\
		void * __t__p3 = __p3;\
		int  __t__p4 = __p4;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Renderer *, const SDL_Rect *, Uint32 , void *, int ))*(void**)(__base - 1720))(__t__p0, __t__p1, __t__p2, __t__p3, __t__p4));\
	})

#define SDL_RenderPresent(__p0) \
	({ \
		SDL_Renderer * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(SDL_Renderer *))*(void**)(__base - 1726))(__t__p0));\
	})

#define SDL_DestroyTexture(__p0) \
	({ \
		SDL_Texture * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(SDL_Texture *))*(void**)(__base - 1732))(__t__p0));\
	})

#define SDL_DestroyRenderer(__p0) \
	({ \
		SDL_Renderer * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(SDL_Renderer *))*(void**)(__base - 1738))(__t__p0));\
	})

#define SDL_GL_BindTexture(__p0, __p1, __p2) \
	({ \
		SDL_Texture * __t__p0 = __p0;\
		float * __t__p1 = __p1;\
		float * __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Texture *, float *, float *))*(void**)(__base - 1744))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_GL_UnbindTexture(__p0) \
	({ \
		SDL_Texture * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Texture *))*(void**)(__base - 1750))(__t__p0));\
	})

#define SDL_RWFromFile(__p0, __p1) \
	({ \
		const char * __t__p0 = __p0;\
		const char * __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_RWops *(*)(const char *, const char *))*(void**)(__base - 1756))(__t__p0, __t__p1));\
	})

#define SDL_RWFromMem(__p0, __p1) \
	({ \
		void * __t__p0 = __p0;\
		int  __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_RWops *(*)(void *, int ))*(void**)(__base - 1768))(__t__p0, __t__p1));\
	})

#define SDL_RWFromConstMem(__p0, __p1) \
	({ \
		const void * __t__p0 = __p0;\
		int  __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_RWops *(*)(const void *, int ))*(void**)(__base - 1774))(__t__p0, __t__p1));\
	})

#define SDL_AllocRW() \
	({ \
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_RWops *(*)(void))*(void**)(__base - 1780))());\
	})

#define SDL_FreeRW(__p0) \
	({ \
		SDL_RWops * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(SDL_RWops *))*(void**)(__base - 1786))(__t__p0));\
	})

#define SDL_ReadU8(__p0) \
	({ \
		SDL_RWops * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((Uint8 (*)(SDL_RWops *))*(void**)(__base - 1792))(__t__p0));\
	})

#define SDL_ReadLE16(__p0) \
	({ \
		SDL_RWops * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((Uint16 (*)(SDL_RWops *))*(void**)(__base - 1798))(__t__p0));\
	})

#define SDL_ReadBE16(__p0) \
	({ \
		SDL_RWops * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((Uint16 (*)(SDL_RWops *))*(void**)(__base - 1804))(__t__p0));\
	})

#define SDL_ReadLE32(__p0) \
	({ \
		SDL_RWops * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((Uint32 (*)(SDL_RWops *))*(void**)(__base - 1810))(__t__p0));\
	})

#define SDL_ReadBE32(__p0) \
	({ \
		SDL_RWops * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((Uint32 (*)(SDL_RWops *))*(void**)(__base - 1816))(__t__p0));\
	})

#define SDL_ReadLE64(__p0) \
	({ \
		SDL_RWops * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((Uint64 (*)(SDL_RWops *))*(void**)(__base - 1822))(__t__p0));\
	})

#define SDL_ReadBE64(__p0) \
	({ \
		SDL_RWops * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((Uint64 (*)(SDL_RWops *))*(void**)(__base - 1828))(__t__p0));\
	})

#define SDL_WriteU8(__p0, __p1) \
	({ \
		SDL_RWops * __t__p0 = __p0;\
		Uint8  __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((size_t (*)(SDL_RWops *, Uint8 ))*(void**)(__base - 1834))(__t__p0, __t__p1));\
	})

#define SDL_WriteLE16(__p0, __p1) \
	({ \
		SDL_RWops * __t__p0 = __p0;\
		Uint16  __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((size_t (*)(SDL_RWops *, Uint16 ))*(void**)(__base - 1840))(__t__p0, __t__p1));\
	})

#define SDL_WriteBE16(__p0, __p1) \
	({ \
		SDL_RWops * __t__p0 = __p0;\
		Uint16  __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((size_t (*)(SDL_RWops *, Uint16 ))*(void**)(__base - 1846))(__t__p0, __t__p1));\
	})

#define SDL_WriteLE32(__p0, __p1) \
	({ \
		SDL_RWops * __t__p0 = __p0;\
		Uint32  __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((size_t (*)(SDL_RWops *, Uint32 ))*(void**)(__base - 1852))(__t__p0, __t__p1));\
	})

#define SDL_WriteBE32(__p0, __p1) \
	({ \
		SDL_RWops * __t__p0 = __p0;\
		Uint32  __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((size_t (*)(SDL_RWops *, Uint32 ))*(void**)(__base - 1858))(__t__p0, __t__p1));\
	})

#define SDL_WriteLE64(__p0, __p1) \
	({ \
		SDL_RWops * __t__p0 = __p0;\
		Uint64  __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((size_t (*)(SDL_RWops *, Uint64 ))*(void**)(__base - 1864))(__t__p0, __t__p1));\
	})

#define SDL_WriteBE64(__p0, __p1) \
	({ \
		SDL_RWops * __t__p0 = __p0;\
		Uint64  __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((size_t (*)(SDL_RWops *, Uint64 ))*(void**)(__base - 1870))(__t__p0, __t__p1));\
	})

#define SDL_CreateThread(__p0, __p1, __p2) \
	({ \
		SDL_ThreadFunction  __t__p0 = __p0;\
		const char * __t__p1 = __p1;\
		void * __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_Thread *(*)(SDL_ThreadFunction , const char *, void *))*(void**)(__base - 1876))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_GetThreadName(__p0) \
	({ \
		SDL_Thread * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((const char *(*)(SDL_Thread *))*(void**)(__base - 1882))(__t__p0));\
	})

#define SDL_ThreadID() \
	({ \
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_threadID (*)(void))*(void**)(__base - 1888))());\
	})

#define SDL_GetThreadID(__p0) \
	({ \
		SDL_Thread * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_threadID (*)(SDL_Thread *))*(void**)(__base - 1894))(__t__p0));\
	})

#define SDL_SetThreadPriority(__p0) \
	({ \
		SDL_ThreadPriority  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_ThreadPriority ))*(void**)(__base - 1900))(__t__p0));\
	})

#define SDL_WaitThread(__p0, __p1) \
	({ \
		SDL_Thread * __t__p0 = __p0;\
		int * __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(SDL_Thread *, int *))*(void**)(__base - 1906))(__t__p0, __t__p1));\
	})

#define SDL_DetachThread(__p0) \
	({ \
		SDL_Thread * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(SDL_Thread *))*(void**)(__base - 1912))(__t__p0));\
	})

#define SDL_TLSCreate() \
	({ \
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_TLSID (*)(void))*(void**)(__base - 1918))());\
	})

#define SDL_TLSGet(__p0) \
	({ \
		SDL_TLSID  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void *(*)(SDL_TLSID ))*(void**)(__base - 1924))(__t__p0));\
	})

#define SDL_TLSSet(__p0, __p1, __p2) \
	({ \
		SDL_TLSID  __t__p0 = __p0;\
		const void * __t__p1 = __p1;\
		SDL_TLSDestructorCallback  __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_TLSID , const void *, SDL_TLSDestructorCallback ))*(void**)(__base - 1930))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_GetTicks() \
	({ \
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((Uint32 (*)(void))*(void**)(__base - 1936))());\
	})

#define SDL_GetPerformanceCounter() \
	({ \
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((Uint64 (*)(void))*(void**)(__base - 1942))());\
	})

#define SDL_GetPerformanceFrequency() \
	({ \
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((Uint64 (*)(void))*(void**)(__base - 1948))());\
	})

#define SDL_Delay(__p0) \
	({ \
		Uint32  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(Uint32 ))*(void**)(__base - 1954))(__t__p0));\
	})

#define SDL_AddTimer(__p0, __p1, __p2) \
	({ \
		Uint32  __t__p0 = __p0;\
		SDL_TimerCallback  __t__p1 = __p1;\
		void * __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_TimerID (*)(Uint32 , SDL_TimerCallback , void *))*(void**)(__base - 1960))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_RemoveTimer(__p0) \
	({ \
		SDL_TimerID  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_bool (*)(SDL_TimerID ))*(void**)(__base - 1966))(__t__p0));\
	})

#define SDL_GetVersion(__p0) \
	({ \
		SDL_version * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(SDL_version *))*(void**)(__base - 1972))(__t__p0));\
	})

#define SDL_GetRevision() \
	({ \
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((const char *(*)(void))*(void**)(__base - 1978))());\
	})

#define SDL_GetRevisionNumber() \
	({ \
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(void))*(void**)(__base - 1984))());\
	})

#define SDL_GetNumVideoDrivers() \
	({ \
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(void))*(void**)(__base - 1990))());\
	})

#define SDL_GetVideoDriver(__p0) \
	({ \
		int  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((const char *(*)(int ))*(void**)(__base - 1996))(__t__p0));\
	})

#define SDL_VideoInit(__p0) \
	({ \
		const char * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(const char *))*(void**)(__base - 2002))(__t__p0));\
	})

#define SDL_VideoQuit() \
	({ \
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(void))*(void**)(__base - 2008))());\
	})

#define SDL_GetCurrentVideoDriver() \
	({ \
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((const char *(*)(void))*(void**)(__base - 2014))());\
	})

#define SDL_GetNumVideoDisplays() \
	({ \
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(void))*(void**)(__base - 2020))());\
	})

#define SDL_GetDisplayName(__p0) \
	({ \
		int  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((const char *(*)(int ))*(void**)(__base - 2026))(__t__p0));\
	})

#define SDL_GetDisplayBounds(__p0, __p1) \
	({ \
		int  __t__p0 = __p0;\
		SDL_Rect * __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(int , SDL_Rect *))*(void**)(__base - 2032))(__t__p0, __t__p1));\
	})

#define SDL_GetNumDisplayModes(__p0) \
	({ \
		int  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(int ))*(void**)(__base - 2038))(__t__p0));\
	})

#define SDL_GetDisplayMode(__p0, __p1, __p2) \
	({ \
		int  __t__p0 = __p0;\
		int  __t__p1 = __p1;\
		SDL_DisplayMode * __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(int , int , SDL_DisplayMode *))*(void**)(__base - 2044))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_GetDesktopDisplayMode(__p0, __p1) \
	({ \
		int  __t__p0 = __p0;\
		SDL_DisplayMode * __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(int , SDL_DisplayMode *))*(void**)(__base - 2050))(__t__p0, __t__p1));\
	})

#define SDL_GetCurrentDisplayMode(__p0, __p1) \
	({ \
		int  __t__p0 = __p0;\
		SDL_DisplayMode * __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(int , SDL_DisplayMode *))*(void**)(__base - 2056))(__t__p0, __t__p1));\
	})

#define SDL_GetClosestDisplayMode(__p0, __p1, __p2) \
	({ \
		int  __t__p0 = __p0;\
		const SDL_DisplayMode * __t__p1 = __p1;\
		SDL_DisplayMode * __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_DisplayMode *(*)(int , const SDL_DisplayMode *, SDL_DisplayMode *))*(void**)(__base - 2062))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_GetWindowDisplayIndex(__p0) \
	({ \
		SDL_Window * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Window *))*(void**)(__base - 2068))(__t__p0));\
	})

#define SDL_SetWindowDisplayMode(__p0, __p1) \
	({ \
		SDL_Window * __t__p0 = __p0;\
		const SDL_DisplayMode * __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Window *, const SDL_DisplayMode *))*(void**)(__base - 2074))(__t__p0, __t__p1));\
	})

#define SDL_GetWindowDisplayMode(__p0, __p1) \
	({ \
		SDL_Window * __t__p0 = __p0;\
		SDL_DisplayMode * __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Window *, SDL_DisplayMode *))*(void**)(__base - 2080))(__t__p0, __t__p1));\
	})

#define SDL_GetWindowPixelFormat(__p0) \
	({ \
		SDL_Window * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((Uint32 (*)(SDL_Window *))*(void**)(__base - 2086))(__t__p0));\
	})

#define SDL_CreateWindow(__p0, __p1, __p2, __p3, __p4, __p5) \
	({ \
		const char * __t__p0 = __p0;\
		int  __t__p1 = __p1;\
		int  __t__p2 = __p2;\
		int  __t__p3 = __p3;\
		int  __t__p4 = __p4;\
		Uint32  __t__p5 = __p5;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_Window *(*)(const char *, int , int , int , int , Uint32 ))*(void**)(__base - 2092))(__t__p0, __t__p1, __t__p2, __t__p3, __t__p4, __t__p5));\
	})

#define SDL_CreateWindowFrom(__p0) \
	({ \
		const void * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_Window *(*)(const void *))*(void**)(__base - 2098))(__t__p0));\
	})

#define SDL_GetWindowID(__p0) \
	({ \
		SDL_Window * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((Uint32 (*)(SDL_Window *))*(void**)(__base - 2104))(__t__p0));\
	})

#define SDL_GetWindowFromID(__p0) \
	({ \
		Uint32  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_Window *(*)(Uint32 ))*(void**)(__base - 2110))(__t__p0));\
	})

#define SDL_GetWindowFlags(__p0) \
	({ \
		SDL_Window * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((Uint32 (*)(SDL_Window *))*(void**)(__base - 2116))(__t__p0));\
	})

#define SDL_SetWindowTitle(__p0, __p1) \
	({ \
		SDL_Window * __t__p0 = __p0;\
		const char * __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(SDL_Window *, const char *))*(void**)(__base - 2122))(__t__p0, __t__p1));\
	})

#define SDL_GetWindowTitle(__p0) \
	({ \
		SDL_Window * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((const char *(*)(SDL_Window *))*(void**)(__base - 2128))(__t__p0));\
	})

#define SDL_SetWindowIcon(__p0, __p1) \
	({ \
		SDL_Window * __t__p0 = __p0;\
		SDL_Surface * __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(SDL_Window *, SDL_Surface *))*(void**)(__base - 2134))(__t__p0, __t__p1));\
	})

#define SDL_SetWindowData(__p0, __p1, __p2) \
	({ \
		SDL_Window * __t__p0 = __p0;\
		const char * __t__p1 = __p1;\
		void * __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void *(*)(SDL_Window *, const char *, void *))*(void**)(__base - 2140))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_GetWindowData(__p0, __p1) \
	({ \
		SDL_Window * __t__p0 = __p0;\
		const char * __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void *(*)(SDL_Window *, const char *))*(void**)(__base - 2146))(__t__p0, __t__p1));\
	})

#define SDL_SetWindowPosition(__p0, __p1, __p2) \
	({ \
		SDL_Window * __t__p0 = __p0;\
		int  __t__p1 = __p1;\
		int  __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(SDL_Window *, int , int ))*(void**)(__base - 2152))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_GetWindowPosition(__p0, __p1, __p2) \
	({ \
		SDL_Window * __t__p0 = __p0;\
		int * __t__p1 = __p1;\
		int * __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(SDL_Window *, int *, int *))*(void**)(__base - 2158))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_SetWindowSize(__p0, __p1, __p2) \
	({ \
		SDL_Window * __t__p0 = __p0;\
		int  __t__p1 = __p1;\
		int  __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(SDL_Window *, int , int ))*(void**)(__base - 2164))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_GetWindowSize(__p0, __p1, __p2) \
	({ \
		SDL_Window * __t__p0 = __p0;\
		int * __t__p1 = __p1;\
		int * __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(SDL_Window *, int *, int *))*(void**)(__base - 2170))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_SetWindowMinimumSize(__p0, __p1, __p2) \
	({ \
		SDL_Window * __t__p0 = __p0;\
		int  __t__p1 = __p1;\
		int  __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(SDL_Window *, int , int ))*(void**)(__base - 2176))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_GetWindowMinimumSize(__p0, __p1, __p2) \
	({ \
		SDL_Window * __t__p0 = __p0;\
		int * __t__p1 = __p1;\
		int * __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(SDL_Window *, int *, int *))*(void**)(__base - 2182))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_SetWindowMaximumSize(__p0, __p1, __p2) \
	({ \
		SDL_Window * __t__p0 = __p0;\
		int  __t__p1 = __p1;\
		int  __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(SDL_Window *, int , int ))*(void**)(__base - 2188))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_GetWindowMaximumSize(__p0, __p1, __p2) \
	({ \
		SDL_Window * __t__p0 = __p0;\
		int * __t__p1 = __p1;\
		int * __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(SDL_Window *, int *, int *))*(void**)(__base - 2194))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_SetWindowBordered(__p0, __p1) \
	({ \
		SDL_Window * __t__p0 = __p0;\
		SDL_bool  __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(SDL_Window *, SDL_bool ))*(void**)(__base - 2200))(__t__p0, __t__p1));\
	})

#define SDL_ShowWindow(__p0) \
	({ \
		SDL_Window * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(SDL_Window *))*(void**)(__base - 2206))(__t__p0));\
	})

#define SDL_HideWindow(__p0) \
	({ \
		SDL_Window * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(SDL_Window *))*(void**)(__base - 2212))(__t__p0));\
	})

#define SDL_RaiseWindow(__p0) \
	({ \
		SDL_Window * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(SDL_Window *))*(void**)(__base - 2218))(__t__p0));\
	})

#define SDL_MaximizeWindow(__p0) \
	({ \
		SDL_Window * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(SDL_Window *))*(void**)(__base - 2224))(__t__p0));\
	})

#define SDL_MinimizeWindow(__p0) \
	({ \
		SDL_Window * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(SDL_Window *))*(void**)(__base - 2230))(__t__p0));\
	})

#define SDL_RestoreWindow(__p0) \
	({ \
		SDL_Window * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(SDL_Window *))*(void**)(__base - 2236))(__t__p0));\
	})

#define SDL_SetWindowFullscreen(__p0, __p1) \
	({ \
		SDL_Window * __t__p0 = __p0;\
		Uint32  __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Window *, Uint32 ))*(void**)(__base - 2242))(__t__p0, __t__p1));\
	})

#define SDL_GetWindowSurface(__p0) \
	({ \
		SDL_Window * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_Surface *(*)(SDL_Window *))*(void**)(__base - 2248))(__t__p0));\
	})

#define SDL_UpdateWindowSurface(__p0) \
	({ \
		SDL_Window * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Window *))*(void**)(__base - 2254))(__t__p0));\
	})

#define SDL_UpdateWindowSurfaceRects(__p0, __p1, __p2) \
	({ \
		SDL_Window * __t__p0 = __p0;\
		const SDL_Rect * __t__p1 = __p1;\
		int  __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Window *, const SDL_Rect *, int ))*(void**)(__base - 2260))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_SetWindowGrab(__p0, __p1) \
	({ \
		SDL_Window * __t__p0 = __p0;\
		SDL_bool  __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(SDL_Window *, SDL_bool ))*(void**)(__base - 2266))(__t__p0, __t__p1));\
	})

#define SDL_GetWindowGrab(__p0) \
	({ \
		SDL_Window * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_bool (*)(SDL_Window *))*(void**)(__base - 2272))(__t__p0));\
	})

#define SDL_SetWindowBrightness(__p0, __p1) \
	({ \
		SDL_Window * __t__p0 = __p0;\
		float  __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Window *, float ))*(void**)(__base - 2278))(__t__p0, __t__p1));\
	})

#define SDL_GetWindowBrightness(__p0) \
	({ \
		SDL_Window * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((float (*)(SDL_Window *))*(void**)(__base - 2284))(__t__p0));\
	})

#define SDL_SetWindowGammaRamp(__p0, __p1, __p2, __p3) \
	({ \
		SDL_Window * __t__p0 = __p0;\
		const Uint16 * __t__p1 = __p1;\
		const Uint16 * __t__p2 = __p2;\
		const Uint16 * __t__p3 = __p3;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Window *, const Uint16 *, const Uint16 *, const Uint16 *))*(void**)(__base - 2290))(__t__p0, __t__p1, __t__p2, __t__p3));\
	})

#define SDL_GetWindowGammaRamp(__p0, __p1, __p2, __p3) \
	({ \
		SDL_Window * __t__p0 = __p0;\
		Uint16 * __t__p1 = __p1;\
		Uint16 * __t__p2 = __p2;\
		Uint16 * __t__p3 = __p3;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Window *, Uint16 *, Uint16 *, Uint16 *))*(void**)(__base - 2296))(__t__p0, __t__p1, __t__p2, __t__p3));\
	})

#define SDL_DestroyWindow(__p0) \
	({ \
		SDL_Window * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(SDL_Window *))*(void**)(__base - 2302))(__t__p0));\
	})

#define SDL_IsScreenSaverEnabled() \
	({ \
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_bool (*)(void))*(void**)(__base - 2308))());\
	})

#define SDL_EnableScreenSaver() \
	({ \
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(void))*(void**)(__base - 2314))());\
	})

#define SDL_DisableScreenSaver() \
	({ \
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(void))*(void**)(__base - 2320))());\
	})

#define SDL_GetKeyboardFocus() \
	({ \
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_Window *(*)(void))*(void**)(__base - 2326))());\
	})

#define SDL_GetKeyboardState(__p0) \
	({ \
		int * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((const Uint8 *(*)(int *))*(void**)(__base - 2332))(__t__p0));\
	})

#define SDL_GetModState() \
	({ \
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_Keymod (*)(void))*(void**)(__base - 2338))());\
	})

#define SDL_SetModState(__p0) \
	({ \
		SDL_Keymod  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(SDL_Keymod ))*(void**)(__base - 2344))(__t__p0));\
	})

#define SDL_GetKeyFromScancode(__p0) \
	({ \
		SDL_Scancode  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_Keycode (*)(SDL_Scancode ))*(void**)(__base - 2350))(__t__p0));\
	})

#define SDL_GetScancodeFromKey(__p0) \
	({ \
		SDL_Keycode  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_Scancode (*)(SDL_Keycode ))*(void**)(__base - 2356))(__t__p0));\
	})

#define SDL_GetScancodeName(__p0) \
	({ \
		SDL_Scancode  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((const char *(*)(SDL_Scancode ))*(void**)(__base - 2362))(__t__p0));\
	})

#define SDL_GetScancodeFromName(__p0) \
	({ \
		const char * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_Scancode (*)(const char *))*(void**)(__base - 2368))(__t__p0));\
	})

#define SDL_GetKeyName(__p0) \
	({ \
		SDL_Keycode  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((const char *(*)(SDL_Keycode ))*(void**)(__base - 2374))(__t__p0));\
	})

#define SDL_GetKeyFromName(__p0) \
	({ \
		const char * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_Keycode (*)(const char *))*(void**)(__base - 2380))(__t__p0));\
	})

#define SDL_StartTextInput() \
	({ \
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(void))*(void**)(__base - 2386))());\
	})

#define SDL_IsTextInputActive() \
	({ \
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_bool (*)(void))*(void**)(__base - 2392))());\
	})

#define SDL_StopTextInput() \
	({ \
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(void))*(void**)(__base - 2398))());\
	})

#define SDL_SetTextInputRect(__p0) \
	({ \
		const SDL_Rect * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(const SDL_Rect *))*(void**)(__base - 2404))(__t__p0));\
	})

#define SDL_HasScreenKeyboardSupport() \
	({ \
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_bool (*)(void))*(void**)(__base - 2410))());\
	})

#define SDL_IsScreenKeyboardShown(__p0) \
	({ \
		SDL_Window * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_bool (*)(SDL_Window *))*(void**)(__base - 2416))(__t__p0));\
	})

#define SDL_CreateRGBSurface(__p0, __p1, __p2, __p3, __p4, __p5, __p6, __p7) \
	({ \
		Uint32  __t__p0 = __p0;\
		int  __t__p1 = __p1;\
		int  __t__p2 = __p2;\
		int  __t__p3 = __p3;\
		Uint32  __t__p4 = __p4;\
		Uint32  __t__p5 = __p5;\
		Uint32  __t__p6 = __p6;\
		Uint32  __t__p7 = __p7;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_Surface *(*)(Uint32 , int , int , int , Uint32 , Uint32 , Uint32 , Uint32 ))*(void**)(__base - 2422))(__t__p0, __t__p1, __t__p2, __t__p3, __t__p4, __t__p5, __t__p6, __t__p7));\
	})

#define SDL_CreateRGBSurfaceFrom(__p0, __p1, __p2, __p3, __p4, __p5, __p6, __p7, __p8) \
	({ \
		void * __t__p0 = __p0;\
		int  __t__p1 = __p1;\
		int  __t__p2 = __p2;\
		int  __t__p3 = __p3;\
		int  __t__p4 = __p4;\
		Uint32  __t__p5 = __p5;\
		Uint32  __t__p6 = __p6;\
		Uint32  __t__p7 = __p7;\
		Uint32  __t__p8 = __p8;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_Surface *(*)(void *, int , int , int , int , Uint32 , Uint32 , Uint32 , Uint32 ))*(void**)(__base - 2428))(__t__p0, __t__p1, __t__p2, __t__p3, __t__p4, __t__p5, __t__p6, __t__p7, __t__p8));\
	})

#define SDL_FreeSurface(__p0) \
	({ \
		SDL_Surface * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(SDL_Surface *))*(void**)(__base - 2434))(__t__p0));\
	})

#define SDL_SetSurfacePalette(__p0, __p1) \
	({ \
		SDL_Surface * __t__p0 = __p0;\
		SDL_Palette * __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Surface *, SDL_Palette *))*(void**)(__base - 2440))(__t__p0, __t__p1));\
	})

#define SDL_LockSurface(__p0) \
	({ \
		SDL_Surface * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Surface *))*(void**)(__base - 2446))(__t__p0));\
	})

#define SDL_UnlockSurface(__p0) \
	({ \
		SDL_Surface * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(SDL_Surface *))*(void**)(__base - 2452))(__t__p0));\
	})

#define SDL_LoadBMP_RW(__p0, __p1) \
	({ \
		SDL_RWops * __t__p0 = __p0;\
		int  __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_Surface *(*)(SDL_RWops *, int ))*(void**)(__base - 2458))(__t__p0, __t__p1));\
	})

#define SDL_SaveBMP_RW(__p0, __p1, __p2) \
	({ \
		SDL_Surface * __t__p0 = __p0;\
		SDL_RWops * __t__p1 = __p1;\
		int  __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Surface *, SDL_RWops *, int ))*(void**)(__base - 2464))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_SetSurfaceRLE(__p0, __p1) \
	({ \
		SDL_Surface * __t__p0 = __p0;\
		int  __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Surface *, int ))*(void**)(__base - 2470))(__t__p0, __t__p1));\
	})

#define SDL_SetColorKey(__p0, __p1, __p2) \
	({ \
		SDL_Surface * __t__p0 = __p0;\
		int  __t__p1 = __p1;\
		Uint32  __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Surface *, int , Uint32 ))*(void**)(__base - 2476))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_GetColorKey(__p0, __p1) \
	({ \
		SDL_Surface * __t__p0 = __p0;\
		Uint32 * __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Surface *, Uint32 *))*(void**)(__base - 2482))(__t__p0, __t__p1));\
	})

#define SDL_SetSurfaceColorMod(__p0, __p1, __p2, __p3) \
	({ \
		SDL_Surface * __t__p0 = __p0;\
		Uint8  __t__p1 = __p1;\
		Uint8  __t__p2 = __p2;\
		Uint8  __t__p3 = __p3;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Surface *, Uint8 , Uint8 , Uint8 ))*(void**)(__base - 2488))(__t__p0, __t__p1, __t__p2, __t__p3));\
	})

#define SDL_GetSurfaceColorMod(__p0, __p1, __p2, __p3) \
	({ \
		SDL_Surface * __t__p0 = __p0;\
		Uint8 * __t__p1 = __p1;\
		Uint8 * __t__p2 = __p2;\
		Uint8 * __t__p3 = __p3;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Surface *, Uint8 *, Uint8 *, Uint8 *))*(void**)(__base - 2494))(__t__p0, __t__p1, __t__p2, __t__p3));\
	})

#define SDL_SetSurfaceAlphaMod(__p0, __p1) \
	({ \
		SDL_Surface * __t__p0 = __p0;\
		Uint8  __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Surface *, Uint8 ))*(void**)(__base - 2500))(__t__p0, __t__p1));\
	})

#define SDL_GetSurfaceAlphaMod(__p0, __p1) \
	({ \
		SDL_Surface * __t__p0 = __p0;\
		Uint8 * __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Surface *, Uint8 *))*(void**)(__base - 2506))(__t__p0, __t__p1));\
	})

#define SDL_SetSurfaceBlendMode(__p0, __p1) \
	({ \
		SDL_Surface * __t__p0 = __p0;\
		SDL_BlendMode  __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Surface *, SDL_BlendMode ))*(void**)(__base - 2512))(__t__p0, __t__p1));\
	})

#define SDL_GetSurfaceBlendMode(__p0, __p1) \
	({ \
		SDL_Surface * __t__p0 = __p0;\
		SDL_BlendMode * __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Surface *, SDL_BlendMode *))*(void**)(__base - 2518))(__t__p0, __t__p1));\
	})

#define SDL_SetClipRect(__p0, __p1) \
	({ \
		SDL_Surface * __t__p0 = __p0;\
		const SDL_Rect * __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_bool (*)(SDL_Surface *, const SDL_Rect *))*(void**)(__base - 2524))(__t__p0, __t__p1));\
	})

#define SDL_GetClipRect(__p0, __p1) \
	({ \
		SDL_Surface * __t__p0 = __p0;\
		SDL_Rect * __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(SDL_Surface *, SDL_Rect *))*(void**)(__base - 2530))(__t__p0, __t__p1));\
	})

#define SDL_ConvertSurface(__p0, __p1, __p2) \
	({ \
		SDL_Surface * __t__p0 = __p0;\
		const SDL_PixelFormat * __t__p1 = __p1;\
		Uint32  __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_Surface *(*)(SDL_Surface *, const SDL_PixelFormat *, Uint32 ))*(void**)(__base - 2536))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_ConvertSurfaceFormat(__p0, __p1, __p2) \
	({ \
		SDL_Surface * __t__p0 = __p0;\
		Uint32  __t__p1 = __p1;\
		Uint32  __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_Surface *(*)(SDL_Surface *, Uint32 , Uint32 ))*(void**)(__base - 2542))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_ConvertPixels(__p0, __p1, __p2, __p3, __p4, __p5, __p6, __p7) \
	({ \
		int  __t__p0 = __p0;\
		int  __t__p1 = __p1;\
		Uint32  __t__p2 = __p2;\
		const void * __t__p3 = __p3;\
		int  __t__p4 = __p4;\
		Uint32  __t__p5 = __p5;\
		void * __t__p6 = __p6;\
		int  __t__p7 = __p7;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(int , int , Uint32 , const void *, int , Uint32 , void *, int ))*(void**)(__base - 2548))(__t__p0, __t__p1, __t__p2, __t__p3, __t__p4, __t__p5, __t__p6, __t__p7));\
	})

#define SDL_FillRect(__p0, __p1, __p2) \
	({ \
		SDL_Surface * __t__p0 = __p0;\
		const SDL_Rect * __t__p1 = __p1;\
		Uint32  __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Surface *, const SDL_Rect *, Uint32 ))*(void**)(__base - 2554))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_FillRects(__p0, __p1, __p2, __p3) \
	({ \
		SDL_Surface * __t__p0 = __p0;\
		const SDL_Rect * __t__p1 = __p1;\
		int  __t__p2 = __p2;\
		Uint32  __t__p3 = __p3;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Surface *, const SDL_Rect *, int , Uint32 ))*(void**)(__base - 2560))(__t__p0, __t__p1, __t__p2, __t__p3));\
	})

#define SDL_UpperBlit(__p0, __p1, __p2, __p3) \
	({ \
		SDL_Surface * __t__p0 = __p0;\
		const SDL_Rect * __t__p1 = __p1;\
		SDL_Surface * __t__p2 = __p2;\
		SDL_Rect * __t__p3 = __p3;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Surface *, const SDL_Rect *, SDL_Surface *, SDL_Rect *))*(void**)(__base - 2566))(__t__p0, __t__p1, __t__p2, __t__p3));\
	})

#define SDL_LowerBlit(__p0, __p1, __p2, __p3) \
	({ \
		SDL_Surface * __t__p0 = __p0;\
		SDL_Rect * __t__p1 = __p1;\
		SDL_Surface * __t__p2 = __p2;\
		SDL_Rect * __t__p3 = __p3;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Surface *, SDL_Rect *, SDL_Surface *, SDL_Rect *))*(void**)(__base - 2572))(__t__p0, __t__p1, __t__p2, __t__p3));\
	})

#define SDL_SoftStretch(__p0, __p1, __p2, __p3) \
	({ \
		SDL_Surface * __t__p0 = __p0;\
		const SDL_Rect * __t__p1 = __p1;\
		SDL_Surface * __t__p2 = __p2;\
		const SDL_Rect * __t__p3 = __p3;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Surface *, const SDL_Rect *, SDL_Surface *, const SDL_Rect *))*(void**)(__base - 2578))(__t__p0, __t__p1, __t__p2, __t__p3));\
	})

#define SDL_UpperBlitScaled(__p0, __p1, __p2, __p3) \
	({ \
		SDL_Surface * __t__p0 = __p0;\
		const SDL_Rect * __t__p1 = __p1;\
		SDL_Surface * __t__p2 = __p2;\
		SDL_Rect * __t__p3 = __p3;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Surface *, const SDL_Rect *, SDL_Surface *, SDL_Rect *))*(void**)(__base - 2584))(__t__p0, __t__p1, __t__p2, __t__p3));\
	})

#define SDL_LowerBlitScaled(__p0, __p1, __p2, __p3) \
	({ \
		SDL_Surface * __t__p0 = __p0;\
		SDL_Rect * __t__p1 = __p1;\
		SDL_Surface * __t__p2 = __p2;\
		SDL_Rect * __t__p3 = __p3;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Surface *, SDL_Rect *, SDL_Surface *, SDL_Rect *))*(void**)(__base - 2590))(__t__p0, __t__p1, __t__p2, __t__p3));\
	})

#define SDL_GetMouseFocus() \
	({ \
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_Window *(*)(void))*(void**)(__base - 2596))());\
	})

#define SDL_GetMouseState(__p0, __p1) \
	({ \
		int * __t__p0 = __p0;\
		int * __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((Uint32 (*)(int *, int *))*(void**)(__base - 2602))(__t__p0, __t__p1));\
	})

#define SDL_GetRelativeMouseState(__p0, __p1) \
	({ \
		int * __t__p0 = __p0;\
		int * __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((Uint32 (*)(int *, int *))*(void**)(__base - 2608))(__t__p0, __t__p1));\
	})

#define SDL_WarpMouseInWindow(__p0, __p1, __p2) \
	({ \
		SDL_Window * __t__p0 = __p0;\
		int  __t__p1 = __p1;\
		int  __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(SDL_Window *, int , int ))*(void**)(__base - 2614))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_SetRelativeMouseMode(__p0) \
	({ \
		SDL_bool  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_bool ))*(void**)(__base - 2620))(__t__p0));\
	})

#define SDL_GetRelativeMouseMode() \
	({ \
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_bool (*)(void))*(void**)(__base - 2626))());\
	})

#define SDL_CreateCursor(__p0, __p1, __p2, __p3, __p4, __p5) \
	({ \
		const Uint8 * __t__p0 = __p0;\
		const Uint8 * __t__p1 = __p1;\
		int  __t__p2 = __p2;\
		int  __t__p3 = __p3;\
		int  __t__p4 = __p4;\
		int  __t__p5 = __p5;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_Cursor *(*)(const Uint8 *, const Uint8 *, int , int , int , int ))*(void**)(__base - 2632))(__t__p0, __t__p1, __t__p2, __t__p3, __t__p4, __t__p5));\
	})

#define SDL_CreateColorCursor(__p0, __p1, __p2) \
	({ \
		SDL_Surface * __t__p0 = __p0;\
		int  __t__p1 = __p1;\
		int  __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_Cursor *(*)(SDL_Surface *, int , int ))*(void**)(__base - 2638))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_CreateSystemCursor(__p0) \
	({ \
		SDL_SystemCursor  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_Cursor *(*)(SDL_SystemCursor ))*(void**)(__base - 2644))(__t__p0));\
	})

#define SDL_SetCursor(__p0) \
	({ \
		SDL_Cursor * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(SDL_Cursor *))*(void**)(__base - 2650))(__t__p0));\
	})

#define SDL_GetCursor() \
	({ \
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_Cursor *(*)(void))*(void**)(__base - 2656))());\
	})

#define SDL_GetDefaultCursor() \
	({ \
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_Cursor *(*)(void))*(void**)(__base - 2662))());\
	})

#define SDL_FreeCursor(__p0) \
	({ \
		SDL_Cursor * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(SDL_Cursor *))*(void**)(__base - 2668))(__t__p0));\
	})

#define SDL_ShowCursor(__p0) \
	({ \
		int  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(int ))*(void**)(__base - 2674))(__t__p0));\
	})

#define SDL_GetPixelFormatName(__p0) \
	({ \
		Uint32  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((const char *(*)(Uint32 ))*(void**)(__base - 2680))(__t__p0));\
	})

#define SDL_PixelFormatEnumToMasks(__p0, __p1, __p2, __p3, __p4, __p5) \
	({ \
		Uint32  __t__p0 = __p0;\
		int * __t__p1 = __p1;\
		Uint32 * __t__p2 = __p2;\
		Uint32 * __t__p3 = __p3;\
		Uint32 * __t__p4 = __p4;\
		Uint32 * __t__p5 = __p5;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_bool (*)(Uint32 , int *, Uint32 *, Uint32 *, Uint32 *, Uint32 *))*(void**)(__base - 2686))(__t__p0, __t__p1, __t__p2, __t__p3, __t__p4, __t__p5));\
	})

#define SDL_MasksToPixelFormatEnum(__p0, __p1, __p2, __p3, __p4) \
	({ \
		int  __t__p0 = __p0;\
		Uint32  __t__p1 = __p1;\
		Uint32  __t__p2 = __p2;\
		Uint32  __t__p3 = __p3;\
		Uint32  __t__p4 = __p4;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((Uint32 (*)(int , Uint32 , Uint32 , Uint32 , Uint32 ))*(void**)(__base - 2692))(__t__p0, __t__p1, __t__p2, __t__p3, __t__p4));\
	})

#define SDL_AllocFormat(__p0) \
	({ \
		Uint32  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_PixelFormat *(*)(Uint32 ))*(void**)(__base - 2698))(__t__p0));\
	})

#define SDL_FreeFormat(__p0) \
	({ \
		SDL_PixelFormat * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(SDL_PixelFormat *))*(void**)(__base - 2704))(__t__p0));\
	})

#define SDL_AllocPalette(__p0) \
	({ \
		int  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_Palette *(*)(int ))*(void**)(__base - 2710))(__t__p0));\
	})

#define SDL_SetPixelFormatPalette(__p0, __p1) \
	({ \
		SDL_PixelFormat * __t__p0 = __p0;\
		SDL_Palette * __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_PixelFormat *, SDL_Palette *))*(void**)(__base - 2716))(__t__p0, __t__p1));\
	})

#define SDL_SetPaletteColors(__p0, __p1, __p2, __p3) \
	({ \
		SDL_Palette * __t__p0 = __p0;\
		const SDL_Color * __t__p1 = __p1;\
		int  __t__p2 = __p2;\
		int  __t__p3 = __p3;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Palette *, const SDL_Color *, int , int ))*(void**)(__base - 2722))(__t__p0, __t__p1, __t__p2, __t__p3));\
	})

#define SDL_FreePalette(__p0) \
	({ \
		SDL_Palette * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(SDL_Palette *))*(void**)(__base - 2728))(__t__p0));\
	})

#define SDL_MapRGB(__p0, __p1, __p2, __p3) \
	({ \
		const SDL_PixelFormat * __t__p0 = __p0;\
		Uint8  __t__p1 = __p1;\
		Uint8  __t__p2 = __p2;\
		Uint8  __t__p3 = __p3;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((Uint32 (*)(const SDL_PixelFormat *, Uint8 , Uint8 , Uint8 ))*(void**)(__base - 2734))(__t__p0, __t__p1, __t__p2, __t__p3));\
	})

#define SDL_MapRGBA(__p0, __p1, __p2, __p3, __p4) \
	({ \
		const SDL_PixelFormat * __t__p0 = __p0;\
		Uint8  __t__p1 = __p1;\
		Uint8  __t__p2 = __p2;\
		Uint8  __t__p3 = __p3;\
		Uint8  __t__p4 = __p4;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((Uint32 (*)(const SDL_PixelFormat *, Uint8 , Uint8 , Uint8 , Uint8 ))*(void**)(__base - 2740))(__t__p0, __t__p1, __t__p2, __t__p3, __t__p4));\
	})

#define SDL_GetRGB(__p0, __p1, __p2, __p3, __p4) \
	({ \
		Uint32  __t__p0 = __p0;\
		const SDL_PixelFormat * __t__p1 = __p1;\
		Uint8 * __t__p2 = __p2;\
		Uint8 * __t__p3 = __p3;\
		Uint8 * __t__p4 = __p4;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(Uint32 , const SDL_PixelFormat *, Uint8 *, Uint8 *, Uint8 *))*(void**)(__base - 2746))(__t__p0, __t__p1, __t__p2, __t__p3, __t__p4));\
	})

#define SDL_GetRGBA(__p0, __p1, __p2, __p3, __p4, __p5) \
	({ \
		Uint32  __t__p0 = __p0;\
		const SDL_PixelFormat * __t__p1 = __p1;\
		Uint8 * __t__p2 = __p2;\
		Uint8 * __t__p3 = __p3;\
		Uint8 * __t__p4 = __p4;\
		Uint8 * __t__p5 = __p5;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(Uint32 , const SDL_PixelFormat *, Uint8 *, Uint8 *, Uint8 *, Uint8 *))*(void**)(__base - 2752))(__t__p0, __t__p1, __t__p2, __t__p3, __t__p4, __t__p5));\
	})

#define SDL_CalculateGammaRamp(__p0, __p1) \
	({ \
		float  __t__p0 = __p0;\
		Uint16 * __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(float , Uint16 *))*(void**)(__base - 2758))(__t__p0, __t__p1));\
	})

#define SDL_HasIntersection(__p0, __p1) \
	({ \
		const SDL_Rect * __t__p0 = __p0;\
		const SDL_Rect * __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_bool (*)(const SDL_Rect *, const SDL_Rect *))*(void**)(__base - 2764))(__t__p0, __t__p1));\
	})

#define SDL_IntersectRect(__p0, __p1, __p2) \
	({ \
		const SDL_Rect * __t__p0 = __p0;\
		const SDL_Rect * __t__p1 = __p1;\
		SDL_Rect * __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_bool (*)(const SDL_Rect *, const SDL_Rect *, SDL_Rect *))*(void**)(__base - 2770))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_UnionRect(__p0, __p1, __p2) \
	({ \
		const SDL_Rect * __t__p0 = __p0;\
		const SDL_Rect * __t__p1 = __p1;\
		SDL_Rect * __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(const SDL_Rect *, const SDL_Rect *, SDL_Rect *))*(void**)(__base - 2776))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_EnclosePoints(__p0, __p1, __p2, __p3) \
	({ \
		const SDL_Point * __t__p0 = __p0;\
		int  __t__p1 = __p1;\
		const SDL_Rect * __t__p2 = __p2;\
		SDL_Rect * __t__p3 = __p3;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_bool (*)(const SDL_Point *, int , const SDL_Rect *, SDL_Rect *))*(void**)(__base - 2782))(__t__p0, __t__p1, __t__p2, __t__p3));\
	})

#define SDL_IntersectRectAndLine(__p0, __p1, __p2, __p3, __p4) \
	({ \
		const SDL_Rect * __t__p0 = __p0;\
		int * __t__p1 = __p1;\
		int * __t__p2 = __p2;\
		int * __t__p3 = __p3;\
		int * __t__p4 = __p4;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_bool (*)(const SDL_Rect *, int *, int *, int *, int *))*(void**)(__base - 2788))(__t__p0, __t__p1, __t__p2, __t__p3, __t__p4));\
	})

#define SDL_GetWindowWMInfo(__p0, __p1) \
	({ \
		SDL_Window * __t__p0 = __p0;\
		SDL_SysWMinfo * __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_bool (*)(SDL_Window *, SDL_SysWMinfo *))*(void**)(__base - 2794))(__t__p0, __t__p1));\
	})

#define SDL_RecordGesture(__p0) \
	({ \
		SDL_TouchID  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_TouchID ))*(void**)(__base - 2800))(__t__p0));\
	})

#define SDL_SaveAllDollarTemplates(__p0) \
	({ \
		SDL_RWops * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_RWops *))*(void**)(__base - 2806))(__t__p0));\
	})

#define SDL_SaveDollarTemplate(__p0, __p1) \
	({ \
		SDL_GestureID  __t__p0 = __p0;\
		SDL_RWops * __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_GestureID , SDL_RWops *))*(void**)(__base - 2812))(__t__p0, __t__p1));\
	})

#define SDL_LoadDollarTemplates(__p0, __p1) \
	({ \
		SDL_TouchID  __t__p0 = __p0;\
		SDL_RWops * __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_TouchID , SDL_RWops *))*(void**)(__base - 2818))(__t__p0, __t__p1));\
	})

#define SDL_CreateShapedWindow(__p0, __p1, __p2, __p3, __p4, __p5) \
	({ \
		const char * __t__p0 = __p0;\
		unsigned int  __t__p1 = __p1;\
		unsigned int  __t__p2 = __p2;\
		unsigned int  __t__p3 = __p3;\
		unsigned int  __t__p4 = __p4;\
		Uint32  __t__p5 = __p5;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_Window *(*)(const char *, unsigned int , unsigned int , unsigned int , unsigned int , Uint32 ))*(void**)(__base - 2824))(__t__p0, __t__p1, __t__p2, __t__p3, __t__p4, __t__p5));\
	})

#define SDL_IsShapedWindow(__p0) \
	({ \
		const SDL_Window * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_bool (*)(const SDL_Window *))*(void**)(__base - 2830))(__t__p0));\
	})

#define SDL_SetWindowShape(__p0, __p1, __p2) \
	({ \
		SDL_Window * __t__p0 = __p0;\
		SDL_Surface * __t__p1 = __p1;\
		SDL_WindowShapeMode * __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Window *, SDL_Surface *, SDL_WindowShapeMode *))*(void**)(__base - 2836))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_GetShapedWindowMode(__p0, __p1) \
	({ \
		SDL_Window * __t__p0 = __p0;\
		SDL_WindowShapeMode * __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Window *, SDL_WindowShapeMode *))*(void**)(__base - 2842))(__t__p0, __t__p1));\
	})

#define SDL_GL_LoadLibrary(__p0) \
	({ \
		const char * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(const char *))*(void**)(__base - 3652))(__t__p0));\
	})

#define SDL_GL_UnloadLibrary() \
	({ \
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(void))*(void**)(__base - 3664))());\
	})

#define SDL_GL_ExtensionSupported(__p0) \
	({ \
		const char * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_bool (*)(const char *))*(void**)(__base - 3670))(__t__p0));\
	})

#define SDL_GL_ResetAttributes() \
	({ \
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(void))*(void**)(__base - 3676))());\
	})

#define SDL_GL_SetAttribute(__p0, __p1) \
	({ \
		SDL_GLattr  __t__p0 = __p0;\
		int  __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_GLattr , int ))*(void**)(__base - 3682))(__t__p0, __t__p1));\
	})

#define SDL_GL_GetAttribute(__p0, __p1) \
	({ \
		SDL_GLattr  __t__p0 = __p0;\
		int * __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_GLattr , int *))*(void**)(__base - 3688))(__t__p0, __t__p1));\
	})

#define SDL_GL_CreateContext(__p0) \
	({ \
		SDL_Window * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_GLContext (*)(SDL_Window *))*(void**)(__base - 3694))(__t__p0));\
	})

#define SDL_GL_MakeCurrent(__p0, __p1) \
	({ \
		SDL_Window * __t__p0 = __p0;\
		SDL_GLContext  __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Window *, SDL_GLContext ))*(void**)(__base - 3700))(__t__p0, __t__p1));\
	})

#define SDL_GL_GetCurrentWindow() \
	({ \
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_Window *(*)(void))*(void**)(__base - 3706))());\
	})

#define SDL_GL_GetCurrentContext() \
	({ \
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_GLContext (*)(void))*(void**)(__base - 3712))());\
	})

#define SDL_GL_GetDrawableSize(__p0, __p1, __p2) \
	({ \
		SDL_Window * __t__p0 = __p0;\
		int * __t__p1 = __p1;\
		int * __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(SDL_Window *, int *, int *))*(void**)(__base - 3718))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_GL_SetSwapInterval(__p0) \
	({ \
		int  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(int ))*(void**)(__base - 3724))(__t__p0));\
	})

#define SDL_GL_GetSwapInterval() \
	({ \
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(void))*(void**)(__base - 3730))());\
	})

#define SDL_GL_SwapWindow(__p0) \
	({ \
		SDL_Window * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(SDL_Window *))*(void**)(__base - 3736))(__t__p0));\
	})

#define SDL_GL_DeleteContext(__p0) \
	({ \
		SDL_GLContext  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(SDL_GLContext ))*(void**)(__base - 3742))(__t__p0));\
	})

#define SDL_sqrtf(__p0) \
	({ \
		float  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((float (*)(float ))*(void**)(__base - 2932))(__t__p0));\
	})

#define SDL_tan(__p0) \
	({ \
		double  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((double (*)(double ))*(void**)(__base - 2938))(__t__p0));\
	})

#define SDL_tanf(__p0) \
	({ \
		float  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((float (*)(float ))*(void**)(__base - 2944))(__t__p0));\
	})

#define SDL_QueueAudio(__p0, __p1, __p2) \
	({ \
		SDL_AudioDeviceID  __t__p0 = __p0;\
		const void * __t__p1 = __p1;\
		Uint32  __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_AudioDeviceID , const void *, Uint32 ))*(void**)(__base - 2914))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_GetQueuedAudioSize(__p0) \
	({ \
		SDL_AudioDeviceID  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((Uint32 (*)(SDL_AudioDeviceID ))*(void**)(__base - 2920))(__t__p0));\
	})

#define SDL_ClearQueuedAudio(__p0) \
	({ \
		SDL_AudioDeviceID  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(SDL_AudioDeviceID ))*(void**)(__base - 2926))(__t__p0));\
	})

#define SDL_HasAVX2() \
	({ \
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_bool (*)(void))*(void**)(__base - 2908))());\
	})

#define SDL_JoystickFromInstanceID(__p0) \
	({ \
		SDL_JoystickID  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_Joystick *(*)(SDL_JoystickID ))*(void**)(__base - 2902))(__t__p0));\
	})

#define SDL_JoystickCurrentPowerLevel(__p0) \
	({ \
		SDL_Joystick * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_JoystickPowerLevel (*)(SDL_Joystick *))*(void**)(__base - 2896))(__t__p0));\
	})

#define SDL_GameControllerFromInstanceID(__p0) \
	({ \
		SDL_JoystickID  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_GameController (*)(SDL_JoystickID ))*(void**)(__base - 2890))(__t__p0));\
	})

#define SDL_RenderIsClipEnabled(__p0) \
	({ \
		SDL_Renderer * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_bool (*)(SDL_Renderer *))*(void**)(__base - 2884))(__t__p0));\
	})

#define SDL_GetDisplayDPI(__p0, __p1, __p2, __p3) \
	({ \
		int  __t__p0 = __p0;\
		float * __t__p1 = __p1;\
		float * __t__p2 = __p2;\
		float * __t__p3 = __p3;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(int , float *, float *, float *))*(void**)(__base - 2878))(__t__p0, __t__p1, __t__p2, __t__p3));\
	})

#define SDL_SetWindowHitTest(__p0, __p1, __p2) \
	({ \
		SDL_Window * __t__p0 = __p0;\
		SDL_HitTest  __t__p1 = __p1;\
		void * __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Window *, SDL_HitTest , void *))*(void**)(__base - 2866))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_GetGrabbedWindow() \
	({ \
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_Window *(*)(void))*(void**)(__base - 2872))());\
	})

#define SDL_WarpMouseGlobal(__p0, __p1) \
	({ \
		int  __t__p0 = __p0;\
		int  __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(int , int ))*(void**)(__base - 2854))(__t__p0, __t__p1));\
	})

#define SDL_CaptureMouse(__p0) \
	({ \
		SDL_bool  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_bool ))*(void**)(__base - 2848))(__t__p0));\
	})

#define SDL_GetGlobalMouseState(__p0, __p1) \
	({ \
		int * __t__p0 = __p0;\
		int * __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((Uint32 (*)(int *, int *))*(void**)(__base - 2860))(__t__p0, __t__p1));\
	})

#define SDL_MemoryBarrierReleaseFunction() \
	({ \
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(void))*(void**)(__base - 2950))());\
	})

#define SDL_MemoryBarrierAcquireFunction() \
	({ \
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(void))*(void**)(__base - 2956))());\
	})

#define SDL_DequeueAudio(__p0, __p1, __p2) \
	({ \
		SDL_AudioDeviceID  __t__p0 = __p0;\
		void * __t__p1 = __p1;\
		Uint32  __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((Uint32 (*)(SDL_AudioDeviceID , void *, Uint32 ))*(void**)(__base - 2962))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_ComposeCustomBlendMode(__p0, __p1, __p2, __p3, __p4, __p5) \
	({ \
		SDL_BlendFactor  __t__p0 = __p0;\
		SDL_BlendFactor  __t__p1 = __p1;\
		SDL_BlendOperation  __t__p2 = __p2;\
		SDL_BlendFactor  __t__p3 = __p3;\
		SDL_BlendFactor  __t__p4 = __p4;\
		SDL_BlendOperation  __t__p5 = __p5;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_BlendMode (*)(SDL_BlendFactor , SDL_BlendFactor , SDL_BlendOperation , SDL_BlendFactor , SDL_BlendFactor , SDL_BlendOperation ))*(void**)(__base - 2968))(__t__p0, __t__p1, __t__p2, __t__p3, __t__p4, __t__p5));\
	})

#define SDL_HasNEON() \
	({ \
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_bool (*)(void))*(void**)(__base - 2974))());\
	})

#define SDL_GameControllerNumMappings() \
	({ \
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(void))*(void**)(__base - 2980))());\
	})

#define SDL_GameControllerMappingForIndex(__p0) \
	({ \
		int  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((char *(*)(int ))*(void**)(__base - 2986))(__t__p0));\
	})

#define SDL_GameControllerGetVendor(__p0) \
	({ \
		SDL_GameController * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((Uint16 (*)(SDL_GameController *))*(void**)(__base - 2992))(__t__p0));\
	})

#define SDL_GameControllerGetProduct(__p0) \
	({ \
		SDL_GameController * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((Uint16 (*)(SDL_GameController *))*(void**)(__base - 2998))(__t__p0));\
	})

#define SDL_GameControllerGetProductVersion(__p0) \
	({ \
		SDL_GameController * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((Uint16 (*)(SDL_GameController *))*(void**)(__base - 3004))(__t__p0));\
	})

#define SDL_GetHintBoolean(__p0, __p1) \
	({ \
		const char * __t__p0 = __p0;\
		SDL_bool  __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_bool (*)(const char *, SDL_bool ))*(void**)(__base - 3010))(__t__p0, __t__p1));\
	})

#define SDL_JoystickGetDeviceVendor(__p0) \
	({ \
		int  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((Uint16 (*)(int ))*(void**)(__base - 3016))(__t__p0));\
	})

#define SDL_JoystickGetDeviceProduct(__p0) \
	({ \
		int  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((Uint16 (*)(int ))*(void**)(__base - 3022))(__t__p0));\
	})

#define SDL_JoystickGetDeviceProductVersion(__p0) \
	({ \
		int  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((Uint16 (*)(int ))*(void**)(__base - 3028))(__t__p0));\
	})

#define SDL_JoystickGetDeviceType(__p0) \
	({ \
		int  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_JoystickType (*)(int ))*(void**)(__base - 3034))(__t__p0));\
	})

#define SDL_JoystickGetDeviceInstanceID(__p0) \
	({ \
		int  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_JoystickID (*)(int ))*(void**)(__base - 3040))(__t__p0));\
	})

#define SDL_JoystickGetVendor(__p0) \
	({ \
		SDL_Joystick * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((Uint16 (*)(SDL_Joystick *))*(void**)(__base - 3046))(__t__p0));\
	})

#define SDL_JoystickGetProduct(__p0) \
	({ \
		SDL_Joystick * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((Uint16 (*)(SDL_Joystick *))*(void**)(__base - 3052))(__t__p0));\
	})

#define SDL_JoystickGetProductVersion(__p0) \
	({ \
		SDL_Joystick * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((Uint16 (*)(SDL_Joystick *))*(void**)(__base - 3058))(__t__p0));\
	})

#define SDL_JoystickGetType(__p0) \
	({ \
		SDL_Joystick * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_JoystickType (*)(SDL_Joystick *))*(void**)(__base - 3064))(__t__p0));\
	})

#define SDL_JoystickGetAxisInitialState(__p0, __p1, __p2) \
	({ \
		SDL_Joystick * __t__p0 = __p0;\
		int  __t__p1 = __p1;\
		Sint16 * __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_bool (*)(SDL_Joystick *, int , Sint16 *))*(void**)(__base - 3070))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_GetDisplayUsableBounds(__p0, __p1) \
	({ \
		int  __t__p0 = __p0;\
		SDL_Rect * __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(int , SDL_Rect *))*(void**)(__base - 3076))(__t__p0, __t__p1));\
	})

#define SDL_GetWindowBordersSize(__p0, __p1, __p2, __p3, __p4) \
	({ \
		SDL_Window * __t__p0 = __p0;\
		int * __t__p1 = __p1;\
		int * __t__p2 = __p2;\
		int * __t__p3 = __p3;\
		int * __t__p4 = __p4;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Window *, int *, int *, int *, int *))*(void**)(__base - 3082))(__t__p0, __t__p1, __t__p2, __t__p3, __t__p4));\
	})

#define SDL_SetWindowResizable(__p0, __p1) \
	({ \
		SDL_Window * __t__p0 = __p0;\
		SDL_bool  __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(SDL_Window *, SDL_bool ))*(void**)(__base - 3088))(__t__p0, __t__p1));\
	})

#define SDL_SetWindowOpacity(__p0, __p1) \
	({ \
		SDL_Window * __t__p0 = __p0;\
		float  __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Window *, float ))*(void**)(__base - 3094))(__t__p0, __t__p1));\
	})

#define SDL_GetWindowOpacity(__p0, __p1) \
	({ \
		SDL_Window * __t__p0 = __p0;\
		float * __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Window *, float *))*(void**)(__base - 3100))(__t__p0, __t__p1));\
	})

#define SDL_SetWindowModalFor(__p0, __p1) \
	({ \
		SDL_Window * __t__p0 = __p0;\
		SDL_Window * __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Window *, SDL_Window *))*(void**)(__base - 3106))(__t__p0, __t__p1));\
	})

#define SDL_SetWindowInputFocus(__p0) \
	({ \
		SDL_Window * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Window *))*(void**)(__base - 3112))(__t__p0));\
	})

#define SDL_CreateRGBSurfaceWithFormat(__p0, __p1, __p2, __p3, __p4) \
	({ \
		Uint32  __t__p0 = __p0;\
		int  __t__p1 = __p1;\
		int  __t__p2 = __p2;\
		int  __t__p3 = __p3;\
		Uint32  __t__p4 = __p4;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_Surface *(*)(Uint32 , int , int , int , Uint32 ))*(void**)(__base - 3118))(__t__p0, __t__p1, __t__p2, __t__p3, __t__p4));\
	})

#define SDL_CreateRGBSurfaceWithFormatFrom(__p0, __p1, __p2, __p3, __p4, __p5) \
	({ \
		void * __t__p0 = __p0;\
		int  __t__p1 = __p1;\
		int  __t__p2 = __p2;\
		int  __t__p3 = __p3;\
		int  __t__p4 = __p4;\
		Uint32  __t__p5 = __p5;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_Surface *(*)(void *, int , int , int , int , Uint32 ))*(void**)(__base - 3124))(__t__p0, __t__p1, __t__p2, __t__p3, __t__p4, __t__p5));\
	})

#define SDL_DuplicateSurface(__p0) \
	({ \
		SDL_Surface * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_Surface *(*)(SDL_Surface *))*(void**)(__base - 3130))(__t__p0));\
	})

#define SDL_wcscmp(__p0, __p1) \
	({ \
		const wchar_t * __t__p0 = __p0;\
		const wchar_t * __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(const wchar_t *, const wchar_t *))*(void**)(__base - 3136))(__t__p0, __t__p1));\
	})

#define SDL_utf8strlen(__p0) \
	({ \
		const char * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((size_t (*)(const char *))*(void**)(__base - 3142))(__t__p0));\
	})

#define SDL_LoadFile_RW(__p0, __p1, __p2) \
	({ \
		SDL_RWops * __t__p0 = __p0;\
		size_t * __t__p1 = __p1;\
		int  __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void *(*)(SDL_RWops *, size_t *, int ))*(void**)(__base - 3148))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_RenderSetIntegerScale(__p0, __p1) \
	({ \
		SDL_Renderer * __t__p0 = __p0;\
		SDL_bool  __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Renderer *, SDL_bool ))*(void**)(__base - 3154))(__t__p0, __t__p1));\
	})

#define SDL_RenderGetIntegerScale(__p0) \
	({ \
		SDL_Renderer * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_bool (*)(SDL_Renderer *))*(void**)(__base - 3160))(__t__p0));\
	})

#define SDL_LockJoysticks() \
	({ \
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(void))*(void**)(__base - 3208))());\
	})

#define SDL_UnlockJoysticks() \
	({ \
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(void))*(void**)(__base - 3214))());\
	})

#define SDL_NewAudioStream(__p0, __p1, __p2, __p3, __p4) \
	({ \
		const SDL_AudioFormat  __t__p0 = __p0;\
		const Uint8  __t__p1 = __p1;\
		const SDL_AudioFormat  __t__p2 = __p2;\
		const Uint8  __t__p3 = __p3;\
		const int  __t__p4 = __p4;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_AudioStream *(*)(const SDL_AudioFormat , const Uint8 , const SDL_AudioFormat , const Uint8 , const int ))*(void**)(__base - 3166))(__t__p0, __t__p1, __t__p2, __t__p3, __t__p4));\
	})

#define SDL_AudioStreamPut(__p0, __p1, __p2) \
	({ \
		SDL_AudioStream * __t__p0 = __p0;\
		const void * __t__p1 = __p1;\
		int  __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_AudioStream *, const void *, int ))*(void**)(__base - 3172))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_AudioStreamGet(__p0, __p1, __p2) \
	({ \
		SDL_AudioStream * __t__p0 = __p0;\
		void * __t__p1 = __p1;\
		int  __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_AudioStream *, void *, int ))*(void**)(__base - 3178))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_AudioStreamAvailable(__p0) \
	({ \
		SDL_AudioStream * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_AudioStream *))*(void**)(__base - 3184))(__t__p0));\
	})

#define SDL_AudioStreamFlush(__p0) \
	({ \
		SDL_AudioStream * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_AudioStream *))*(void**)(__base - 3190))(__t__p0));\
	})

#define SDL_AudioStreamClear(__p0) \
	({ \
		SDL_AudioStream * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(SDL_AudioStream *))*(void**)(__base - 3196))(__t__p0));\
	})

#define SDL_FreeAudioStream(__p0) \
	({ \
		SDL_AudioStream * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(SDL_AudioStream *))*(void**)(__base - 3202))(__t__p0));\
	})

#define SDL_GetMemoryFunctions(__p0, __p1, __p2, __p3) \
	({ \
		SDL_malloc_func * __t__p0 = __p0;\
		SDL_calloc_func * __t__p1 = __p1;\
		SDL_realloc_func * __t__p2 = __p2;\
		SDL_free_func * __t__p3 = __p3;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(SDL_malloc_func *, SDL_calloc_func *, SDL_realloc_func *, SDL_free_func *))*(void**)(__base - 3220))(__t__p0, __t__p1, __t__p2, __t__p3));\
	})

#define SDL_SetMemoryFunctions(__p0, __p1, __p2, __p3) \
	({ \
		SDL_malloc_func  __t__p0 = __p0;\
		SDL_calloc_func  __t__p1 = __p1;\
		SDL_realloc_func  __t__p2 = __p2;\
		SDL_free_func  __t__p3 = __p3;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_malloc_func , SDL_calloc_func , SDL_realloc_func , SDL_free_func ))*(void**)(__base - 3226))(__t__p0, __t__p1, __t__p2, __t__p3));\
	})

#define SDL_GetNumAllocations() \
	({ \
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(void))*(void**)(__base - 3232))());\
	})

#define SDL_RenderGetMetalLayer(__p0) \
	({ \
		SDL_Renderer * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void *(*)(SDL_Renderer *))*(void**)(__base - 3238))(__t__p0));\
	})

#define SDL_RenderGetMetalCommandEncoder(__p0) \
	({ \
		SDL_Renderer * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void *(*)(SDL_Renderer *))*(void**)(__base - 3244))(__t__p0));\
	})

#define SDL_acosf(__p0) \
	({ \
		float  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((float (*)(float ))*(void**)(__base - 3250))(__t__p0));\
	})

#define SDL_asinf(__p0) \
	({ \
		float  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((float (*)(float ))*(void**)(__base - 3256))(__t__p0));\
	})

#define SDL_atanf(__p0) \
	({ \
		float  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((float (*)(float ))*(void**)(__base - 3262))(__t__p0));\
	})

#define SDL_atan2f(__p0, __p1) \
	({ \
		float  __t__p0 = __p0;\
		float  __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((float (*)(float , float ))*(void**)(__base - 3268))(__t__p0, __t__p1));\
	})

#define SDL_ceilf(__p0) \
	({ \
		float  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((float (*)(float ))*(void**)(__base - 3274))(__t__p0));\
	})

#define SDL_copysignf(__p0, __p1) \
	({ \
		float  __t__p0 = __p0;\
		float  __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((float (*)(float , float ))*(void**)(__base - 3280))(__t__p0, __t__p1));\
	})

#define SDL_fabsf(__p0) \
	({ \
		float  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((float (*)(float ))*(void**)(__base - 3286))(__t__p0));\
	})

#define SDL_floorf(__p0) \
	({ \
		float  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((float (*)(float ))*(void**)(__base - 3292))(__t__p0));\
	})

#define SDL_fmod(__p0, __p1) \
	({ \
		double  __t__p0 = __p0;\
		double  __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((double (*)(double , double ))*(void**)(__base - 3298))(__t__p0, __t__p1));\
	})

#define SDL_fmodf(__p0, __p1) \
	({ \
		float  __t__p0 = __p0;\
		float  __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((float (*)(float , float ))*(void**)(__base - 3304))(__t__p0, __t__p1));\
	})

#define SDL_logf(__p0) \
	({ \
		float  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((float (*)(float ))*(void**)(__base - 3310))(__t__p0));\
	})

#define SDL_log10(__p0) \
	({ \
		double  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((double (*)(double ))*(void**)(__base - 3316))(__t__p0));\
	})

#define SDL_log10f(__p0) \
	({ \
		float  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((float (*)(float ))*(void**)(__base - 3322))(__t__p0));\
	})

#define SDL_powf(__p0, __p1) \
	({ \
		float  __t__p0 = __p0;\
		float  __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((float (*)(float , float ))*(void**)(__base - 3328))(__t__p0, __t__p1));\
	})

#define SDL_scalbnf(__p0, __p1) \
	({ \
		float  __t__p0 = __p0;\
		int  __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((float (*)(float , int ))*(void**)(__base - 3334))(__t__p0, __t__p1));\
	})

#define SDL_SetYUVConversionMode(__p0) \
	({ \
		SDL_YUV_CONVERSION_MODE  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(SDL_YUV_CONVERSION_MODE ))*(void**)(__base - 3340))(__t__p0));\
	})

#define SDL_GetYUVConversionMode() \
	({ \
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_YUV_CONVERSION_MODE (*)(void))*(void**)(__base - 3346))());\
	})

#define SDL_GetYUVConversionModeForResolution(__p0, __p1) \
	({ \
		int  __t__p0 = __p0;\
		int  __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_YUV_CONVERSION_MODE (*)(int , int ))*(void**)(__base - 3352))(__t__p0, __t__p1));\
	})

#define SDL_HasAVX512F() \
	({ \
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_bool (*)(void))*(void**)(__base - 3358))());\
	})

#define SDL_GameControllerMappingForDeviceIndex(__p0) \
	({ \
		int  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((char *(*)(int ))*(void**)(__base - 3364))(__t__p0));\
	})

#define SDL_GameControllerGetPlayerIndex(__p0) \
	({ \
		SDL_GameController * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_GameController *))*(void**)(__base - 3370))(__t__p0));\
	})

#define SDL_GameControllerRumble(__p0, __p1, __p2, __p3) \
	({ \
		SDL_GameController * __t__p0 = __p0;\
		Uint16  __t__p1 = __p1;\
		Uint16  __t__p2 = __p2;\
		Uint32  __t__p3 = __p3;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_GameController *, Uint16 , Uint16 , Uint32 ))*(void**)(__base - 3376))(__t__p0, __t__p1, __t__p2, __t__p3));\
	})

#define SDL_JoystickGetDevicePlayerIndex(__p0) \
	({ \
		int  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(int ))*(void**)(__base - 3382))(__t__p0));\
	})

#define SDL_JoystickGetPlayerIndex(__p0) \
	({ \
		SDL_Joystick * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Joystick *))*(void**)(__base - 3388))(__t__p0));\
	})

#define SDL_JoystickRumble(__p0, __p1, __p2, __p3) \
	({ \
		SDL_Joystick * __t__p0 = __p0;\
		Uint16  __t__p1 = __p1;\
		Uint16  __t__p2 = __p2;\
		Uint32  __t__p3 = __p3;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Joystick *, Uint16 , Uint16 , Uint32 ))*(void**)(__base - 3394))(__t__p0, __t__p1, __t__p2, __t__p3));\
	})

#define SDL_wcsdup(__p0) \
	({ \
		const wchar_t * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((wchar_t *(*)(const wchar_t *))*(void**)(__base - 3400))(__t__p0));\
	})

#define SDL_exp(__p0) \
	({ \
		double  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((double (*)(double ))*(void**)(__base - 3406))(__t__p0));\
	})

#define SDL_expf(__p0) \
	({ \
		float  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((float (*)(float ))*(void**)(__base - 3412))(__t__p0));\
	})

#define SDL_HasColorKey(__p0) \
	({ \
		SDL_Surface * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_bool (*)(SDL_Surface *))*(void**)(__base - 3418))(__t__p0));\
	})

#define SDL_IsTablet() \
	({ \
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_bool (*)(void))*(void**)(__base - 3424))());\
	})

#define SDL_CreateThreadWithStackSize(__p0, __p1, __p2, __p3) \
	({ \
		SDL_ThreadFunction  __t__p0 = __p0;\
		const char * __t__p1 = __p1;\
		const size_t  __t__p2 = __p2;\
		void * __t__p3 = __p3;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_Thread *(*)(SDL_ThreadFunction , const char *, const size_t , void *))*(void**)(__base - 3430))(__t__p0, __t__p1, __t__p2, __t__p3));\
	})

#define SDL_GetDisplayOrientation(__p0) \
	({ \
		int  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_DisplayOrientation (*)(int ))*(void**)(__base - 3436))(__t__p0));\
	})

#define SDL_SIMDGetAlignment() \
	({ \
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((size_t (*)(void))*(void**)(__base - 3442))());\
	})

#define SDL_SIMDAlloc(__p0) \
	({ \
		const size_t  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void *(*)(const size_t ))*(void**)(__base - 3448))(__t__p0));\
	})

#define SDL_SIMDFree(__p0) \
	({ \
		void * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(void *))*(void**)(__base - 3454))(__t__p0));\
	})

#define SDL_RenderDrawPointF(__p0, __p1, __p2) \
	({ \
		SDL_Renderer * __t__p0 = __p0;\
		float  __t__p1 = __p1;\
		float  __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Renderer *, float , float ))*(void**)(__base - 3460))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_RenderDrawPointsF(__p0, __p1, __p2) \
	({ \
		SDL_Renderer * __t__p0 = __p0;\
		const SDL_FPoint * __t__p1 = __p1;\
		int  __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Renderer *, const SDL_FPoint *, int ))*(void**)(__base - 3466))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_RenderDrawLineF(__p0, __p1, __p2, __p3, __p4) \
	({ \
		SDL_Renderer * __t__p0 = __p0;\
		float  __t__p1 = __p1;\
		float  __t__p2 = __p2;\
		float  __t__p3 = __p3;\
		float  __t__p4 = __p4;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Renderer *, float , float , float , float ))*(void**)(__base - 3472))(__t__p0, __t__p1, __t__p2, __t__p3, __t__p4));\
	})

#define SDL_RenderDrawLinesF(__p0, __p1, __p2) \
	({ \
		SDL_Renderer * __t__p0 = __p0;\
		const SDL_FPoint * __t__p1 = __p1;\
		int  __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Renderer *, const SDL_FPoint *, int ))*(void**)(__base - 3478))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_RenderDrawRectF(__p0, __p1) \
	({ \
		SDL_Renderer * __t__p0 = __p0;\
		const SDL_FRect * __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Renderer *, const SDL_FRect *))*(void**)(__base - 3484))(__t__p0, __t__p1));\
	})

#define SDL_RenderDrawRectsF(__p0, __p1, __p2) \
	({ \
		SDL_Renderer * __t__p0 = __p0;\
		const SDL_FRect * __t__p1 = __p1;\
		int  __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Renderer *, const SDL_FRect *, int ))*(void**)(__base - 3490))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_RenderFillRectF(__p0, __p1) \
	({ \
		SDL_Renderer * __t__p0 = __p0;\
		const SDL_FRect * __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Renderer *, const SDL_FRect *))*(void**)(__base - 3496))(__t__p0, __t__p1));\
	})

#define SDL_RenderFillRectsF(__p0, __p1, __p2) \
	({ \
		SDL_Renderer * __t__p0 = __p0;\
		const SDL_FRect * __t__p1 = __p1;\
		int  __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Renderer *, const SDL_FRect *, int ))*(void**)(__base - 3502))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_RenderCopyF(__p0, __p1, __p2, __p3) \
	({ \
		SDL_Renderer * __t__p0 = __p0;\
		SDL_Texture * __t__p1 = __p1;\
		const SDL_Rect * __t__p2 = __p2;\
		const SDL_FRect * __t__p3 = __p3;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Renderer *, SDL_Texture *, const SDL_Rect *, const SDL_FRect *))*(void**)(__base - 3508))(__t__p0, __t__p1, __t__p2, __t__p3));\
	})

#define SDL_RenderCopyExF(__p0, __p1, __p2, __p3, __p4, __p5, __p6) \
	({ \
		SDL_Renderer * __t__p0 = __p0;\
		SDL_Texture * __t__p1 = __p1;\
		const SDL_Rect * __t__p2 = __p2;\
		const SDL_FRect * __t__p3 = __p3;\
		const double  __t__p4 = __p4;\
		const SDL_FPoint * __t__p5 = __p5;\
		const SDL_RendererFlip  __t__p6 = __p6;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Renderer *, SDL_Texture *, const SDL_Rect *, const SDL_FRect *, const double , const SDL_FPoint *, const SDL_RendererFlip ))*(void**)(__base - 3514))(__t__p0, __t__p1, __t__p2, __t__p3, __t__p4, __t__p5, __t__p6));\
	})

#define SDL_RenderFlush(__p0) \
	({ \
		SDL_Renderer * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Renderer *))*(void**)(__base - 3520))(__t__p0));\
	})

#define SDL_RWsize(__p0) \
	({ \
		SDL_RWops * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((Sint64 (*)(SDL_RWops *))*(void**)(__base - 3526))(__t__p0));\
	})

#define SDL_RWseek(__p0, __p1, __p2) \
	({ \
		SDL_RWops * __t__p0 = __p0;\
		Sint64  __t__p1 = __p1;\
		int  __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((Sint64 (*)(SDL_RWops *, Sint64 , int ))*(void**)(__base - 3532))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_RWtell(__p0) \
	({ \
		SDL_RWops * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((Sint64 (*)(SDL_RWops *))*(void**)(__base - 3538))(__t__p0));\
	})

#define SDL_RWread(__p0, __p1, __p2, __p3) \
	({ \
		SDL_RWops * __t__p0 = __p0;\
		void * __t__p1 = __p1;\
		size_t  __t__p2 = __p2;\
		size_t  __t__p3 = __p3;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((size_t (*)(SDL_RWops *, void *, size_t , size_t ))*(void**)(__base - 3544))(__t__p0, __t__p1, __t__p2, __t__p3));\
	})

#define SDL_RWwrite(__p0, __p1, __p2, __p3) \
	({ \
		SDL_RWops * __t__p0 = __p0;\
		const void * __t__p1 = __p1;\
		size_t  __t__p2 = __p2;\
		size_t  __t__p3 = __p3;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((size_t (*)(SDL_RWops *, const void *, size_t , size_t ))*(void**)(__base - 3550))(__t__p0, __t__p1, __t__p2, __t__p3));\
	})

#define SDL_RWclose(__p0) \
	({ \
		SDL_RWops * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_RWops *))*(void**)(__base - 3556))(__t__p0));\
	})

#define SDL_LoadFile(__p0, __p1) \
	({ \
		const char * __t__p0 = __p0;\
		size_t * __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void *(*)(const char *, size_t *))*(void**)(__base - 3562))(__t__p0, __t__p1));\
	})

#define SDL_GetTouchDeviceType(__p0) \
	({ \
		SDL_TouchID  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_TouchDeviceType (*)(SDL_TouchID ))*(void**)(__base - 3568))(__t__p0));\
	})

#define SDL_HasARMSIMD() \
	({ \
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_bool (*)(void))*(void**)(__base - 3574))());\
	})

#define SDL_GameControllerTypeForIndex(__p0) \
	({ \
		int  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_GameControllerType (*)(int ))*(void**)(__base - 3580))(__t__p0));\
	})

#define SDL_GameControllerFromPlayerIndex(__p0) \
	({ \
		int  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_GameController *(*)(int ))*(void**)(__base - 3586))(__t__p0));\
	})

#define SDL_GameControllerGetType(__p0) \
	({ \
		SDL_GameController * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_GameControllerType (*)(SDL_GameController *))*(void**)(__base - 3592))(__t__p0));\
	})

#define SDL_GameControllerSetPlayerIndex(__p0, __p1) \
	({ \
		SDL_GameController * __t__p0 = __p0;\
		int  __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(SDL_GameController *, int ))*(void**)(__base - 3598))(__t__p0, __t__p1));\
	})

#define SDL_JoystickFromPlayerIndex(__p0) \
	({ \
		int  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_Joystick *(*)(int ))*(void**)(__base - 3604))(__t__p0));\
	})

#define SDL_JoystickSetPlayerIndex(__p0, __p1) \
	({ \
		SDL_Joystick * __t__p0 = __p0;\
		int  __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_Joystick *(*)(SDL_Joystick *, int ))*(void**)(__base - 3610))(__t__p0, __t__p1));\
	})

#define SDL_SetTextureScaleMode(__p0, __p1) \
	({ \
		SDL_Texture * __t__p0 = __p0;\
		SDL_ScaleMode  __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Texture *, SDL_ScaleMode ))*(void**)(__base - 3616))(__t__p0, __t__p1));\
	})

#define SDL_GetTextureScaleMode(__p0, __p1) \
	({ \
		SDL_Texture * __t__p0 = __p0;\
		SDL_ScaleMode * __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Texture *, SDL_ScaleMode *))*(void**)(__base - 3622))(__t__p0, __t__p1));\
	})

#define SDL_LockTextureToSurface(__p0, __p1, __p2) \
	({ \
		SDL_Texture * __t__p0 = __p0;\
		const SDL_Rect * __t__p1 = __p1;\
		SDL_Surface ** __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Texture *, const SDL_Rect *, SDL_Surface **))*(void**)(__base - 3628))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_wcsstr(__p0, __p1) \
	({ \
		const wchar_t * __t__p0 = __p0;\
		const wchar_t * __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((wchar_t *(*)(const wchar_t *, const wchar_t *))*(void**)(__base - 3634))(__t__p0, __t__p1));\
	})

#define SDL_wcsncmp(__p0, __p1, __p2) \
	({ \
		const wchar_t * __t__p0 = __p0;\
		const wchar_t * __t__p1 = __p1;\
		size_t  __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(const wchar_t *, const wchar_t *, size_t ))*(void**)(__base - 3640))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_strtokr(__p0, __p1, __p2) \
	({ \
		char * __t__p0 = __p0;\
		const char * __t__p1 = __p1;\
		char ** __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((char *(*)(char *, const char *, char **))*(void**)(__base - 3646))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_isupper(__p0) \
	({ \
		int  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(int ))*(void**)(__base - 3928))(__t__p0));\
	})

#define SDL_islower(__p0) \
	({ \
		int  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(int ))*(void**)(__base - 3934))(__t__p0));\
	})

#define SDL_JoystickAttachVirtual(__p0, __p1, __p2, __p3) \
	({ \
		SDL_JoystickType  __t__p0 = __p0;\
		int  __t__p1 = __p1;\
		int  __t__p2 = __p2;\
		int  __t__p3 = __p3;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_JoystickType , int , int , int ))*(void**)(__base - 3940))(__t__p0, __t__p1, __t__p2, __t__p3));\
	})

#define SDL_JoystickDetachVirtual(__p0) \
	({ \
		int  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(int ))*(void**)(__base - 3946))(__t__p0));\
	})

#define SDL_JoystickIsVirtual(__p0) \
	({ \
		int  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_bool (*)(int ))*(void**)(__base - 3952))(__t__p0));\
	})

#define SDL_JoystickSetVirtualAxis(__p0, __p1, __p2) \
	({ \
		SDL_Joystick * __t__p0 = __p0;\
		int  __t__p1 = __p1;\
		Sint16  __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Joystick *, int , Sint16 ))*(void**)(__base - 3958))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_JoystickSetVirtualButton(__p0, __p1, __p2) \
	({ \
		SDL_Joystick * __t__p0 = __p0;\
		int  __t__p1 = __p1;\
		Uint8  __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Joystick *, int , Uint8 ))*(void**)(__base - 3964))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_JoystickSetVirtualHat(__p0, __p1, __p2) \
	({ \
		SDL_Joystick * __t__p0 = __p0;\
		int  __t__p1 = __p1;\
		Uint8  __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Joystick *, int , Uint8 ))*(void**)(__base - 3970))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_GetErrorMsg(__p0, __p1) \
	({ \
		char * __t__p0 = __p0;\
		int  __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((char *(*)(char *, int ))*(void**)(__base - 3976))(__t__p0, __t__p1));\
	})

#define SDL_LockSensors() \
	({ \
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(void))*(void**)(__base - 3982))());\
	})

#define SDL_UnlockSensors() \
	({ \
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(void))*(void**)(__base - 3988))());\
	})

#define SDL_Metal_GetLayer(__p0) \
	({ \
		SDL_MetalView  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void *(*)(SDL_MetalView ))*(void**)(__base - 3994))(__t__p0));\
	})

#define SDL_Metal_GetDrawableSize(__p0, __p1, __p2) \
	({ \
		SDL_Window * __t__p0 = __p0;\
		int * __t__p1 = __p1;\
		int * __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(SDL_Window *, int *, int *))*(void**)(__base - 4000))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_trunc(__p0) \
	({ \
		double  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((double (*)(double ))*(void**)(__base - 4006))(__t__p0));\
	})

#define SDL_truncf(__p0) \
	({ \
		float  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((float (*)(float ))*(void**)(__base - 4012))(__t__p0));\
	})

#define SDL_GetPreferredLocales() \
	({ \
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_Locale *(*)(void))*(void**)(__base - 4018))());\
	})

#define SDL_SIMDRealloc(__p0, __p1) \
	({ \
		void * __t__p0 = __p0;\
		const size_t  __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void *(*)(void *, const size_t ))*(void**)(__base - 4024))(__t__p0, __t__p1));\
	})

#define SDL_OpenURL(__p0) \
	({ \
		const char * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(const char *))*(void**)(__base - 4030))(__t__p0));\
	})

#define SDL_HasSurfaceRLE(__p0) \
	({ \
		SDL_Surface * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_bool (*)(SDL_Surface *))*(void**)(__base - 4036))(__t__p0));\
	})

#define SDL_GameControllerHasLED(__p0) \
	({ \
		SDL_GameController * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_bool (*)(SDL_GameController *))*(void**)(__base - 4042))(__t__p0));\
	})

#define SDL_GameControllerSetLED(__p0, __p1, __p2, __p3) \
	({ \
		SDL_GameController * __t__p0 = __p0;\
		Uint8  __t__p1 = __p1;\
		Uint8  __t__p2 = __p2;\
		Uint8  __t__p3 = __p3;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_GameController *, Uint8 , Uint8 , Uint8 ))*(void**)(__base - 4048))(__t__p0, __t__p1, __t__p2, __t__p3));\
	})

#define SDL_JoystickHasLED(__p0) \
	({ \
		SDL_Joystick * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_bool (*)(SDL_Joystick *))*(void**)(__base - 4054))(__t__p0));\
	})

#define SDL_JoystickSetLED(__p0, __p1, __p2, __p3) \
	({ \
		SDL_Joystick * __t__p0 = __p0;\
		Uint8  __t__p1 = __p1;\
		Uint8  __t__p2 = __p2;\
		Uint8  __t__p3 = __p3;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Joystick *, Uint8 , Uint8 , Uint8 ))*(void**)(__base - 4060))(__t__p0, __t__p1, __t__p2, __t__p3));\
	})

#define SDL_GameControllerRumbleTriggers(__p0, __p1, __p2, __p3) \
	({ \
		SDL_GameController * __t__p0 = __p0;\
		Uint16  __t__p1 = __p1;\
		Uint16  __t__p2 = __p2;\
		Uint32  __t__p3 = __p3;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_GameController *, Uint16 , Uint16 , Uint32 ))*(void**)(__base - 4066))(__t__p0, __t__p1, __t__p2, __t__p3));\
	})

#define SDL_JoystickRumbleTriggers(__p0, __p1, __p2, __p3) \
	({ \
		SDL_Joystick * __t__p0 = __p0;\
		Uint16  __t__p1 = __p1;\
		Uint16  __t__p2 = __p2;\
		Uint32  __t__p3 = __p3;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Joystick *, Uint16 , Uint16 , Uint32 ))*(void**)(__base - 4072))(__t__p0, __t__p1, __t__p2, __t__p3));\
	})

#define SDL_GameControllerHasAxis(__p0, __p1) \
	({ \
		SDL_GameController * __t__p0 = __p0;\
		SDL_GameControllerAxis  __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_bool (*)(SDL_GameController *, SDL_GameControllerAxis ))*(void**)(__base - 4078))(__t__p0, __t__p1));\
	})

#define SDL_GameControllerHasButton(__p0, __p1) \
	({ \
		SDL_GameController * __t__p0 = __p0;\
		SDL_GameControllerButton  __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_bool (*)(SDL_GameController *, SDL_GameControllerButton ))*(void**)(__base - 4084))(__t__p0, __t__p1));\
	})

#define SDL_GameControllerGetNumTouchpads(__p0) \
	({ \
		SDL_GameController * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_GameController *))*(void**)(__base - 4090))(__t__p0));\
	})

#define SDL_GameControllerGetNumTouchpadFingers(__p0, __p1) \
	({ \
		SDL_GameController * __t__p0 = __p0;\
		int  __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_GameController *, int ))*(void**)(__base - 4096))(__t__p0, __t__p1));\
	})

#define SDL_GameControllerGetTouchpadFinger(__p0, __p1, __p2, __p3, __p4, __p5, __p6) \
	({ \
		SDL_GameController * __t__p0 = __p0;\
		int  __t__p1 = __p1;\
		int  __t__p2 = __p2;\
		Uint8 * __t__p3 = __p3;\
		float * __t__p4 = __p4;\
		float * __t__p5 = __p5;\
		float * __t__p6 = __p6;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_GameController *, int , int , Uint8 *, float *, float *, float *))*(void**)(__base - 4102))(__t__p0, __t__p1, __t__p2, __t__p3, __t__p4, __t__p5, __t__p6));\
	})

#define SDL_GetNumTouchDevices() \
	({ \
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(void))*(void**)(__base - 4108))());\
	})

#define SDL_GetTouchDevice(__p0) \
	({ \
		int  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_TouchID (*)(int ))*(void**)(__base - 4114))(__t__p0));\
	})

#define SDL_GetNumTouchFingers(__p0) \
	({ \
		SDL_TouchID  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_TouchID ))*(void**)(__base - 4120))(__t__p0));\
	})

#define SDL_GetTouchFinger(__p0, __p1) \
	({ \
		SDL_TouchID  __t__p0 = __p0;\
		int  __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_Finger *(*)(SDL_TouchID , int ))*(void**)(__base - 4126))(__t__p0, __t__p1));\
	})

#define SDL_crc32(__p0, __p1, __p2) \
	({ \
		Uint32  __t__p0 = __p0;\
		const void * __t__p1 = __p1;\
		size_t  __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((Uint32 (*)(Uint32 , const void *, size_t ))*(void**)(__base - 4132))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_GameControllerGetSerial(__p0) \
	({ \
		SDL_GameController * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((const char *(*)(SDL_GameController *))*(void**)(__base - 4138))(__t__p0));\
	})

#define SDL_JoystickGetSerial(__p0) \
	({ \
		SDL_Joystick * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((const char *(*)(SDL_Joystick *))*(void**)(__base - 4144))(__t__p0));\
	})

#define SDL_GameControllerHasSensor(__p0, __p1) \
	({ \
		SDL_GameController * __t__p0 = __p0;\
		SDL_SensorType  __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_bool (*)(SDL_GameController *, SDL_SensorType ))*(void**)(__base - 4150))(__t__p0, __t__p1));\
	})

#define SDL_GameControllerSetSensorEnabled(__p0, __p1, __p2) \
	({ \
		SDL_GameController * __t__p0 = __p0;\
		SDL_SensorType  __t__p1 = __p1;\
		SDL_bool  __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_GameController *, SDL_SensorType , SDL_bool ))*(void**)(__base - 4156))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_GameControllerIsSensorEnabled(__p0, __p1) \
	({ \
		SDL_GameController * __t__p0 = __p0;\
		SDL_SensorType  __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_bool (*)(SDL_GameController *, SDL_SensorType ))*(void**)(__base - 4162))(__t__p0, __t__p1));\
	})

#define SDL_GameControllerGetSensorData(__p0, __p1, __p2, __p3) \
	({ \
		SDL_GameController * __t__p0 = __p0;\
		SDL_SensorType  __t__p1 = __p1;\
		float * __t__p2 = __p2;\
		int  __t__p3 = __p3;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_GameController *, SDL_SensorType , float *, int ))*(void**)(__base - 4168))(__t__p0, __t__p1, __t__p2, __t__p3));\
	})

#define SDL_wcscasecmp(__p0, __p1) \
	({ \
		const wchar_t * __t__p0 = __p0;\
		const wchar_t * __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(const wchar_t *, const wchar_t *))*(void**)(__base - 4174))(__t__p0, __t__p1));\
	})

#define SDL_wcsncasecmp(__p0, __p1, __p2) \
	({ \
		const wchar_t * __t__p0 = __p0;\
		const wchar_t * __t__p1 = __p1;\
		size_t  __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(const wchar_t *, const wchar_t *, size_t ))*(void**)(__base - 4180))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_CopyAndSwap16(__p0, __p1, __p2) \
	({ \
		APTR  __t__p0 = __p0;\
		APTR  __t__p1 = __p1;\
		LONG  __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(APTR , APTR , LONG ))*(void**)(__base - 4186))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_CopyAndSwap32(__p0, __p1, __p2) \
	({ \
		APTR  __t__p0 = __p0;\
		APTR  __t__p1 = __p1;\
		LONG  __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(APTR , APTR , LONG ))*(void**)(__base - 4192))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_UpdateNVTexture(__p0, __p1, __p2, __p3, __p4, __p5) \
	({ \
		SDL_Texture * __t__p0 = __p0;\
		const SDL_Rect * __t__p1 = __p1;\
		const Uint8 * __t__p2 = __p2;\
		int  __t__p3 = __p3;\
		const Uint8 * __t__p4 = __p4;\
		int  __t__p5 = __p5;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Texture *, const SDL_Rect *, const Uint8 *, int , const Uint8 *, int ))*(void**)(__base - 4198))(__t__p0, __t__p1, __t__p2, __t__p3, __t__p4, __t__p5));\
	})

#define SDL_round(__p0) \
	({ \
		double  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((double (*)(double ))*(void**)(__base - 4204))(__t__p0));\
	})

#define SDL_roundf(__p0) \
	({ \
		float  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((float (*)(float ))*(void**)(__base - 4210))(__t__p0));\
	})

#define SDL_lround(__p0) \
	({ \
		double  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((long (*)(double ))*(void**)(__base - 4216))(__t__p0));\
	})

#define SDL_lroundf(__p0) \
	({ \
		float  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((long (*)(float ))*(void**)(__base - 4222))(__t__p0));\
	})

#define SDL_SoftStretchLinear(__p0, __p1, __p2, __p3) \
	({ \
		SDL_Surface * __t__p0 = __p0;\
		const SDL_Rect * __t__p1 = __p1;\
		SDL_Surface * __t__p2 = __p2;\
		const SDL_Rect * __t__p3 = __p3;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Surface *, const SDL_Rect *, SDL_Surface *, const SDL_Rect *))*(void**)(__base - 4228))(__t__p0, __t__p1, __t__p2, __t__p3));\
	})

#define SDL_SetWindowKeyboardGrab(__p0, __p1) \
	({ \
		SDL_Window * __t__p0 = __p0;\
		SDL_bool  __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(SDL_Window *, SDL_bool ))*(void**)(__base - 4234))(__t__p0, __t__p1));\
	})

#define SDL_SetWindowMouseGrab(__p0, __p1) \
	({ \
		SDL_Window * __t__p0 = __p0;\
		SDL_bool  __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(SDL_Window *, SDL_bool ))*(void**)(__base - 4240))(__t__p0, __t__p1));\
	})

#define SDL_GetWindowKeyboardGrab(__p0) \
	({ \
		SDL_Window * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_bool (*)(SDL_Window *))*(void**)(__base - 4246))(__t__p0));\
	})

#define SDL_GetWindowMouseGrab(__p0) \
	({ \
		SDL_Window * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_bool (*)(SDL_Window *))*(void**)(__base - 4252))(__t__p0));\
	})

#define SDL_isalpha(__p0) \
	({ \
		int  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(int ))*(void**)(__base - 4258))(__t__p0));\
	})

#define SDL_isalnum(__p0) \
	({ \
		int  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(int ))*(void**)(__base - 4264))(__t__p0));\
	})

#define SDL_isblank(__p0) \
	({ \
		int  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(int ))*(void**)(__base - 4270))(__t__p0));\
	})

#define SDL_iscntrl(__p0) \
	({ \
		int  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(int ))*(void**)(__base - 4276))(__t__p0));\
	})

#define SDL_isxdigit(__p0) \
	({ \
		int  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(int ))*(void**)(__base - 4282))(__t__p0));\
	})

#define SDL_ispunct(__p0) \
	({ \
		int  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(int ))*(void**)(__base - 4288))(__t__p0));\
	})

#define SDL_isprint(__p0) \
	({ \
		int  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(int ))*(void**)(__base - 4294))(__t__p0));\
	})

#define SDL_isgraph(__p0) \
	({ \
		int  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(int ))*(void**)(__base - 4300))(__t__p0));\
	})

#define SDL_GetAudioDeviceSpec(__p0, __p1, __p2) \
	({ \
		int  __t__p0 = __p0;\
		int  __t__p1 = __p1;\
		SDL_AudioSpec * __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(int , int , SDL_AudioSpec *))*(void**)(__base - 4306))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_TLSCleanup() \
	({ \
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(void))*(void**)(__base - 4312))());\
	})

#define SDL_SetWindowAlwaysOnTop(__p0, __p1) \
	({ \
		SDL_Window * __t__p0 = __p0;\
		SDL_bool  __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(SDL_Window *, SDL_bool ))*(void**)(__base - 4318))(__t__p0, __t__p1));\
	})

#define SDL_FlashWindow(__p0, __p1) \
	({ \
		SDL_Window * __t__p0 = __p0;\
		SDL_FlashOperation  __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Window *, SDL_FlashOperation ))*(void**)(__base - 4324))(__t__p0, __t__p1));\
	})

#define SDL_GameControllerSendEffect(__p0, __p1, __p2) \
	({ \
		SDL_GameController * __t__p0 = __p0;\
		const void * __t__p1 = __p1;\
		int  __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_GameController *, const void *, int ))*(void**)(__base - 4330))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_JoystickSendEffect(__p0, __p1, __p2) \
	({ \
		SDL_Joystick * __t__p0 = __p0;\
		const void * __t__p1 = __p1;\
		int  __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Joystick *, const void *, int ))*(void**)(__base - 4336))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_GameControllerGetSensorDataRate(__p0, __p1) \
	({ \
		SDL_GameController * __t__p0 = __p0;\
		SDL_SensorType  __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((float (*)(SDL_GameController *, SDL_SensorType ))*(void**)(__base - 4342))(__t__p0, __t__p1));\
	})

#define SDL_SetTextureUserData(__p0, __p1) \
	({ \
		SDL_Texture * __t__p0 = __p0;\
		void * __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Texture *, void *))*(void**)(__base - 4348))(__t__p0, __t__p1));\
	})

#define SDL_GetTextureUserData(__p0) \
	({ \
		SDL_Texture * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void *(*)(SDL_Texture *))*(void**)(__base - 4354))(__t__p0));\
	})

#define SDL_RenderGeometry(__p0, __p1, __p2, __p3, __p4, __p5) \
	({ \
		SDL_Renderer * __t__p0 = __p0;\
		SDL_Texture * __t__p1 = __p1;\
		const SDL_Vertex * __t__p2 = __p2;\
		int  __t__p3 = __p3;\
		const int * __t__p4 = __p4;\
		int  __t__p5 = __p5;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Renderer *, SDL_Texture *, const SDL_Vertex *, int , const int *, int ))*(void**)(__base - 4360))(__t__p0, __t__p1, __t__p2, __t__p3, __t__p4, __t__p5));\
	})

#define SDL_RenderGeometryRaw(__p0, __p1, __p2, __p3, __p4, __p5, __p6, __p7, __p8, __p9, __p10, __p11) \
	({ \
		SDL_Renderer * __t__p0 = __p0;\
		SDL_Texture * __t__p1 = __p1;\
		const float * __t__p2 = __p2;\
		int  __t__p3 = __p3;\
		const int * __t__p4 = __p4;\
		int  __t__p5 = __p5;\
		const float * __t__p6 = __p6;\
		int  __t__p7 = __p7;\
		int  __t__p8 = __p8;\
		const void * __t__p9 = __p9;\
		int  __t__p10 = __p10;\
		int  __t__p11 = __p11;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Renderer *, SDL_Texture *, const float *, int , const int *, int , const float *, int , int , const void *, int , int ))*(void**)(__base - 4366))(__t__p0, __t__p1, __t__p2, __t__p3, __t__p4, __t__p5, __t__p6, __t__p7, __t__p8, __t__p9, __t__p10, __t__p11));\
	})

#define SDL_RenderSetVSync(__p0, __p1) \
	({ \
		SDL_Renderer * __t__p0 = __p0;\
		int  __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Renderer *, int ))*(void**)(__base - 4372))(__t__p0, __t__p1));\
	})

#define SDL_vasprintf(__p0, __p1, __p2) \
	({ \
		char ** __t__p0 = __p0;\
		const char * __t__p1 = __p1;\
		va_list __t__p2;\
		va_copy(__t__p2, __p2);\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(char **, const char *, va_list ))*(void**)(__base - 4378))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_GetWindowICCProfile(__p0, __p1) \
	({ \
		SDL_Window * __t__p0 = __p0;\
		size_t * __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void *(*)(SDL_Window *, size_t *))*(void**)(__base - 4384))(__t__p0, __t__p1));\
	})

#define SDL_GetTicks64() \
	({ \
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((Uint64 (*)(void))*(void**)(__base - 4390))());\
	})

#define SDL_GameControllerGetAppleSFSymbolsNameForButton(__p0, __p1) \
	({ \
		SDL_GameController * __t__p0 = __p0;\
		SDL_GameControllerButton  __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((const char *(*)(SDL_GameController *, SDL_GameControllerButton ))*(void**)(__base - 4396))(__t__p0, __t__p1));\
	})

#define SDL_GameControllerGetAppleSFSymbolsNameForAxis(__p0, __p1) \
	({ \
		SDL_GameController * __t__p0 = __p0;\
		SDL_GameControllerAxis  __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((const char *(*)(SDL_GameController *, SDL_GameControllerAxis ))*(void**)(__base - 4402))(__t__p0, __t__p1));\
	})

#define SDL_hid_init() \
	({ \
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(void))*(void**)(__base - 4408))());\
	})

#define SDL_hid_exit() \
	({ \
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(void))*(void**)(__base - 4414))());\
	})

#define SDL_hid_device_change_count() \
	({ \
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((Uint32 (*)(void))*(void**)(__base - 4420))());\
	})

#define SDL_hid_enumerate(__p0, __p1) \
	({ \
		unsigned short  __t__p0 = __p0;\
		unsigned short  __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_hid_device_info *(*)(unsigned short , unsigned short ))*(void**)(__base - 4426))(__t__p0, __t__p1));\
	})

#define SDL_hid_free_enumeration(__p0) \
	({ \
		SDL_hid_device_info * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(SDL_hid_device_info *))*(void**)(__base - 4432))(__t__p0));\
	})

#define SDL_hid_open(__p0, __p1, __p2) \
	({ \
		unsigned short  __t__p0 = __p0;\
		unsigned short  __t__p1 = __p1;\
		const wchar_t * __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_hid_device *(*)(unsigned short , unsigned short , const wchar_t *))*(void**)(__base - 4438))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_hid_open_path(__p0, __p1) \
	({ \
		const char * __t__p0 = __p0;\
		int  __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_hid_device *(*)(const char *, int ))*(void**)(__base - 4444))(__t__p0, __t__p1));\
	})

#define SDL_hid_write(__p0, __p1, __p2) \
	({ \
		SDL_hid_device * __t__p0 = __p0;\
		const unsigned char * __t__p1 = __p1;\
		size_t  __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_hid_device *, const unsigned char *, size_t ))*(void**)(__base - 4450))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_hid_read_timeout(__p0, __p1, __p2, __p3) \
	({ \
		SDL_hid_device * __t__p0 = __p0;\
		unsigned char * __t__p1 = __p1;\
		size_t  __t__p2 = __p2;\
		int  __t__p3 = __p3;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_hid_device *, unsigned char *, size_t , int ))*(void**)(__base - 4456))(__t__p0, __t__p1, __t__p2, __t__p3));\
	})

#define SDL_hid_read(__p0, __p1, __p2) \
	({ \
		SDL_hid_device * __t__p0 = __p0;\
		unsigned char * __t__p1 = __p1;\
		size_t  __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_hid_device *, unsigned char *, size_t ))*(void**)(__base - 4462))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_hid_set_nonblocking(__p0, __p1) \
	({ \
		SDL_hid_device * __t__p0 = __p0;\
		int  __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_hid_device *, int ))*(void**)(__base - 4468))(__t__p0, __t__p1));\
	})

#define SDL_hid_send_feature_report(__p0, __p1, __p2) \
	({ \
		SDL_hid_device * __t__p0 = __p0;\
		const unsigned char * __t__p1 = __p1;\
		size_t  __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_hid_device *, const unsigned char *, size_t ))*(void**)(__base - 4474))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_hid_get_feature_report(__p0, __p1, __p2) \
	({ \
		SDL_hid_device * __t__p0 = __p0;\
		unsigned char * __t__p1 = __p1;\
		size_t  __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_hid_device *, unsigned char *, size_t ))*(void**)(__base - 4480))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_hid_close(__p0) \
	({ \
		SDL_hid_device * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(SDL_hid_device *))*(void**)(__base - 4486))(__t__p0));\
	})

#define SDL_hid_get_manufacturer_string(__p0, __p1, __p2) \
	({ \
		SDL_hid_device * __t__p0 = __p0;\
		wchar_t * __t__p1 = __p1;\
		size_t  __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_hid_device *, wchar_t *, size_t ))*(void**)(__base - 4492))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_hid_get_product_string(__p0, __p1, __p2) \
	({ \
		SDL_hid_device * __t__p0 = __p0;\
		wchar_t * __t__p1 = __p1;\
		size_t  __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_hid_device *, wchar_t *, size_t ))*(void**)(__base - 4498))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_hid_get_serial_number_string(__p0, __p1, __p2) \
	({ \
		SDL_hid_device * __t__p0 = __p0;\
		wchar_t * __t__p1 = __p1;\
		size_t  __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_hid_device *, wchar_t *, size_t ))*(void**)(__base - 4504))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_hid_get_indexed_string(__p0, __p1, __p2, __p3) \
	({ \
		SDL_hid_device * __t__p0 = __p0;\
		int  __t__p1 = __p1;\
		wchar_t * __t__p2 = __p2;\
		size_t  __t__p3 = __p3;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_hid_device *, int , wchar_t *, size_t ))*(void**)(__base - 4510))(__t__p0, __t__p1, __t__p2, __t__p3));\
	})

#define SDL_SetWindowMouseRect(__p0, __p1) \
	({ \
		SDL_Window * __t__p0 = __p0;\
		const SDL_Rect * __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Window *, const SDL_Rect *))*(void**)(__base - 4516))(__t__p0, __t__p1));\
	})

#define SDL_GetWindowMouseRect(__p0) \
	({ \
		SDL_Window * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((const SDL_Rect *(*)(SDL_Window *))*(void**)(__base - 4522))(__t__p0));\
	})

#define SDL_RenderWindowToLogical(__p0, __p1, __p2, __p3, __p4) \
	({ \
		SDL_Renderer * __t__p0 = __p0;\
		int  __t__p1 = __p1;\
		int  __t__p2 = __p2;\
		float * __t__p3 = __p3;\
		float * __t__p4 = __p4;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(SDL_Renderer *, int , int , float *, float *))*(void**)(__base - 4528))(__t__p0, __t__p1, __t__p2, __t__p3, __t__p4));\
	})

#define SDL_RenderLogicalToWindow(__p0, __p1, __p2, __p3, __p4) \
	({ \
		SDL_Renderer * __t__p0 = __p0;\
		float  __t__p1 = __p1;\
		float  __t__p2 = __p2;\
		int * __t__p3 = __p3;\
		int * __t__p4 = __p4;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(SDL_Renderer *, float , float , int *, int *))*(void**)(__base - 4534))(__t__p0, __t__p1, __t__p2, __t__p3, __t__p4));\
	})

#define SDL_JoystickHasRumble(__p0) \
	({ \
		SDL_Joystick * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_bool (*)(SDL_Joystick *))*(void**)(__base - 4540))(__t__p0));\
	})

#define SDL_JoystickHasRumbleTriggers(__p0) \
	({ \
		SDL_Joystick * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_bool (*)(SDL_Joystick *))*(void**)(__base - 4546))(__t__p0));\
	})

#define SDL_GameControllerHasRumble(__p0) \
	({ \
		SDL_GameController * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_bool (*)(SDL_GameController *))*(void**)(__base - 4552))(__t__p0));\
	})

#define SDL_GameControllerHasRumbleTriggers(__p0) \
	({ \
		SDL_GameController * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_bool (*)(SDL_GameController *))*(void**)(__base - 4558))(__t__p0));\
	})

#define SDL_hid_ble_scan(__p0) \
	({ \
		SDL_bool  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(SDL_bool ))*(void**)(__base - 4564))(__t__p0));\
	})

#define SDL_PremultiplyAlpha(__p0, __p1, __p2, __p3, __p4, __p5, __p6, __p7) \
	({ \
		int  __t__p0 = __p0;\
		int  __t__p1 = __p1;\
		Uint32  __t__p2 = __p2;\
		const void * __t__p3 = __p3;\
		int  __t__p4 = __p4;\
		Uint32  __t__p5 = __p5;\
		void * __t__p6 = __p6;\
		int  __t__p7 = __p7;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(int , int , Uint32 , const void *, int , Uint32 , void *, int ))*(void**)(__base - 4570))(__t__p0, __t__p1, __t__p2, __t__p3, __t__p4, __t__p5, __t__p6, __t__p7));\
	})

#define SDL_getenv(__p0) \
	({ \
		const char * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((char *(*)(const char *))*(void**)(__base - 4576))(__t__p0));\
	})

#define SDL_setenv(__p0, __p1, __p2) \
	({ \
		const char * __t__p0 = __p0;\
		const char * __t__p1 = __p1;\
		int  __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(const char *, const char *, int ))*(void**)(__base - 4582))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_GetTouchName(__p0) \
	({ \
		int  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((const char *(*)(int ))*(void**)(__base - 4588))(__t__p0));\
	})

#define SDL_ClearComposition() \
	({ \
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(void))*(void**)(__base - 4594))());\
	})

#define SDL_IsTextInputShown() \
	({ \
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_bool (*)(void))*(void**)(__base - 4600))());\
	})

#define SDL_HasIntersectionF(__p0, __p1) \
	({ \
		const SDL_FRect * __t__p0 = __p0;\
		const SDL_FRect * __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_bool (*)(const SDL_FRect *, const SDL_FRect *))*(void**)(__base - 4606))(__t__p0, __t__p1));\
	})

#define SDL_IntersectFRect(__p0, __p1, __p2) \
	({ \
		const SDL_FRect * __t__p0 = __p0;\
		const SDL_FRect * __t__p1 = __p1;\
		SDL_FRect * __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_bool (*)(const SDL_FRect *, const SDL_FRect *, SDL_FRect *))*(void**)(__base - 4612))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_UnionFRect(__p0, __p1, __p2) \
	({ \
		const SDL_FRect * __t__p0 = __p0;\
		const SDL_FRect * __t__p1 = __p1;\
		SDL_FRect * __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(const SDL_FRect *, const SDL_FRect *, SDL_FRect *))*(void**)(__base - 4618))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_EncloseFPoints(__p0, __p1, __p2, __p3) \
	({ \
		const SDL_FPoint * __t__p0 = __p0;\
		int  __t__p1 = __p1;\
		const SDL_FRect * __t__p2 = __p2;\
		SDL_FRect * __t__p3 = __p3;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_bool (*)(const SDL_FPoint *, int , const SDL_FRect *, SDL_FRect *))*(void**)(__base - 4624))(__t__p0, __t__p1, __t__p2, __t__p3));\
	})

#define SDL_IntersectFRectAndLine(__p0, __p1, __p2, __p3, __p4) \
	({ \
		const SDL_FRect * __t__p0 = __p0;\
		float * __t__p1 = __p1;\
		float * __t__p2 = __p2;\
		float * __t__p3 = __p3;\
		float * __t__p4 = __p4;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_bool (*)(const SDL_FRect *, float *, float *, float *, float *))*(void**)(__base - 4630))(__t__p0, __t__p1, __t__p2, __t__p3, __t__p4));\
	})

#define SDL_RenderGetWindow(__p0) \
	({ \
		SDL_Renderer * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_Window *(*)(SDL_Renderer *))*(void**)(__base - 4636))(__t__p0));\
	})

#define SDL_bsearch(__p0, __p1, __p2, __p3, __p4) \
	({ \
		const void * __t__p0 = __p0;\
		const void * __t__p1 = __p1;\
		size_t  __t__p2 = __p2;\
		size_t  __t__p3 = __p3;\
		SDL_CompareCallback  __t__p4 = __p4;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void *(*)(const void *, const void *, size_t , size_t , SDL_CompareCallback ))*(void**)(__base - 4642))(__t__p0, __t__p1, __t__p2, __t__p3, __t__p4));\
	})

#define SDL_GameControllerPathForIndex(__p0) \
	({ \
		int  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((const char *(*)(int ))*(void**)(__base - 4648))(__t__p0));\
	})

#define SDL_GameControllerPath(__p0) \
	({ \
		SDL_GameController * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((const char *(*)(SDL_GameController *))*(void**)(__base - 4654))(__t__p0));\
	})

#define SDL_JoystickPathForIndex(__p0) \
	({ \
		int  __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((const char *(*)(int ))*(void**)(__base - 4660))(__t__p0));\
	})

#define SDL_JoystickPath(__p0) \
	({ \
		SDL_Joystick * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((const char *(*)(SDL_Joystick *))*(void**)(__base - 4666))(__t__p0));\
	})

#define SDL_JoystickAttachVirtualEx(__p0) \
	({ \
		const SDL_VirtualJoystickDesc * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(const SDL_VirtualJoystickDesc *))*(void**)(__base - 4672))(__t__p0));\
	})

#define SDL_HasLSX() \
	({ \
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_bool (*)(void))*(void**)(__base - 4678))());\
	})

#define SDL_HasLASX() \
	({ \
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_bool (*)(void))*(void**)(__base - 4684))());\
	})

#define SDL_GameControllerGetFirmwareVersion(__p0) \
	({ \
		SDL_GameController * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((Uint16 (*)(SDL_GameController *))*(void**)(__base - 4690))(__t__p0));\
	})

#define SDL_GUIDToString(__p0, __p1, __p2) \
	({ \
		SDL_GUID  __t__p0 = __p0;\
		char * __t__p1 = __p1;\
		int  __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(SDL_GUID , char *, int ))*(void**)(__base - 4696))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_GUIDFromString(__p0) \
	({ \
		const char * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_GUID (*)(const char *))*(void**)(__base - 4702))(__t__p0));\
	})

#define SDL_JoystickGetFirmwareVersion(__p0) \
	({ \
		SDL_Joystick * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((Uint16 (*)(SDL_Joystick *))*(void**)(__base - 4708))(__t__p0));\
	})

#define SDL_GetOriginalMemoryFunctions(__p0, __p1, __p2, __p3) \
	({ \
		SDL_malloc_func * __t__p0 = __p0;\
		SDL_calloc_func * __t__p1 = __p1;\
		SDL_realloc_func * __t__p2 = __p2;\
		SDL_free_func * __t__p3 = __p3;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_malloc_func *, SDL_calloc_func *, SDL_realloc_func *, SDL_free_func *))*(void**)(__base - 4714))(__t__p0, __t__p1, __t__p2, __t__p3));\
	})

#define SDL_ResetKeyboard() \
	({ \
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(void))*(void**)(__base - 4720))());\
	})

#define SDL_GetPointDisplayIndex(__p0) \
	({ \
		const SDL_Point * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(const SDL_Point *))*(void**)(__base - 4726))(__t__p0));\
	})

#define SDL_GetRectDisplayIndex(__p0) \
	({ \
		const SDL_Rect * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(const SDL_Rect *))*(void**)(__base - 4732))(__t__p0));\
	})

#define SDL_ResetHint(__p0) \
	({ \
		const char * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_bool (*)(const char *))*(void**)(__base - 4738))(__t__p0));\
	})

#define SDL_crc16(__p0, __p1, __p2) \
	({ \
		Uint16  __t__p0 = __p0;\
		const void * __t__p1 = __p1;\
		size_t  __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((Uint16 (*)(Uint16 , const void *, size_t ))*(void**)(__base - 4744))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_GetDefaultAudioInfo(__p0, __p1, __p2) \
	({ \
		char ** __t__p0 = __p0;\
		SDL_AudioSpec * __t__p1 = __p1;\
		int  __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(char **, SDL_AudioSpec *, int ))*(void**)(__base - 4750))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_GetWindowSizeInPixels(__p0, __p1, __p2) \
	({ \
		SDL_Window * __t__p0 = __p0;\
		int * __t__p1 = __p1;\
		int * __t__p2 = __p2;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(SDL_Window *, int *, int *))*(void**)(__base - 4756))(__t__p0, __t__p1, __t__p2));\
	})

#define SDL_GetJoystickGUIDInfo(__p0, __p1, __p2, __p3, __p4) \
	({ \
		SDL_JoystickGUID  __t__p0 = __p0;\
		Uint16 * __t__p1 = __p1;\
		Uint16 * __t__p2 = __p2;\
		Uint16 * __t__p3 = __p3;\
		Uint16 * __t__p4 = __p4;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(SDL_JoystickGUID , Uint16 *, Uint16 *, Uint16 *, Uint16 *))*(void**)(__base - 4762))(__t__p0, __t__p1, __t__p2, __t__p3, __t__p4));\
	})

#define SDL_SetPrimarySelectionText(__p0) \
	({ \
		const char * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(const char *))*(void**)(__base - 4768))(__t__p0));\
	})

#define SDL_GetPrimarySelectionText() \
	({ \
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((char *(*)(void))*(void**)(__base - 4774))());\
	})

#define SDL_HasPrimarySelectionText() \
	({ \
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_bool (*)(void))*(void**)(__base - 4780))());\
	})

#define SDL_ResetHints() \
	({ \
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((void (*)(void))*(void**)(__base - 4786))());\
	})

#define SDL_strcasestr(__p0, __p1) \
	({ \
		const char * __t__p0 = __p0;\
		const char * __t__p1 = __p1;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((char *(*)(const char *, const char *))*(void**)(__base - 4792))(__t__p0, __t__p1));\
	})

#define SDL_HasWindowSurface(__p0) \
	({ \
		SDL_Window * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((SDL_bool (*)(SDL_Window *))*(void**)(__base - 4798))(__t__p0));\
	})

#define SDL_DestroyWindowSurface(__p0) \
	({ \
		SDL_Window * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((int (*)(SDL_Window *))*(void**)(__base - 4804))(__t__p0));\
	})

#define SDL_GameControllerGetSteamHandle(__p0) \
	({ \
		SDL_GameController * __t__p0 = __p0;\
		long __base = (long)(SDL2_BASE_NAME);\
		__asm volatile("mr 12,%0": :"r"(__base):"r12");\
		(((Uint64 (*)(SDL_GameController *))*(void**)(__base - 4810))(__t__p0));\
	})

#endif /* !_PPCINLINE_SDL2_H */
