COMPILE="/usr/local/opt/llvm/bin/clang++ src/*.cpp -I/Library/Frameworks/SDL2.framework/Headers -I/Library/Frameworks/SDL2_image.framework/Headers -F/Library/Frameworks -framework SDL2 -F/Library/Frameworks -framework SDL2_image -w -o prog"
eval $COMPILE