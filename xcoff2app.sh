PATH_TO_RETRO68=$HOME/Retro68-build/toolchain/m68k-apple-macos
PATH_TO_SDL2=$HOME/sdl2macos9
RINC=$PATH_TO_RETRO68/RIncludes
RES="$PATH_TO_SDL2/RetroPPCAPPL.r $PATH_TO_SDL2/SDL.r"

echo MakePEF -o $1.pef $1
MakePEF -o $1.pef $1
echo Rez -I$RINC $RES --data $1.pef -t "APPL" -c "????" -o $1.bin --cc $1.APPL --cc $1.dsk
Rez -I$RINC $RES --data $1.pef -t "APPL" -c "????" -o $1.bin --cc $1.APPL --cc $1.dsk


