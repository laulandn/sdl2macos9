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
#include "../../SDL_internal.h"

#if defined(SDL_JOYSTICK_MACOSCLASSIC)

/* This is the dummy implementation of the SDL joystick API */

#include "SDL_joystick.h"
#include "../SDL_sysjoystick.h"
#include "../SDL_joystick_c.h"

static int MACOS_JoystickInit(void)
{
    fprintf(stderr,"macosclassic joystick init\n"); fflush(stderr);
    return 0;
}

static int MACOS_JoystickGetCount(void)
{
    fprintf(stderr,"macosclassic joystick get count\n"); fflush(stderr);
    return 0;
}

static void MACOS_JoystickDetect(void)
{
    fprintf(stderr,"macosclassic joystick detect\n"); fflush(stderr);
}

static const char *MACOS_JoystickGetDeviceName(int device_index)
{
    fprintf(stderr,"macosclassic joystick get dev name\n"); fflush(stderr);
    return NULL;
}

static const char *MACOS_JoystickGetDevicePath(int device_index)
{
    fprintf(stderr,"macosclassic joystick get dev path\n"); fflush(stderr);
    return NULL;
}

static int MACOS_JoystickGetDeviceSteamVirtualGamepadSlot(int device_index)
{
    fprintf(stderr,"macosclassic joystick get dev steam virt\n"); fflush(stderr);
    return -1;
}

static int MACOS_JoystickGetDevicePlayerIndex(int device_index)
{
    fprintf(stderr,"macosclassic joystick get dev player index\n"); fflush(stderr);
    return -1;
}

static void MACOS_JoystickSetDevicePlayerIndex(int device_index, int player_index)
{
    fprintf(stderr,"macosclassic joystick set dev player index\n"); fflush(stderr);
}

static SDL_JoystickGUID MACOS_JoystickGetDeviceGUID(int device_index)
{
    SDL_JoystickGUID guid;
    fprintf(stderr,"macosclassic joystick get dev guid\n"); fflush(stderr);
    SDL_zero(guid);
    return guid;
}

static SDL_JoystickID MACOS_JoystickGetDeviceInstanceID(int device_index)
{
    fprintf(stderr,"macosclassic joystick get dev inst id\n"); fflush(stderr);
    return -1;
}

static int MACOS_JoystickOpen(SDL_Joystick *joystick, int device_index)
{
    fprintf(stderr,"macosclassic joystick open\n"); fflush(stderr);
    return SDL_SetError("Logic error: No joysticks available");
}

static int MACOS_JoystickRumble(SDL_Joystick *joystick, Uint16 low_frequency_rumble, Uint16 high_frequency_rumble)
{
    fprintf(stderr,"macosclassic joystick rumble\n"); fflush(stderr);
    return SDL_Unsupported();
}

static int MACOS_JoystickRumbleTriggers(SDL_Joystick *joystick, Uint16 left_rumble, Uint16 right_rumble)
{
    fprintf(stderr,"macosclassic joystick rumble triggers\n"); fflush(stderr);
    return SDL_Unsupported();
}

static Uint32 MACOS_JoystickGetCapabilities(SDL_Joystick *joystick)
{
    fprintf(stderr,"macosclassic joystick get cap\n"); fflush(stderr);
    return 0;
}

static int MACOS_JoystickSetLED(SDL_Joystick *joystick, Uint8 red, Uint8 green, Uint8 blue)
{
    fprintf(stderr,"macosclassic joystick joystick set led\n"); fflush(stderr);
    return SDL_Unsupported();
}

static int MACOS_JoystickSendEffect(SDL_Joystick *joystick, const void *data, int size)
{
    fprintf(stderr,"macosclassic joystick send effects\n"); fflush(stderr);
    return SDL_Unsupported();
}

static int MACOS_JoystickSetSensorsEnabled(SDL_Joystick *joystick, SDL_bool enabled)
{
    fprintf(stderr,"macosclassic joystick set sensors\n"); fflush(stderr);
    return SDL_Unsupported();
}

static void MACOS_JoystickUpdate(SDL_Joystick *joystick)
{
    fprintf(stderr,"macosclassic joystick update\n"); fflush(stderr);
}

static void MACOS_JoystickClose(SDL_Joystick *joystick)
{
    fprintf(stderr,"macosclassic joystick close\n"); fflush(stderr);
}

static void MACOS_JoystickQuit(void)
{
    fprintf(stderr,"macosclassic joystick quit\n"); fflush(stderr);
}

static SDL_bool MACOS_JoystickGetGamepadMapping(int device_index, SDL_GamepadMapping *out)
{
    fprintf(stderr,"macosclassic joystick get gamepad mapping\n"); fflush(stderr);
    return SDL_FALSE;
}

SDL_JoystickDriver SDL_MACOS_JoystickDriver = {
    MACOS_JoystickInit,
    MACOS_JoystickGetCount,
    MACOS_JoystickDetect,
    MACOS_JoystickGetDeviceName,
    MACOS_JoystickGetDevicePath,
    MACOS_JoystickGetDeviceSteamVirtualGamepadSlot,
    MACOS_JoystickGetDevicePlayerIndex,
    MACOS_JoystickSetDevicePlayerIndex,
    MACOS_JoystickGetDeviceGUID,
    MACOS_JoystickGetDeviceInstanceID,
    MACOS_JoystickOpen,
    MACOS_JoystickRumble,
    MACOS_JoystickRumbleTriggers,
    MACOS_JoystickGetCapabilities,
    MACOS_JoystickSetLED,
    MACOS_JoystickSendEffect,
    MACOS_JoystickSetSensorsEnabled,
    MACOS_JoystickUpdate,
    MACOS_JoystickClose,
    MACOS_JoystickQuit,
    MACOS_JoystickGetGamepadMapping
};

#endif /* SDL_JOYSTICK_MACOSCLASSIC */

/* vi: set ts=4 sw=4 expandtab: */
