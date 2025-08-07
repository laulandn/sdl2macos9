This is SDL2, an extremely popular library used for building multimedia apps and games.

For classic MacOS 7/8/9 m68k and ppc, using Retro68. CodeWarrior support is broken but could be fixed "relatively" easily. Also includes AmigaOS 3 for m68k support, and should work on related systems.

https://github.com/laulandn/sdl2macos9
(Obviously Mac Finder file creators and types and resource forks are lost there.)

I discussed what I worked on and kept a running commentary over at System7Today for a while:
SDL2 for PPC MacOS 9 efforts...

Works well enough to port 2d games (several attempts at various stages are included as separate downloads), and speed is comparable to SDL 1.2.

I'm pausing active development, and consider it about 2/3 done. If anyone is interested in finishing, or using this to port a game, leave a note or contact me, and we'll talk.

What remains to be done:
* OpenGL: Hooks in video driver are present and called, but no driver exists for either MacOS or Amiga.
* Audio: Non-functional skeleton driver for MacOS (disabled SDL 1.2 driver source is in tree ready to be ported). Seems fully functional on Amiga.
* Joystick: Non-functional skeleton driver for MacOS (disabled SDL 1.2 driver source is in tree ready to be ported). No support on Amiga.
* Threads: Some "wait" functions are not implemented correctly on MacOS, works as well as cooperative can be expected. There seem to be a few bugs on Amiga.
* Misc: Timers not fully tested. Loadso never tested. Some file funcs could be better.