COMPILE="clang++ -std=c++11 ${1} ./glad/src/glad.c -o prog -I/Library/Frameworks/SDL2.framework/Headers -I/Library/Frameworks/SDL2_Image.framework/Headers -I./glad/include -F/Library/Frameworks -framework SDL2"
echo ${COMPILE}
eval $COMPILE