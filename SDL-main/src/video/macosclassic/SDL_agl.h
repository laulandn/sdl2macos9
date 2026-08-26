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

/* We have our own copy of this so we aren't dependent on any particular OpenGL SDK */

#ifndef SDL_agl_h_
#define SDL_agl_h_

#include "SDL_opengl.h"
#ifdef TARGET_OS_OSX
#else
#include <Quickdraw.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef GDHandle AGLDevice;
typedef CGrafPtr AGLDrawable;
typedef struct __AGLPixelFormatRec *AGLPixelFormat;
typedef struct __AGLContextRec *AGLContext;

#define AGL_NONE                 0
#define AGL_ALL_RENDERERS        1
#define AGL_RGBA                 4
#define AGL_DOUBLEBUFFER         5
#define AGL_STEREO               6
#define AGL_RED_SIZE             8
#define AGL_GREEN_SIZE           9
#define AGL_BLUE_SIZE           10
#define AGL_ALPHA_SIZE          11
#define AGL_DEPTH_SIZE          12
#define AGL_STENCIL_SIZE        13
#define AGL_ACCUM_RED_SIZE      14
#define AGL_ACCUM_GREEN_SIZE    15
#define AGL_ACCUM_BLUE_SIZE     16
#define AGL_ACCUM_ALPHA_SIZE    17
#define AGL_PIXEL_SIZE          50
#define AGL_SAMPLE_BUFFERS_ARB  55
#define AGL_SAMPLES_ARB         56
#define AGL_RENDERER_ID         70
#define AGL_NO_RECOVERY         72
#define AGL_ACCELERATED         73
#define AGL_CLOSEST_POLICY      74
#define AGL_SWAP_INTERVAL      222

extern AGLPixelFormat aglChoosePixelFormat(const AGLDevice *gdevs, GLint ndev,
                                           const GLint *attribs);
extern void aglDestroyPixelFormat(AGLPixelFormat pix);
extern GLboolean aglDescribePixelFormat(AGLPixelFormat pix, GLint attrib,
                                        GLint *value);
extern AGLContext aglCreateContext(AGLPixelFormat pix, AGLContext share);
extern GLboolean aglDestroyContext(AGLContext ctx);
extern GLboolean aglUpdateContext(AGLContext ctx);
extern GLboolean aglSetCurrentContext(AGLContext ctx);
extern AGLContext aglGetCurrentContext(void);
extern GLboolean aglSetDrawable(AGLContext ctx, AGLDrawable draw);
extern void aglSwapBuffers(AGLContext ctx);
extern GLboolean aglSetInteger(AGLContext ctx, GLenum pname,
                               const GLint *params);
extern GLenum aglGetError(void);
extern const GLubyte *aglErrorString(GLenum code);

#ifdef __cplusplus
}
#endif

#endif
