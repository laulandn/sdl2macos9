/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2022 Sam Lantinga <slouken@libsdl.org>

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

#include "SDL_stdinc.h"

#include <string.h>
#include <sys/types.h>

#include <proto/charsets.h>

char *
MOS_ConvertText(const char *src, LONG srcmib, LONG dstmib)
{
	size_t dstlen, tags[] = { CST_GetDestBytes, (size_t)&dstlen, TAG_DONE };
	char *dst = NULL;

	ConvertTagList((APTR)src, -1, NULL, -1, srcmib, dstmib, (struct TagItem *)&tags);

	dstlen += 1;
	dst = SDL_malloc(dstlen);

	if (dst)
		ConvertTagList((APTR)src, -1, dst, dstlen, srcmib, dstmib, NULL);

	return dst;
}

char *
MOS_ConvertPath(const char *fn)
{
	CONST_STRPTR src = fn;
	ULONG flen = strlen(fn);
	BOOL colon = FALSE;
	char *dst, *path = SDL_malloc(flen + 2 + 128);

	dst = path;

	if (*src == '/')
	{
		/* really depends on filesystem layout, hope for the best */
		colon	= 1;
		src++;
	}

	while ((size_t)src < (size_t)(fn + flen))
	{
		const char *end = strchr(src, '/');
		int len;

		if(!end)
			end = fn + flen; /* last component */

		len = (size_t)end - (size_t)src;

		if(len == 0 || (len == 1 && src[0] == '.'))
		{
			/* remove repeated slashes and . */
		}
		else
		{
			if (len == 1 && colon)
			{
				*dst++ = ':';
				colon  = FALSE;
			}
			else if (len == 2 && src[0] == '.' && src[1] == '.')
			{
				/* replace .. with the empty string */
			}
			else
			{
				bcopy((void *)src, (void *)dst, len);
				dst += len;
			}

			if(end < fn + flen)
				*dst++ = '/';
		}

		src = end + 1;
	}

	*dst++ = '\0';
	return path;
}
