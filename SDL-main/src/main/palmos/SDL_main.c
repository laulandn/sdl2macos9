/*
    SDL - Simple DirectMedia Layer
    Copyright (C) 1997-2012 Sam Lantinga

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

    Sam Lantinga
    slouken@libsdl.org
*/

/* Include the SDL main definition header */
#include "SDL.h"
#include "SDL_main.h"
#ifdef main
#undef main
#endif

#ifdef SDL_MAIN_NEEDED


/* This is where execution begins */
int main(int argc, char *argv[])
{

        //SDL_SetMainReady();

        argc=1;
        argv[1]="";
        argv[2]="";

	SDL_main(argc,argv);
   	
	/* Exit cleanly, calling atexit() functions */
	exit (0);    

	/* Never reached, but keeps the compiler quiet */
	return (0);
}w

#endif
