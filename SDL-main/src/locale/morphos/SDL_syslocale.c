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

#include "../../SDL_internal.h"
#include "../SDL_syslocale.h"

#include <proto/dos.h>
#include <proto/utility.h>
#include <libraries/iffparse.h>

struct loc
{
	const char *name;
	const char *codeLang;
};

static const struct loc locs[] =
{
	{ "català",		"ca_ES" }, 
	{ "dansk",		"da_DK" },
	{ "deutsch",	"de_DE" },
	{ "english",	"en_GB" },
	{ "español",	"es_ES" },
	{ "français",	"fr_FR" },
	{ "greek",		"el_GR" },
	{ "hrvatski",	"hr_HR" },
	{ "italiano",	"it_IT" },
	{ "magyar",		"hu_HU" },
	{ "malti",		"mt_MT"	},
	{ "nederlands",	"nl_NL" },
	{ "norsk",		"nn_NO" },
	{ "polski",		"pl_PL" },
	{ "português",	"pt_PT" },
	{ "shqipja"		"sq_AL" },
	{ "suomi",		"fi_FI" },
	{ "svenska",	"sv_SE" },
	{ "türkçe",		"tr_TR" },
	{ "èe¹tina",	"cs_CZ" },
	{ "íslenska", 	"is_IS" },  
	{ NULL,			NULL } 
};

void
SDL_SYS_GetPreferredLocales(char *buf, size_t buflen)
{
	D("[%s]\n", __FUNCTION__);
	
	char language[80];
	language[0] = '\0';
	SDL_bool found = SDL_FALSE;

	// check the LANGUAGE env variable
	if (GetVar("LANGUAGE", language, sizeof(language), 0) > 0)
	{
		int i;
		const struct loc *curLoc = NULL;

		for(i=0;;i++)
		{
			curLoc = &locs[i];

			if(Strnicmp(language, curLoc->name, sizeof(curLoc->name)) == 0)
			{
			  D("[%s] found language name for '%s'\n", __FUNCTION__, curLoc->codeLang);
			  snprintf(buf, buflen, curLoc->codeLang);
			  found = SDL_TRUE;
			  break;
			}
		}

	}
	if (!found)
		snprintf(buf, buflen, "en_GB");  

}
