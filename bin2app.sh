PATH_TO_RETRO68=$HOME/Retro68-build/toolchain/m68k-apple-macos
PATH_TO_SDL2=$HOME/sdl2macos9
RINC=$PATH_TO_RETRO68/RIncludes
RES="$PATH_TO_SDL2/Retro68APPL.r $PATH_TO_SDL2/SDL.r"


Rez -I$RINC $RES --copy $1.code.bin -t "APPL" -c "????" -o $1.bin --cc $1.APPL --cc $1.dsk
echo Rez -I$RINC $RES --copy $1.code.bin -t "APPL" -c "????" -o $1.bin --cc $1.APPL --cc $1.dsk

