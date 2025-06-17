PATH_TO_RETRO68=$HOME/Retro68-build/toolchain/powerpc-apple-macos
PATH_TO_SDL2=$HOME/sdl2macos9
RINC=$PATH_TO_RETRO68/RIncludes
RES="$PATH_TO_SDL2/RetroPPCAPPL.r $PATH_TO_SDL2/SDL.r"

echo MakePEF -o $1.pef $1
MakePEF -o $1.pef $1

# Just for reference, doesn't actually work
#cmd="/Developer/Tools/Rez $RES -s $RINC -a -t APPL -c '????' -o $1.pef"

# Uncomment on Linux
#cmd="Rez -I$RINC $RES --data $1.pef -t APPL -c 1234 -o $1.bin --cc $1.APPL --cc $1.dsk"

# Uncomment on MacOS X
cp $1.pef $1.APPL
cp $PATH_TO_SDL2/resforkcarb.raw $1.APPL/rsrc
cmd="/Developer/Tools/Setfile -t APPL -c '????' $1.APPL"

echo $cmd
$cmd
