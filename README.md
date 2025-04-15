This is a "rough draft" of SDL2 for MacOS 9 (also working on System 7.6 68k), using CodeWarrior Pro 6 and 7. Enough was done to get it building in CW, and the start of a "macosclassic" video driver was created. It DOES seem to basically work, but much still needs to be done. Event handling is just started, there is no audio etc. etc. etc.

NOTE: This is obvious in flux, and active development. So if something is broken, try again tomorrow...next week...maybe? I'm including a known working (but old) "_prev" version that will NOT be updated, for archival reasons.

----

Dev notes: Getting just SDL2 itself building, did take a lot of effort, but it was mostly "mechanical", dealing with the foibles of CodeWarrior, creating project files from scratch, things it couldn't handle, "simple" things like headers missing that are standard on more modern systems, etc. The first step was doing that with all "dummy" drivers. Was a bit shocked I got even that far. The results did absolutely NOTHING in the test programs. With a dummy video driver, they don't even try to set up textures, etc.

The key missing part was a Classic Mac OS "video" driver, which also includes event handling. I determined it was not possible to "port" the SDL1 driver due to too many changes in paradigms of SDL itself. Once I'd sketched a new one out, and got it hooked into the proper places, the debug output showed the test programs actually working. I then started adding basic Mac OS implementations. This effort is in src/video/macosclassic. (I used the QNX driver as a skeleton as it was the smallest and easier to understand.)

Mini-FAQ:
"What is SDL?": Like DirectX, a library for multimedia games/apps, but runs on many many platforms.
"Why is this interesting?": Games, potentially...
"Why not SDL3?": Because you have to learn to walk before you can fly.
"Why not Retro68?": Because CodeWarrior is a heck of a lot more user friendly for casual hacking.
"Why MacOS 7/8/9 in 2025?": Because it looked like it was possible, and nobody else bothered.
"Why CW6/7?": Because I was already hacking on SDL 1.2 with those and they were handy.
"Where are the games?!?": There's a terrible one included that (mostly) works, but this is very early days...maybe try a port yourself and see what works?
