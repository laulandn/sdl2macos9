# Makefile to build the SDL 2 Library

CC      = ppc-morphos-gcc-11 -noixemul
INCLUDE = -I../../../../include -I../sdk
CFLAGS  = -mcpu=750 -mtune=7450 -O3 $(INCLUDE) -Wall -Wno-pointer-sign -fno-strict-aliasing -D_LARGEFILE64_SOURCE
AR	= ppc-morphos-ar
CVI = /gg/bin/cvinclude.pl

ECHE = echo -e
BOLD = \033[1m
NRML = \033[22m

COMPILING = @$(ECHE) "compiling $(BOLD)$@$(NRML)..."
LINKING = @$(ECHE) "linking $(BOLD)$@$(NRML)..."
STRIPPING = @$(ECHE) "stripping $(BOLD)$@$(NRML)..."
ARCHIVING = @$(ECHE) "archiving $(BOLD)$@$(NRML)..."

all: lib/libSDL2.a lib/libb32/libSDL2.a lib/libb32/libSDL2-nc.a

lib: all

install: all
install-iso: all

sdl-startup.o: sdl-startup.c sdl-stubs.c
	$(COMPILING)
	@$(CC) $(CFLAGS) -o $@ -c sdl-startup.c

sdl-startup-brel.o: sdl-startup.c sdl-stubs.c
	$(COMPILING)
	@$(CC) $(CFLAGS) -mresident32 -o $@ -c sdl-startup.c

sdl-startup-brel-nc.o: sdl-startup.c sdl-stubs.c
	$(COMPILING)
	@$(CC) $(CFLAGS) -mresident32 -o $@ -c sdl-startup.c -D__NO_SDL_CONSTRUCTORS

lib/libSDL2.a: sdl-startup.o ../sdk/fd/sdl2_lib.fd
	$(ARCHIVING)
	@mkdir -p lib
	@-rm -f $@
	@$(CVI) --fd=../sdk/fd/sdl2_lib.fd --clib=../sdk/clib/sdl2_protos.h --gluelib=$@
	@$(AR) crus $@ sdl-startup.o 

lib/libb32/libSDL2.a: sdl-startup-brel.o  ../sdk/fd/sdl2_lib.fd
	$(ARCHIVING)
	@mkdir -p lib/libb32
	@-rm -f $@
	@$(CVI) --fd=../sdk/fd/sdl2_lib.fd --clib=../sdk/clib/sdl2_protos.h --brelgluelib=$@
	@$(AR) crus $@ sdl-startup-brel.o

lib/libb32/libSDL2-nc.a: sdl-startup-brel-nc.o ../sdk/fd/sdl2_lib.fd
	$(ARCHIVING)
	@mkdir -p lib/libb32
	@-rm -f $@
	@$(CVI) --fd=../sdk/fd/sdl2_lib.fd --clib=../sdk/clib/sdl2_protos.h --brelgluelib=$@
	@$(AR) crus $@ sdl-startup-brel-nc.o
clean:
	@-rm -rf lib *.s *.o

dump:
	ppc-morphos-objdump --disassemble-all --reloc lib/libSDL2.a >lib/libSDL2.s
