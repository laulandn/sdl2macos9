/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2024 Sam Lantinga <slouken@libsdl.org>

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

#include "SDL_sysjoystick_c.h"

#ifdef SDL_JOYSTICK_MORPHOS

#include "../SDL_sysjoystick.h"
#include "../SDL_joystick_c.h"
#include "SDL_endian.h"
#include "SDL_joystick.h"

#include <exec/execbase.h>
#include <libraries/sensors.h>
#include <libraries/sensors_hid.h>
#define USE_INLINE_STDARG
#include <proto/sensors.h>
#undef USE_INLINE_STDARG

// SDL2 deadzone is around 409, we need 1638
#define DEADZONE_MIN (-0.05)
#define DEADZONE_MAX (0.05)

#define JOYSTICK_MIN -1.0
#define JOYSTICK_MAX 1.0

#define CLAMP(val) \
			(((val) <= (DEADZONE_MAX) && (val) >= (DEADZONE_MIN)) ? (0) : \
			((val) > (JOYSTICK_MAX)) ? (JOYSTICK_MAX) : (((val) < (JOYSTICK_MIN)) ? (JOYSTICK_MIN) : (val)))

APTR sensorlist;
APTR JoySensor[MAX_JOYSTICKS];
int joystick_count;

static int MORPHOS_JoystickInit(void)
{
	int rc = 0;

	APTR sensor = NULL;
	ULONG device_index = 0;

	D("[%s] Obtain sensor list...\n", __FUNCTION__);
	sensorlist = ObtainSensorsListTags(SENSORS_Class, SensorClass_HID, TAG_DONE);
	while ((sensor = NextSensor(sensor, sensorlist, NULL)) && device_index < MAX_JOYSTICKS)
	{
		JoySensor[device_index++] = sensor;
	}

	D("[%s] Found %ld joysticks...\n", __FUNCTION__, device_index);
	joystick_count = device_index;
	
	return rc;
}

static int MORPHOS_JoystickGetCount(void)
{
	return joystick_count;
}

static void MORPHOS_JoystickDetect(void)
{
}

static const char *MORPHOS_JoystickGetDeviceName(int device_index)
{
	APTR sensor = JoySensor[device_index];
	const char *name = NULL;
	GetSensorAttrTags(sensor, SENSORS_HID_Name, (IPTR)&name, TAG_DONE);
	return name;
}

static const char *MORPHOS_JoystickGetDevicePath(int device_index)
{
    return NULL;
}

static int MORPHOS_JoystickGetDeviceSteamVirtualGamepadSlot(int device_index)
{
    return -1;
}

static int MORPHOS_JoystickGetDevicePlayerIndex(int device_index)
{
    return device_index;
}

static void MORPHOS_JoystickSetDevicePlayerIndex(int device_index, int player_index)
{
}


static SDL_JoystickGUID MORPHOS_JoystickGetDeviceGUID(int device_index)
{
	SDL_JoystickGUID guid;
	APTR sensor = JoySensor[device_index];
	Uint16 *guid16 = (Uint16 *)guid.data;
	const char *name = NULL;

	ULONG product, vendor;
	
	GetSensorAttrTags(sensor,
			SENSORS_HID_Name, (IPTR)&name,
			SENSORS_HID_Product, (IPTR)&product,
			SENSORS_HID_Vendor, (IPTR)&vendor,
			TAG_DONE);

	SDL_zero(guid);
	SDL_memset(guid.data, 0, sizeof(guid.data));

	*guid16++ = SDL_SwapLE16(SDL_HARDWARE_BUS_USB);
    *guid16++ = 0;

    if (vendor && product)
	{
        *guid16++ = SDL_SwapLE16(vendor);
        *guid16++ = 0;
        *guid16++ = SDL_SwapLE16(product);
        *guid16++ = 0;
        *guid16++ = 0;
        *guid16++ = 0;
    } 
	else
	{
        SDL_strlcpy((char*)guid16, name, sizeof(guid.data) - 4);
    }
	
	return guid;
}

static SDL_JoystickID MORPHOS_JoystickGetDeviceInstanceID(int device_index)
{
	return device_index;
}

static int MORPHOS_JoystickOpen(SDL_Joystick *joystick, int device_index)
{
	D("[%s]\n", __FUNCTION__);
	APTR sensor = JoySensor[device_index];
	int rc = -1;

	if (sensor) {
		size_t buttons = 0, naxes = 0, nhats = 0, nsticks = 0, nrumbles=0;
		CONST_STRPTR name = "<unknown>";
		struct joystick_hwdata *hwdata = SDL_calloc(device_index + 1, sizeof(*hwdata));
		if (!hwdata) {
			return SDL_OutOfMemory();
		}
		hwdata->main_sensor = sensor;

		hwdata->child_sensors = ObtainSensorsListTags(
			SENSORS_Parent, (IPTR)hwdata->main_sensor,
			SENSORS_Class, SensorClass_HID,
			TAG_DONE);

		sensor = NULL;
		while ((sensor = NextSensor(sensor, hwdata->child_sensors, NULL))) 
		{
			ULONG type = SensorType_HIDInput_Unknown/*, Limb, color, id*/;
			/*GetSensorAttrTags(sensor, 
								SENSORS_HIDInput_ID, (IPTR)&id, 
								SENSORS_HIDInput_Name, (IPTR)&name, 
								SENSORS_HIDInput_Limb, (IPTR)&Limb, 
								SENSORS_HIDInput_Color, (IPTR)&color, 
								TAG_DONE);
			D("[%s] sensor id: %d name: %s Limb:%d LimbName:%s color:%d\n", __FUNCTION__, id, name, Limb, color);	*/
			
			if (GetSensorAttrTags(sensor, SENSORS_Type, (IPTR)&type, TAG_DONE))
			{
				switch (type) 
				{
					case SensorType_HIDInput_Trigger:
						if (buttons < MAX_BUTTONS) 
						{
							hwdata->button[buttons++] = sensor;
						}
						break;
					case SensorType_HIDInput_Stick:
						if (nhats < MAX_HATS)
						{
							hwdata->hat[nhats++] = sensor;
						}
						break;
					case SensorType_HIDInput_Analog:
					case SensorType_HIDInput_AnalogStick:
					case SensorType_HIDInput_3DStick:
						if (nsticks < MAX_STICKS) 
						{
							hwdata->stick[nsticks] = sensor;
							hwdata->stickType[nsticks] = type;
							nsticks++;
							if (type == SensorType_HIDInput_AnalogStick)
								naxes += 2;
							else if (type == SensorType_HIDInput_3DStick)
								naxes += 4;
							else
								naxes++;
						}
						break;
					case SensorType_HIDInput_Rumble:
						if (nrumbles < MAX_RUMBLE)
						{
							GetSensorAttrTags(sensor, SENSORS_HID_Name, (IPTR)&name, TAG_DONE);
							hwdata->rumble[nrumbles] = sensor;
							nrumbles++;
						}
						break;
					case SensorType_HIDInput_Battery:
						GetSensorAttrTags(sensor, SENSORS_HID_Name, (IPTR)&name, TAG_DONE);
					    // Force "Xbox360 Controller" (WIRED) to use SDL_JOYSTICK_POWER_WIRED
						if (strcmp((const char *)MORPHOS_JoystickGetDeviceName(device_index),(const char *)"Xbox360 Controller") == 0)
						{
							SDL_PrivateJoystickBatteryLevel(joystick, SDL_JOYSTICK_POWER_WIRED);  
							hwdata->battery = NULL;
						} else {							
							hwdata->battery = sensor;
						}
						break;
					case SensorType_HIDInput_Knob:
						GetSensorAttrTags(sensor, SENSORS_HID_Name, (IPTR)&name, TAG_DONE);
						break;
					case SensorType_HIDInput_Wheel:
						GetSensorAttrTags(sensor, SENSORS_HID_Name, (IPTR)&name, TAG_DONE);
						break;
					default:
						//D("[%s] unknown SensorType: %d\n", __FUNCTION__, type);
						continue;
				}
			}
		}

		joystick->naxes = naxes;
		joystick->nhats = nhats;
		joystick->nbuttons = buttons;
		hwdata->numSticks = nsticks;
		hwdata->numRumbles = nrumbles;
		joystick->hwdata = hwdata;
		joystick->name = (char *)MORPHOS_JoystickGetDeviceName(device_index);
		rc = 0;
	} else {
		SDL_SetError("Failed to open device");
	}
	return rc;
}

static int MORPHOS_JoystickRumble(SDL_Joystick * joystick, Uint16 low_frequency_rumble, Uint16 high_frequency_rumble, Uint32 msDuration)
{
	struct joystick_hwdata *hwdata = joystick->hwdata;
	if (hwdata) 
	{
		if (hwdata->numRumbles)
		{
			//ULONG msDuration = SDL_MAX_RUMBLE_DURATION_MS;
			
			DOUBLE lpower=(DOUBLE)(low_frequency_rumble/65535), hpower=(DOUBLE)(high_frequency_rumble/65535);

			D("[%s] SetSensorAttr lpower=%f - hpower=%f - duration=%d\n", __FUNCTION__,lpower, hpower, msDuration);

			struct TagItem lfreq[] = {
				{SENSORS_HIDInput_Rumble_Power, (IPTR)&lpower}, 
				{SENSORS_HIDInput_Rumble_Duration, msDuration}, 
				{TAG_DONE}
			};
			struct TagItem hfreq[] = {
				{SENSORS_HIDInput_Rumble_Power, (IPTR)&hpower}, 
				{SENSORS_HIDInput_Rumble_Duration, msDuration}, 
				{TAG_DONE}	
			};
			
			if (hwdata->rumble[0])
				SetSensorAttr(hwdata->rumble[0], lfreq);
			
			if (hwdata->rumble[1])
				SetSensorAttr(hwdata->rumble[1], hfreq);
		} else {
			return SDL_Unsupported();
		}
	}		
    return 0;
}

static int MORPHOS_JoystickRumbleTriggers(SDL_Joystick *joystick, Uint16 left_rumble, Uint16 right_rumble)
{
    return SDL_Unsupported();
}

static Uint32 MORPHOS_JoystickGetCapabilities(SDL_Joystick *joystick)
{
    Uint32 result = 0;
	struct joystick_hwdata *hwdata = joystick->hwdata;
	if (hwdata) 
	{
		if (hwdata->numRumbles)
		{
        	result |= SDL_JOYCAP_RUMBLE;
		}
    }

    return result;
}

static int MORPHOS_JoystickSetLED(SDL_Joystick *joystick, Uint8 red, Uint8 green, Uint8 blue)
{
    return SDL_Unsupported();
}

static int MORPHOS_JoystickSendEffect(SDL_Joystick *joystick, const void *data, int size)
{
    return SDL_Unsupported();
}

static int MORPHOS_JoystickSetSensorsEnabled(SDL_Joystick *joystick, SDL_bool enabled)
{
    return SDL_Unsupported();
}

static void MORPHOS_JoystickUpdate(SDL_Joystick *joystick)
{
	struct joystick_hwdata *hwdata = joystick->hwdata;
	if (hwdata) 
	{
		int i, j;
		Sint16 sval;
		double btn_value, bt_value, x_value, y_value, z_value, ns_value, ew_value, z_rotation;

		for (i = 0; i < joystick->nbuttons; i++) 
		{
			GetSensorAttrTags(hwdata->button[i], SENSORS_HIDInput_Value, (IPTR)&btn_value, TAG_DONE);
			if ((joystick->buttons[i] && btn_value == 0.0) || (joystick->buttons[i] == 0 && btn_value > 0.0)) 
			{
				SDL_PrivateJoystickButton(joystick, i, btn_value == 0.0 ? 0 : 1);
			}
		}

		for (i = 0; i < joystick->nhats; i++) 
		{
			GetSensorAttrTags(hwdata->hat[i],
				SENSORS_HIDInput_EW_Value, (IPTR)&ew_value,
				SENSORS_HIDInput_NS_Value, (IPTR)&ns_value,
				TAG_DONE);
			Uint8 value_hat = SDL_HAT_CENTERED;
			if (ns_value >= 1.0) {
				value_hat |= SDL_HAT_DOWN;
			} else if (ns_value <= -1.0) {
				value_hat |= SDL_HAT_UP;
			}
			if (ew_value >= 1.0) {
				value_hat |= SDL_HAT_RIGHT;
			} else if (ew_value <= -1.0) {
				value_hat |= SDL_HAT_LEFT;
			}
			SDL_PrivateJoystickHat(joystick, i, value_hat);
		}
		
		j = 0;
		for (i = 0; i < hwdata->numSticks; i++) 
		{
			switch (hwdata->stickType[i]) 
			{
				case SensorType_HIDInput_3DStick:
					GetSensorAttrTags(hwdata->stick[i],
						SENSORS_HIDInput_X_Index, (IPTR)&x_value,
						SENSORS_HIDInput_Y_Index, (IPTR)&y_value,
						SENSORS_HIDInput_Z_Index, (IPTR)&z_value,
						SENSORS_HIDInput_Z_Rotation, (IPTR)&z_rotation,
						TAG_DONE);

					sval = (Sint16)(CLAMP(x_value) * SDL_JOYSTICK_AXIS_MAX);
					SDL_PrivateJoystickAxis(joystick, j, sval);

					sval = (Sint16)(CLAMP(y_value) * SDL_JOYSTICK_AXIS_MAX);
					SDL_PrivateJoystickAxis(joystick, j+1, sval);

					sval = (Sint16)(CLAMP(z_value) * SDL_JOYSTICK_AXIS_MAX);
					SDL_PrivateJoystickAxis(joystick, j+2, sval);

					sval = (Sint16)(CLAMP(z_rotation) * SDL_JOYSTICK_AXIS_MAX);
					SDL_PrivateJoystickAxis(joystick, j+3, sval);
					
					j += 4;
					break;

				case SensorType_HIDInput_Analog:
					GetSensorAttrTags(hwdata->stick[i], SENSORS_HIDInput_Value, (IPTR)&btn_value, TAG_DONE);

					sval = (Sint16)(btn_value * SDL_JOYSTICK_AXIS_MAX);
					SDL_PrivateJoystickAxis(joystick, j, sval);

					j++;
					break;

				case SensorType_HIDInput_AnalogStick:
					GetSensorAttrTags(hwdata->stick[i],
						SENSORS_HIDInput_EW_Value, (IPTR)&ew_value,
						SENSORS_HIDInput_NS_Value, (IPTR)&ns_value,
						TAG_DONE);

					sval = (Sint16)(CLAMP(ew_value) * SDL_JOYSTICK_AXIS_MAX);
					SDL_PrivateJoystickAxis(joystick, j, sval);

					sval = (Sint16)(CLAMP(ns_value) * SDL_JOYSTICK_AXIS_MAX);
					SDL_PrivateJoystickAxis(joystick, j+1, sval);

					j += 2;
					break;
			}
		}
		
		if (hwdata->battery) 
		{
			SDL_JoystickPowerLevel ePowerLevel = SDL_JOYSTICK_POWER_UNKNOWN;
			GetSensorAttrTags(hwdata->battery,
						SENSORS_HIDInput_Value, (IPTR)&bt_value,
						TAG_DONE);
			ULONG level = bt_value*100;
			switch (level)
			{
			   case 0 ... 5:
					ePowerLevel = SDL_JOYSTICK_POWER_EMPTY;
					break;
			   case 6 ... 20:
				   ePowerLevel = SDL_JOYSTICK_POWER_LOW;
					break;
			   case 21 ... 70:
					ePowerLevel = SDL_JOYSTICK_POWER_MEDIUM;
					break;
			   case 71 ... 100:
					ePowerLevel = SDL_JOYSTICK_POWER_FULL;
					break;
			}
			SDL_PrivateJoystickBatteryLevel(joystick, ePowerLevel);  
		}
	}
}

void MORPHOS_JoystickClose(SDL_Joystick *joystick)
{
	D("[%s]\n", __FUNCTION__);
	struct joystick_hwdata *hwdata = joystick->hwdata;
	if (hwdata) 
	{
		if (hwdata->child_sensors) 
		{
			ReleaseSensorsList(hwdata->child_sensors, NULL);
			hwdata->child_sensors = NULL;
		}
		SDL_free(hwdata);
		joystick->hwdata = NULL;
	}
}

void MORPHOS_JoystickQuit(void)
{
	D("[%s]\n", __FUNCTION__);
	if (sensorlist) {
		ReleaseSensorsList(sensorlist, NULL);
		sensorlist = NULL;
	}
}

static SDL_bool MORPHOS_JoystickGetGamepadMapping(int device_index, SDL_GamepadMapping *out)
{
    return SDL_FALSE;
}

SDL_JoystickDriver SDL_MORPHOS_JoystickDriver =
{
    MORPHOS_JoystickInit,
    MORPHOS_JoystickGetCount,
    MORPHOS_JoystickDetect,
    MORPHOS_JoystickGetDeviceName,
	MORPHOS_JoystickGetDevicePath,
	MORPHOS_JoystickGetDeviceSteamVirtualGamepadSlot,
    MORPHOS_JoystickGetDevicePlayerIndex,
    MORPHOS_JoystickSetDevicePlayerIndex,
    MORPHOS_JoystickGetDeviceGUID,
    MORPHOS_JoystickGetDeviceInstanceID,
    MORPHOS_JoystickOpen,
    MORPHOS_JoystickRumble,
    MORPHOS_JoystickRumbleTriggers,
    MORPHOS_JoystickGetCapabilities,
    MORPHOS_JoystickSetLED,
	MORPHOS_JoystickSendEffect,
	MORPHOS_JoystickSetSensorsEnabled,
    MORPHOS_JoystickUpdate,
    MORPHOS_JoystickClose,
    MORPHOS_JoystickQuit,
	MORPHOS_JoystickGetGamepadMapping
};

#endif
