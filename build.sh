COMPILE="/usr/local/opt/llvm/bin/clang++ src/*.cpp -I/Library/Frameworks/SDL2.framework/Headers -I/Library/Frameworks/SDL2_ttf.framework/Headers -I/Library/Frameworks/SDL2_image.framework/Headers -F/Library/Frameworks -framework SDL2 -framework SDL2_image -framework SDL2_ttf -w -o prog"
eval $COMPILE
