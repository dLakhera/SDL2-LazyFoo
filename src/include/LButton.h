#pragma once
#include "LTexture.h"

class LButton
{
public:
    LButton();
    void setPosition(int x, int y);
    void handleEvent(SDL_Event *e);
    void render();

private:
    SDL_Point mPosition;
    int mCurrentSprite;
};