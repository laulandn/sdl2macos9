# bin2app.sh: Takes a CODE resource and creates an m68k application.

PATH_TO_RETRO68=$HOME/Retro68-build/toolchain/m68k-apple-macos
PATH_TO_SDL2=$HOME/sdl2macos9
RINC=$PATH_TO_RETRO68/RIncludes
RES="$PATH_TO_SDL2/Retro68APPL.r $PATH_TO_SDL2/SDL.r"

# Apple's Rez, just for reference, doesn't actually work
#cmd="/Developer/Tools/Rez $RES -s $RINC -a -t APPL -c '????' -o $1.pef"

# This only exists on ancient MacOS X
if [[ -d "/Developer" ]]; then
  cp $1.pef $1.APPL
  cp $PATH_TO_SDL2/ppcresfork.raw $1.APPL/rsrc
  cmd="/Developer/Tools/Setfile -t APPL -c '????' $1.APPL"
else
cmd="$PATH_TO_RETRO68/../bin/Rez -I$RINC $RES --copy $1.code.bin -t APPL -c 1234 -o $1.bin --cc $1.APPL --cc $1.dsk"
fi

echo $cmd
$cmd

