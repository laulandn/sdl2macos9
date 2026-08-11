This is a utility lib that fakes out a few functions from sdl_image.

It can be used to provide some bare minimal functionality, ie loading image formats the base SDL knows how, without actually using the real sdl_image.

Using this, it will only load .bmp files, but should work fine just for those.
