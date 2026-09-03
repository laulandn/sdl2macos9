PATH_TO_TOOLS=$(HOME)/Downloads/ps2dev/iop/bin
PATH_TO_SDK=$(HOME)/Downloads/PSn00bSDK/libpsn00b

.SUFFIXES:	.elf

CC = $(PATH_TO_TOOLS)/mipsel-none-elf-gcc
CXX = $(PATH_TO_TOOLS)/mipsel-none-elf-g++

INCPATH+= -I"../include" -I../../psxaddons  -I$(PATH_TO_SDK)/include

LIBPATH = -L..
#LIBS    = -lSDL2_test -lSDL2 -lm -lRetroConsole
#LIBS    = -lSDL2_test -lSDL2 -lm ../../macos8addons/libmacos8addons.a -lOpenGLLibrary
#LIBS    = -lSDL2_test -lSDL2 -lm ../../macos8addons/libmacos8addons.a -L$(HOME)/tinygl-main1/lib -lTinyGL -lagl -lgl
#LIBS    =  -lSDL2_test -lSDL2 -lm $(HOME)/Mesa-3.2.1/libmesa.a ../../macos8addons/libmacos8addons.a  $(HOME)/MacGLide-master/MacGLide/OpenGLide/libOpenGlide.a $(HOME)/MacGLide-master/MacGLide/Mac/libMac.a
#LIBS    = -lSDL2_test -lSDL2 -lm -lThreadsLib 
LIBS    = -lSDL2_test -lSDL2 -L../../Baselibc -lc -L../../psxaddons -lpsxaddons

#CFLAGS+= -DHAVE_SDL_TTF
#TTFLIBS = SDL2ttf.lib

CFLAGS+= $(INCPATH) -D__PS1__ -DHAVE_OPENGL=1

TARGETS = testatomic.elf testdisplayinfo.elf testbounds.elf testdraw2.elf \
          testdrawchessboard.elf testdropfile.elf testerror.elf testfile.elf \
          testfilesystem.elf testgamecontroller.elf testgeometry.elf testgesture.elf \
          testhittesting.elf testhotplug.elf testiconv.elf testime.elf testlocale.elf \
          testintersections.elf testjoystick.elf testkeys.elf testloadso.elf \
          testlock.elf testmessage.elf testoverlay2.elf testplatform.elf \
          testpower.elf testsensor.elf testrelative.elf testrendercopyex.elf \
          testrendertarget.elf testrumble.elf testscale.elf testsem.elf \
          testshader.elf testshape.elf testsprite2.elf testspriteminimal.elf \
          teststreaming.elf testthread.elf testtimer.elf testver.elf \
          testviewport.elf testwm2.elf torturethread.elf checkkeys.elf \
          checkkeysthreads.elf testmouse.elf testgles.elf testgles2.elf \
          controllermap.elf testhaptic.elf testqsort.elf testresample.elf \
          testaudioinfo.elf testaudiocapture.elf loopwave.elf loopwavequeue.elf \
          testsurround.elf testyuv.elf testgl2.elf testvulkan.elf testnative.elf \
          testaudiohotplug.elf testcustomcursor.elf testmultiaudio.elf \
          testoffscreen.elf testurl.elf

noninteractive = \
	testatomic.elf \
	testerror.elf \
	testfilesystem.elf \
	testkeys.elf \
	testlocale.elf \
	testplatform.elf \
	testpower.elf \
	testqsort.elf \
	testthread.elf \
	testtimer.elf \
	testver.elf

needs_audio = \
	testaudioinfo.elf \
	testsurround.elf

needs_display = \
	testbounds.elf \
	testdisplayinfo.elf

TESTS = $(noninteractive) $(needs_audio) $(needs_display)

# testautomation sources
TASRCS = testautomation.c \
	testautomation_audio.c testautomation_clipboard.c \
	testautomation_events.c testautomation_guid.c \
	testautomation_hints.c testautomation_joystick.c \
	testautomation_keyboard.c testautomation_log.c \
	testautomation_main.c testautomation_math.c \
	testautomation_mouse.c testautomation_pixels.c \
	testautomation_platform.c testautomation_rect.c \
	testautomation_render.c testautomation_rwops.c \
	testautomation_sdltest.c testautomation_stdlib.c \
	testautomation_subsystems.c testautomation_surface.c \
	testautomation_syswm.c testautomation_timer.c \
	testautomation_video.c

OBJS = $(TARGETS:.elf=.o)
COBJS = $(CSRCS:.c=.o)
TAOBJS = $(TASRCS:.c=.o)
TNOBJS = $(TNSRCS:.c=.o)


all: testutils.lib $(TARGETS)


.o.elf:
	$(CC) -o $*.elf $< testutils.o testyuv_cvt.o ../src/main/ps1/SDL_main.o $(LIBPATH) $(LIBS)
#	../../bin2app.sh $*

%.o : %.c
	@echo Compiling $<
	@$(CC) -o $@ -c $< $(CFLAGS)


# specials

#testautomation_stdlib.o: testautomation_stdlib.c
#	 $(CFLAGS) -wcd=201 -fo=$^@ $<

#testautomation.elf: $(TAOBJS)
#	 $(CC) $(LIBPATH) lib {$(LIBS)} op q op el file {$<} name $@


testutils.lib: testutils.o testyuv_cvt.o
#  wlib -q -b -n -c -pa -s -t -zld -ii -io $@ $<

check: .SYMBOLIC $(TESTS)
#  @set SDL_AUDIODRIVER=dummy
#  @set SDL_VIDEODRIVER=dummy
#  @copy ..\SDL2.dll .
#  @for .elf in ($(TESTS)) do .elf

check-quick: .SYMBOLIC $(TESTS)
#  @set SDL_TESTS_QUICK=1
#  @set SDL_AUDIODRIVER=dummy
#  @set SDL_VIDEODRIVER=dummy
#  @copy ..\SDL2.dll .
#  @for .elf in ($(TESTS)) do .elf

clean:
	rm -rf *.o *.err *.elf *.pef *.dsk *.bin *.APPL *.gdb .rsrc .finf
	rm -f testkeys testoverlay2 testscale testaudioinfo testlocale testvulkan testintersect ions testerror testviewport testcustomcursor testmessage testrendertarget testver test file testsurround testgl2 controllermap testmouse testplatform testhotplug testdisplay info testloadso loopwave testsem checkkeysthreads testresample testgamecontroller chec kkeys testshader testsensor testyuv testsprite2 testime testurl testshape testiconv te stgles teststreaming testtimer testatomic testoffscreen testwm2 testbounds testthread testgles2 testgeometry testspriteminimal testrumble torturethread testdraw2 testaudioh otplug testhittesting testjoystick testrelative testmultiaudio testpower testaudiocapt ure loopwavequeue testdropfile testfilesystem testqsort testdrawchessboard testnative testrendercopyex testlock testgesture testhaptic testgles testintersections testfile testaudiocapture testaudiohotplug checkkeys testdisplayinfo

distclean: clean
	rm -f *.elf *.lib
