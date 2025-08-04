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
#include "sdl_mac.h"

#ifdef SDL_VIDEO_DRIVER_MACOSCLASSIC

/**
 * Runs the main event loop.
 * @param   _THIS
 */
void SDL_Mac_pumpEvents(_THIS)
{
  EventRecord event;
  int etype,val,x,y;

#ifdef MAC_DEBUG
  fprintf(stderr,"macosclassic pumpEvents...\n"); fflush(stderr);
#endif

  val=EventAvail(everyEvent,&event);
  if(val) {
	GetNextEvent(everyEvent,&event);
    etype=event.what;
    x=event.where.h;
    y=event.where.v;
    // Just EXTREMELY rough correction for now...
    x-=WINDOW_OFFSET_X; y-=WINDOW_OFFSET_Y;
    /*fprintf(stderr,"macosclassic what=%d at %d,%d\n",event.what,x,y); fflush(stderr);*/
    switch(etype) {
      case nullEvent: 
        fprintf(stderr,"macosclassic null event!\n"); fflush(stderr);
	break;
      case kHighLevelEvent:
        /* Handle this eventually... */
        break;
      case activateEvt:
        /* Just skip for now */
        break;
      case updateEvt:
        SetPort((GrafPtr)GetWindowPort((WindowPtr)event.message));
        BeginUpdate((WindowPtr)event.message);
        EndUpdate((WindowPtr)event.message);
        DrawGrowIcon((WindowPtr)event.message);
        break;
      case mouseDown:
        fprintf(stderr,"macosclassic mouseDown at %d,%d!\n",x,y); fflush(stderr);
        SDL_SendMouseMotion(sdlw,1,0,x,y);
        SDL_SendMouseButton(sdlw,1,1,SDL_BUTTON_LEFT);
        break;
      case mouseUp:
        fprintf(stderr,"macosclassic mouseUp %d,%d!\n",x,y); fflush(stderr);
        SDL_SendMouseMotion(sdlw,1,0,x,y);
        SDL_SendMouseButton(sdlw,1,0,SDL_BUTTON_LEFT);
        break;
      case autoKey:
        /*fprintf(stderr,"macosclassic autoKey!\n"); fflush(stderr);*/
        handleKeyboardEvent(&event,etype);
        break;
	  case keyDown:
        /*fprintf(stderr,"macosclassic keyDown!\n"); fflush(stderr);*/
        handleKeyboardEvent(&event,etype);
        break;
	  case keyUp:
        /*fprintf(stderr,"macosclassic keyUp!\n"); fflush(stderr);*/
        handleKeyboardEvent(&event,etype);
	    break;
	  default:
#ifdef MAC_DEBUG
	    fprintf(stderr,"macosclassic mac event.what=%d skipped!\n",etype); fflush(stderr);
#endif
	    break;
	}
  }


}

#endif
