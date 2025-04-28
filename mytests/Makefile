
CC=powerpc-apple-macos-gcc
CFLAGS=-I../SDL2
LD=powerpc-apple-macos-g++
LDFLAGS=-L.. -lSDL2


.c.o:
	$(CC) $(CFLAGS) -c -o$*.o $*.c

.cpp.o:
	$(CC) $(CFLAGS) -c -o$*.o $*.cpp


all: test

clean:
	rm -f test *.o *.pef *.dsk *.APPL *.bin


test: test.o
	$(LD) -otest test.o ../SDL_main.o $(LDFLAGS)
	$(HOME)/sdl2macos9/xcoff2app.sh test


