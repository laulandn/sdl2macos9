# xcoff2app.sh: Takes an xcoff and creates a standard PPC application.

PATH_TO_RETRO68=$HOME/Retro68-build/toolchain/powerpc-apple-macos
PATH_TO_SDL2=$HOME/sdl2macos9
RINC=$PATH_TO_RETRO68/RIncludes
RES="$PATH_TO_SDL2/RetroPPCAPPL.r $PATH_TO_SDL2/SDL.r"

echo MakePEF -o $1.pef $1
MakePEF -o $1.pef $1

# Apple's Rez, just for reference, doesn't actually work
#cmd="/Developer/Tools/Rez $RES -s $RINC -a -t APPL -c 1234 -o $1.pef"

# Was testing this but don't think it works...keep for reference...
#cmd="Rez -I$RINC $RES --data $1.pef -t APPL -c 1234 -o $1.bin --cc $1.APPL --cc $1.dsk"
#cp $1.pef $1.APPL
#cp $PATH_TO_SDL2/resforkppc.raw .rsrc/$1.APPL
#cp $PATH_TO_SDL2/finfapp.raw .finf/$1.APPL

# This only exists on ancient MacOS X
if [[ -d "/Developer" ]]; then
  cp $1.pef $1.APPL
  cp $PATH_TO_SDL2/resforkppc.raw $1.APPL/rsrc
  cmd="/Developer/Tools/Setfile -t APPL -c '????' $1.APPL"
else
cmd="$PATH_TO_RETRO68/../bin/Rez -I$RINC $RES --data $1.pef -t APPL -c 1234 -o $1.bin --cc $1.APPL --cc $1.dsk"
cp $1.pef $1.APPL
fi

echo $cmd
$cmd
