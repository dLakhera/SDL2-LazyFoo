COMPILE="/usr/local/opt/llvm/bin/clang++ ${1} ./glad/src/glad.c -I/Library/Frameworks/SDL2.framework/Headers -I/Library/Frameworks/SDL2_image.framework/Headers -I./glad/include -F/Library/Frameworks -framework SDL2 -F/Library/Frameworks -framework SDL2_image -w -o prog"
echo ${COMPILE}
eval $COMPILE