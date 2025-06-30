
CC=powerpc-apple-macos-gcc
#CC=m68k-apple-macos-gcc
#CC=m68k-amigaos-gcc -mcrt=nix20

CFLAGS=-I../SDL-main/include
#CFLAGS=`sdl2-config --cflags`

LD=powerpc-apple-macos-g++
#LD=m68k-apple-macos-g++
#LD=m68k-amigaos-g++ -mcrt=nix20

#LDFLAGS=-L.. -lSDL2main -lSDL2
LDFLAGS=-L../SDL-main -lSDL2 -lSDL2main -lThreadsLib
#LDFLAGS=-L../SDL-main -lSDL2 -lSDL2main

CONV=$(HOME)/sdl2macos9/xcoff2app.sh
#CONV=$(HOME)/sdl2macos9/bin2app.sh
#CONV=echo

#EXT=.code.bin

.c.o:
	$(CC) $(CFLAGS) -c -o$*.o $*.c

.cpp.o:
	$(CC) $(CFLAGS) -c -o$*.o $*.cpp


all: test

clean:
	rm -f test *.o *.pef *.dsk *.APPL *.bin *.gdb
	rm -f sdlmut sdlsem sdlthread sdlthread2 test test2 test3 test4 test5 test6 macthread


test: test.o
	$(LD) -otest$(EXT) test.o $(LDFLAGS)
	$(CONV) test

sdlthread: sdlthread.o
	$(LD) -osdlthread$(EXT) sdlthread.o $(LDFLAGS)
	$(CONV) sdlthread

sdlthread2: sdlthread2.o
	$(LD) -osdlthread2$(EXT) sdlthread2.o $(LDFLAGS)
	$(CONV) sdlthread2

sdlsem: sdlsem.o
	$(LD) -osdlsem$(EXT) sdlsem.o $(LDFLAGS)
	$(CONV) sdlsem

sdlmut: sdlmut.o
	$(LD) -osdlmut$(EXT) sdlmut.o $(LDFLAGS)
	$(CONV) sdlmut


macthread: macthread.o
	$(LD) -omacthread$(EXT) macthread.o $(LDFLAGS)
	$(CONV) macthread

