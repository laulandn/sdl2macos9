LIBNAME=macos8addons

CC=m68k-apple-macos-gcc
CXX=m68k-apple-macos-g++
AR=m68k-apple-macos-ar
RANLIB=m68k-apple-macos-ranlib
#CC=powerpc-apple-macos-gcc
#CXX=powerpc-apple-macos-g++
#AR=powerpc-apple-macos-ar
#RANLIB=powerpc-apple-macos-ranlib

CFLAGS= 

OBJS=$(subst .c,.o,$(wildcard *.c))

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<


lib: $(OBJS)
	$(AR) rcv lib$(LIBNAME).a $(OBJS)
	$(RANLIB) lib$(LIBNAME).a

all: $(OBJS)

clean:
	rm -f *.o *.a
