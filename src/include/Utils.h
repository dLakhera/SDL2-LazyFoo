#pragma once
#include "LTexture.h"

bool init(/* std::vector<SDL_Rect> */);
bool loadMedia(const std::string str, LTexture &gTexture);
void close();
