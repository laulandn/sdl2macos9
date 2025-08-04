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
#include "../../events/SDL_keyboard_c.h"
#include "SDL_scancode.h"
#include "SDL_events.h"
#include "sdl_amiga.h"
/*#include <sys/keycodes.h>*/

#ifdef SDL_VIDEO_DRIVER_AMIGAOS3

int macmoddown=0;

/**
 * A map thta translates Screen key names to SDL scan codes.
 * This map is incomplete, but should include most major keys.
 */
 /*
static int key_to_sdl[] = {
    'SPACE' = SDL_SCANCODE_SPACE,
    'APOSTROPHE' = SDL_SCANCODE_APOSTROPHE,
    'COMMA' = SDL_SCANCODE_COMMA,
    'MINUS' = SDL_SCANCODE_MINUS,
    'PERIOD' = SDL_SCANCODE_PERIOD,
    'SLASH' = SDL_SCANCODE_SLASH,
    'ZERO' = SDL_SCANCODE_0,
    'ONE' = SDL_SCANCODE_1,
    'TWO' = SDL_SCANCODE_2,
    'THREE' = SDL_SCANCODE_3,
    'FOUR' = SDL_SCANCODE_4,
    'FIVE' = SDL_SCANCODE_5,
    'SIX' = SDL_SCANCODE_6,
    'SEVEN' = SDL_SCANCODE_7,
    'EIGHT' = SDL_SCANCODE_8,
    'NINE' = SDL_SCANCODE_9,
    'SEMICOLON' = SDL_SCANCODE_SEMICOLON,
    'EQUAL' = SDL_SCANCODE_EQUALS,
    'LEFT_BRACKET' = SDL_SCANCODE_LEFTBRACKET,
    'BACK_SLASH' = SDL_SCANCODE_BACKSLASH,
    'RIGHT_BRACKET' = SDL_SCANCODE_RIGHTBRACKET,
    'GRAVE' = SDL_SCANCODE_GRAVE,
    'A' = SDL_SCANCODE_A,
    'B' = SDL_SCANCODE_B,
    'C' = SDL_SCANCODE_C,
    'D' = SDL_SCANCODE_D,
    'E' = SDL_SCANCODE_E,
    'F' = SDL_SCANCODE_F,
    'G' = SDL_SCANCODE_G,
    'H' = SDL_SCANCODE_H,
    'I' = SDL_SCANCODE_I,
    'J' = SDL_SCANCODE_J,
    'K' = SDL_SCANCODE_K,
    'L' = SDL_SCANCODE_L,
    'M' = SDL_SCANCODE_M,
    'N' = SDL_SCANCODE_N,
    'O' = SDL_SCANCODE_O,
    'P' = SDL_SCANCODE_P,
    'Q' = SDL_SCANCODE_Q,
    'R' = SDL_SCANCODE_R,
    'S' = SDL_SCANCODE_S,
    'T' = SDL_SCANCODE_T,
    'U' = SDL_SCANCODE_U,
    'V' = SDL_SCANCODE_V,
    'W' = SDL_SCANCODE_W,
    'X' = SDL_SCANCODE_X,
    'Y' = SDL_SCANCODE_Y,
    'Z' = SDL_SCANCODE_Z,
    'UP' = SDL_SCANCODE_UP,
    'DOWN' = SDL_SCANCODE_DOWN,
    'LEFT' = SDL_SCANCODE_LEFT,
    'PG_UP' = SDL_SCANCODE_PAGEUP,
    'PG_DOWN' = SDL_SCANCODE_PAGEDOWN,
    'RIGHT' = SDL_SCANCODE_RIGHT,
    'RETURN' = SDL_SCANCODE_RETURN,
    'TAB' = SDL_SCANCODE_TAB,
    'ESCAPE' = SDL_SCANCODE_ESCAPE,
};
*/

/**
 * Called from the event dispatcher when a keyboard event is encountered.
 * Translates the event such that it can be handled by SDL.
 * @param   event   Screen keyboard event
 */
void handleKeyboardEvent(struct IntuiMessage *event)
{
    /*int             val;*/
    SDL_Scancode    scancode=0;
    int keyToReturn=0;

    fprintf(stderr,"amigaos3 handleKeyboardEvent...\n"); fflush(stderr);

    /* Get the key value.*/
    /*if (screen_get_event_property_iv(event, SCREEN_PROPERTY_SYM, &val) < 0) {
        return;
    }*/

    /* Skip unrecognized keys.*/
    /*if ((val < 0) || (val >= SDL_TABLESIZE(key_to_sdl))) {
        return;
    }*/

    /* Translate to an SDL scan code. */
    /*scancode = key_to_sdl[val];
    if (scancode == 0) {
        return;
    }*/

    /* Get event flags (key state). */
    /*if (screen_get_event_property_iv(event, SCREEN_PROPERTY_FLAGS, &val) < 0) {
        return;
    }*/
    
#ifdef AMIGA_DEBUG
    fprintf(stderr,"amigaos3 key event type code=%x qual=%x\n",event->Code,event->Qualifier); fflush(stderr);
#endif
        keyToReturn=event->Code&0x7f;
        /* This code is just a hack to get bare minimum done for now... */
        switch(keyToReturn) {
	/*
          case 28: scancode=SDL_SCANCODE_LEFT; break;
          case 29: scancode=SDL_SCANCODE_RIGHT; break;
          case 30: scancode=SDL_SCANCODE_UP; break;
          case 31: scancode=SDL_SCANCODE_DOWN; break;*/
		   /**/
	  // TODO: HORRIBLE HACK...these are actualy wasd!
          case 0x20: scancode=SDL_SCANCODE_LEFT; break;
          case 0x22: scancode=SDL_SCANCODE_RIGHT; break;
          case 0x11: scancode=SDL_SCANCODE_UP; break;
          case 0x21: scancode=SDL_SCANCODE_DOWN; break;
		   /**/
          case 0x40: scancode=SDL_SCANCODE_SPACE; break;
          case 0x44: scancode=SDL_SCANCODE_RETURN; break;
          case 0x42: scancode=SDL_SCANCODE_TAB; break;
          case 0x45: scancode=SDL_SCANCODE_ESCAPE; break;
          default:
            scancode=keyToReturn;//RawKeyConvert(keyToReturn);
            break;
	}

#ifdef AMIGA_DEBUG
     	fprintf(stderr,"amigaos3 SDL scancode is 0x%x\n",scancode); fflush(stderr);
#endif
      
    /* Propagate the event to SDL.
    // FIXME:
    // Need to handle more key states (such as key combinations).*/
    if (event->Code&0x80) {
        SDL_SendKeyboardKey(SDL_PRESSED, scancode);
    } else {
        SDL_SendKeyboardKey(SDL_RELEASED, scancode);
    }
}

#endif
