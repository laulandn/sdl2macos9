PATH_TO_RETRO68=$HOME/Retro68-build/toolchain/powerpc-apple-macos
PATH_TO_SDL2=$HOME/sdl2macos9
RINC=$PATH_TO_RETRO68/RIncludes
RES="$PATH_TO_SDL2/RetroPPCAPPL.r $PATH_TO_SDL2/SDL.r"

mkdir $1.app
mkdir $1.app/Contents
mkdir $1.app/Contents/MacOS
mkdir $1.app/Contents/Resources
mv $1 $1.app/Contents/MacOS

cp $PATH_TO_SDL2/PkgInfo $1.app/Contents
sed s/ClockView/$1/g $PATH_TO_SDL2/Info.plist >$1.app/Contents/Info.plist
