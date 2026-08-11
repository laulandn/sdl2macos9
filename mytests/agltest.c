#include <MacWindows.h>
#include "agl.h"
int main(void)
{
unsigned long temp;
Rect rect;
WindowPtr win;
GLint attrib[] = { AGL_RGBA, AGL_NONE };
AGLPixelFormat fmt;
AGLContext ctx;
/* Initialize Mac OS */
InitCursor();
/* Create a window */
SetRect(&rect, 50, 50, 450, 450);
win = NewCWindow (0L, &rect, "\pAGL intro", true,
                  plainDBox, (WindowPtr) -1L, true, 0L);
SetPortWindowPort(win);
/* Choose pixel format */
fmt = aglChoosePixelFormat(NULL, 0, attrib);
/* Create an AGL context */
ctx = aglCreateContext(fmt, NULL);
/* Attach the context to the window */
aglSetDrawable(ctx, GetWindowPort (win));
aglSetCurrentContext(ctx);
/* Clear buffer */
glClearColor(1.0, 1.0, 0.0, 1.0);
glClear(GL_COLOR_BUFFER_BIT);
glFinish();
Delay (60, &temp);
return 0;
}