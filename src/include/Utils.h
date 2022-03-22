#pragma once
#include "LTexture.h"

bool init();
bool loadMedia(const std::string str, LTexture &gTexture, std::vector<SDL_Rect> &gSprites);
void close();