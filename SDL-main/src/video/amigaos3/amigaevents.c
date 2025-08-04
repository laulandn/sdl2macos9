/* MacOS9 Note: This code was based on the QNX driver
   solely because it was the smallest and easiest to understand.
   Below is the original copyright message */

/*
  Simple DirectMedia Layer
  Copyright (C) 2017 BlackBerry Limited

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
#include "../../SDL_internal.h"
#include "../SDL_sysvideo.h"
#include "sdl_amiga.h"


#ifdef SDL_VIDEO_DRIVER_AMIGAOS3

#define SIGMASK(w) (1L<<((w)->UserPort->mp_SigBit))
#define GETIMSG(w) ((struct IntuiMessage *)GetMsg((w)->UserPort))

/**
 * Runs the main event loop.
 * @param   _THIS
 */
void SDL_Amiga_pumpEvents(_THIS)
{
  struct IntuiMessage *IntMsg;
  //int etype,val;

#ifdef AMIGA_DEBUG
  //fprintf(stderr,"amigaos3 pumpEvents...\n"); fflush(stderr);
#endif

    // (void)Wait(SIGMASK(amigawindow));

   while (IntMsg=GETIMSG(amigawindow))
    {
     switch (IntMsg->Class)
      {
       case IDCMP_REFRESHWINDOW:
	     fprintf(stderr,"amigaos3 refresh event\n"); fflush(stderr);
        BeginRefresh (amigawindow);
        //RedrawScaleWindow (amigawindow,ImageData);
        EndRefresh (amigawindow,TRUE);
        break;
       case IDCMP_ACTIVEWINDOW:
	     fprintf(stderr,"amigaos3 active event\n"); fflush(stderr);
        break;
       case IDCMP_CHANGEWINDOW:
	     fprintf(stderr,"amigaos3 changewindow event\n"); fflush(stderr);
        BeginRefresh (amigawindow);
        //RedrawScaleWindow (amigawindow,ImageData);
        EndRefresh (amigawindow,TRUE);
        break;
       case IDCMP_NEWSIZE:
	     fprintf(stderr,"amigaos3 newsize event\n"); fflush(stderr);
        BeginRefresh (amigawindow);
        //RedrawScaleWindow (amigawindow,ImageData);
        EndRefresh (amigawindow,TRUE);
        break;
       case IDCMP_CLOSEWINDOW:
	     fprintf(stderr,"amigaos3 close event\n"); fflush(stderr);
  exitCleanly(0);
        break;
       case IDCMP_MOUSEBUTTONS:
	     fprintf(stderr,"amigaos3 button event\n"); fflush(stderr);
	     fprintf(stderr,"amigaos3 button MouseX=%d MouseY=%d\n",IntMsg->MouseX,IntMsg->MouseY); fflush(stderr);
		     if(IntMsg->Code&IECODE_UP_PREFIX) {
	               SDL_SendMouseMotion(sdlw,1,0,IntMsg->MouseX,IntMsg->MouseY);
		       SDL_SendMouseButton(sdlw,1,0,SDL_BUTTON_LEFT);
	     fprintf(stderr,"amigaos3 button up %d,%d\n",IntMsg->MouseX,IntMsg->MouseY); fflush(stderr);
		     }
		     else {
	               SDL_SendMouseMotion(sdlw,1,0,IntMsg->MouseX,IntMsg->MouseY);
		       SDL_SendMouseButton(sdlw,1,1,SDL_BUTTON_LEFT);
	     fprintf(stderr,"amigaos3 button down %d,%d\n",IntMsg->MouseX,IntMsg->MouseY); fflush(stderr);
		     }
	     break;
       case IDCMP_VANILLAKEY:
       case IDCMP_RAWKEY:
	     fprintf(stderr,"amigaos3 key event\n"); fflush(stderr);
	     handleKeyboardEvent(IntMsg);
	     break;
       default:
	     fprintf(stderr,"amigaos3 %08lx event\n",(long)IntMsg->Class); fflush(stderr);
	break;
      }

     ReplyMsg (&IntMsg->ExecMessage);
    }

}

#endif
