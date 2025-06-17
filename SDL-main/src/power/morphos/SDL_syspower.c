/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2021 Sam Lantinga <slouken@libsdl.org>

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

#ifndef SDL_POWER_DISABLED
#ifdef SDL_POWER_MORPHOS

#include <libraries/sensors.h>
#include <proto/sensors.h>

#include "SDL_power.h"

SDL_bool
SDL_GetPowerInfo_MorphOS(SDL_PowerState *state, int *seconds, int *percent)
{
	static const size_t battery_sensortags[] = { SENSORS_Type, SensorType_Battery, TAG_DONE };

	APTR sensorlist = ObtainSensorsList((struct TagItem *)&battery_sensortags);
	APTR sensor = NULL;
	ssize_t maxcap = 0, totcap = 0, val, charging = 0, totsecs = 0;
	SDL_PowerState st = SDL_POWERSTATE_NO_BATTERY;

	while ((sensor = NextSensor(sensor, sensorlist, NULL))) {
		ssize_t capacity, max_capacity, is_batt_present, is_batt_charging, secs_remaining;

		struct TagItem battags[6] =
		{
			{ SENSORS_Battery_Capacity, (size_t)&capacity },
			{ SENSORS_Battery_MaxCapacity, (size_t)&max_capacity },
			{ SENSORS_Battery_Present, (size_t)&is_batt_present },
			{ SENSORS_Battery_Charging, (size_t)&is_batt_charging },
			{ SENSORS_Battery_Remaining, (size_t)&secs_remaining },
			{ TAG_DONE }
		};

		if (GetSensorAttr(sensor, battags) >= 5 && is_batt_present) {
			maxcap += max_capacity;
			totcap += capacity;

			if (secs_remaining != SENSORS_Battery_Remaining_Calculating)
				totsecs += secs_remaining;

			if (is_batt_charging && secs_remaining != SENSORS_Battery_Remaining_Charged)
				charging++;
		}
	}

	ReleaseSensorsList(sensorlist, NULL);

	if (charging)
	{
		st = SDL_POWERSTATE_CHARGING;
	}
	else if (maxcap > 0)
	{
		if (totcap < maxcap)
			st = SDL_POWERSTATE_ON_BATTERY;
		else
			st = SDL_POWERSTATE_CHARGED;
	}

	*state = st;
	*seconds = totsecs == 0 ? -1 : totsecs;
	val = -1;

	if (maxcap > 0)
	{
		val = (totcap * 100) / maxcap;
		val = val > 100 ? 100 : val;
	}

	*percent = val;

	return SDL_TRUE;
}

#endif /* SDL_POWER_MORPHOS */
#endif /* SDL_POWER_DISABLED */

