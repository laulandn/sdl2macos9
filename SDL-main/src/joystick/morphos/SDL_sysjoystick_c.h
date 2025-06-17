/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2020 Sam Lantinga <slouken@libsdl.org>

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

#ifdef SDL_JOYSTICK_MORPHOS

#include <exec/types.h>
#include "SDL_joystick.h"

#define MAX_JOYSTICKS 	32
#define MAX_BUTTONS     16
#define MAX_HATS        8
#define MAX_STICKS      8
#define MAX_RUMBLE		2

struct joystick_hwdata
{
	APTR main_sensor; // Main HID sensor
	APTR child_sensors; // List of specific sub-sensor entries
	APTR button[MAX_BUTTONS]; // SensorType_HIDInput_Trigger
	APTR hat[MAX_HATS]; // SensorType_HIDInput_Stick
	APTR stick[MAX_STICKS]; // SensorType_HIDInput_Analog, SensorType_HIDInput_AnalogStick, SensorType_HIDInput_3DStick
	APTR battery; 	// SensorType_HIDInput_Battery 
	APTR rumble[MAX_RUMBLE]; // SensorType_HIDInput_Rumble

	ULONG stickType[MAX_STICKS];
	int numSticks;
	int numRumbles;

	// hot plug support
	struct MsgPort *notifyPort;
	APTR sensorsNotify;
};

#endif