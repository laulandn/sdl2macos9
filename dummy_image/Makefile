AR = powerpc-apple-macos-ar
RANLIB = powerpc-apple-macos-ranlib
CC = powerpc-apple-macos-gcc

LIBNAME = libSDL_image.a


all:
	$(CC) -I../SDL2 -I. -c image_dummy.c 
	rm -f *.a
	$(AR) crv $(LIBNAME) *.o
	$(RANLIB) $(LIBNAME)

clean:
	rm -f *.o *.a
