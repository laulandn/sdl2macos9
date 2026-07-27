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
#include "sdl_mac.h"
/*#include <sys/keycodes.h>*/

#ifdef SDL_VIDEO_DRIVER_MACOSCLASSIC

int macmoddown=0;
static Uint8 mac_key_state[128];

static SDL_Scancode MacKeyCodeToSDL( int keycode )
{
    switch (keycode) {
    case 0x00: return SDL_SCANCODE_A;
    case 0x01: return SDL_SCANCODE_S;
    case 0x02: return SDL_SCANCODE_D;
    case 0x03: return SDL_SCANCODE_F;
    case 0x04: return SDL_SCANCODE_H;
    case 0x05: return SDL_SCANCODE_G;
    case 0x06: return SDL_SCANCODE_Z;
    case 0x07: return SDL_SCANCODE_X;
    case 0x08: return SDL_SCANCODE_C;
    case 0x09: return SDL_SCANCODE_V;
    case 0x0B: return SDL_SCANCODE_B;
    case 0x0C: return SDL_SCANCODE_Q;
    case 0x0D: return SDL_SCANCODE_W;
    case 0x0E: return SDL_SCANCODE_E;
    case 0x0F: return SDL_SCANCODE_R;
    case 0x10: return SDL_SCANCODE_Y;
    case 0x11: return SDL_SCANCODE_T;
    case 0x12: return SDL_SCANCODE_1;
    case 0x13: return SDL_SCANCODE_2;
    case 0x14: return SDL_SCANCODE_3;
    case 0x15: return SDL_SCANCODE_4;
    case 0x16: return SDL_SCANCODE_6;
    case 0x17: return SDL_SCANCODE_5;
    case 0x18: return SDL_SCANCODE_EQUALS;
    case 0x19: return SDL_SCANCODE_9;
    case 0x1A: return SDL_SCANCODE_7;
    case 0x1B: return SDL_SCANCODE_MINUS;
    case 0x1C: return SDL_SCANCODE_8;
    case 0x1D: return SDL_SCANCODE_0;
    case 0x1E: return SDL_SCANCODE_RIGHTBRACKET;
    case 0x1F: return SDL_SCANCODE_O;
    case 0x20: return SDL_SCANCODE_U;
    case 0x21: return SDL_SCANCODE_LEFTBRACKET;
    case 0x22: return SDL_SCANCODE_I;
    case 0x23: return SDL_SCANCODE_P;
    case 0x24: return SDL_SCANCODE_RETURN;
    case 0x25: return SDL_SCANCODE_L;
    case 0x26: return SDL_SCANCODE_J;
    case 0x27: return SDL_SCANCODE_APOSTROPHE;
    case 0x28: return SDL_SCANCODE_K;
    case 0x29: return SDL_SCANCODE_SEMICOLON;
    case 0x2A: return SDL_SCANCODE_BACKSLASH;
    case 0x2B: return SDL_SCANCODE_COMMA;
    case 0x2C: return SDL_SCANCODE_SLASH;
    case 0x2D: return SDL_SCANCODE_N;
    case 0x2E: return SDL_SCANCODE_M;
    case 0x2F: return SDL_SCANCODE_PERIOD;
    case 0x30: return SDL_SCANCODE_TAB;
    case 0x31: return SDL_SCANCODE_SPACE;
    case 0x32: return SDL_SCANCODE_GRAVE;
    case 0x33: return SDL_SCANCODE_BACKSPACE;
    case 0x35: return SDL_SCANCODE_ESCAPE;
    case 0x38: return SDL_SCANCODE_LSHIFT;
    case 0x39: return SDL_SCANCODE_CAPSLOCK;
    case 0x3A: return SDL_SCANCODE_LALT;
    case 0x3B: return SDL_SCANCODE_LCTRL;
    case 0x3C: return SDL_SCANCODE_RSHIFT;
    case 0x3D: return SDL_SCANCODE_RALT;
    case 0x3E: return SDL_SCANCODE_RCTRL;
    case 0x7B: return SDL_SCANCODE_LEFT;
    case 0x7C: return SDL_SCANCODE_RIGHT;
    case 0x7D: return SDL_SCANCODE_DOWN;
    case 0x7E: return SDL_SCANCODE_UP;
    default: return SDL_SCANCODE_UNKNOWN;
    }
}

void Mac_ResetKeyboardState(void)
{
    int keycode;

    for (keycode = 0; keycode < SDL_arraysize(mac_key_state); ++keycode) {
        SDL_Scancode scancode;

        if (!mac_key_state[keycode])
            continue;
        scancode = MacKeyCodeToSDL(keycode);
        if (scancode != SDL_SCANCODE_UNKNOWN)
            SDL_SendKeyboardKey(SDL_RELEASED, scancode);
    }
    SDL_zeroa(mac_key_state);
}

void Mac_PollKeyboard(void)
{
    KeyMap key_map;
    const Uint8 *key_bits = (const Uint8 *)key_map;
    int keycode;

    GetKeys(key_map);
    for (keycode = 0; keycode < SDL_arraysize(mac_key_state); ++keycode) {
        const Uint8 pressed =
            (key_bits[keycode >> 3] & (1u << (keycode & 7))) != 0;
        SDL_Scancode scancode;

        if (pressed == mac_key_state[keycode])
            continue;
        mac_key_state[keycode] = pressed;
        scancode = MacKeyCodeToSDL(keycode);
        if (scancode != SDL_SCANCODE_UNKNOWN) {
            SDL_SendKeyboardKey(pressed ? SDL_PRESSED : SDL_RELEASED,
                                scancode);
        }
    }
}

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
void handleKeyboardEvent(EventRecord *event, int what)
{
    SDL_Event quit_event;
    int character = event->message & 0xff;

#ifndef MAC_DEBUG
    (void)what;
#endif

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
    
#ifdef MAC_DEBUG
    fprintf(stderr,"macosclassic key event type %d what %d\n",event->what,what); fflush(stderr);
#endif
    
		if(event->modifiers&cmdKey) {
#ifdef MAC_DEBUG
          int mchoice=MenuKey(event->message&0xff);
          fprintf(stderr,"macosclassic mac menu '%c' mchoice=%d\n",(char)event->message&0xff,mchoice); fflush(stderr);
#endif
          /* TODO: Possibly handle other command menus here... */
          if(event->what == keyDown && (event->message&0xff)=='q') {
#ifdef MAC_DEBUG
            fprintf(stderr,"macosclassic Command-Q...quiting...\n"); fflush(stderr);
#endif
            SDL_zero(quit_event);
            quit_event.type = SDL_QUIT;
            SDL_PushEvent(&quit_event);
          }
        }
		else {
#ifdef MAC_DEBUG
		  fprintf(stderr,"macosclassic mac keypress '%c' (%d)\n",character,character); fflush(stderr);
		  fprintf(stderr,"macosclassic event->modifiers %d\n",event->modifiers); fflush(stderr);
#endif
        }

    if (event->modifiers & cmdKey)
        return;

    /* Key state comes from GetKeys so simultaneous keys cannot be lost when
       the Event Manager coalesces or delays individual transitions. */
    if (event->what == keyDown || event->what == autoKey) {
        if (!(event->modifiers & (controlKey | optionKey)) &&
            character >= 32 && character <= 126) {
            char text[2];
            text[0] = (char)character;
            text[1] = '\0';
            SDL_SendKeyboardText(text);
        }
    }
}

#endif
