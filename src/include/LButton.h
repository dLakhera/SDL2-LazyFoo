#pragma once
#include "LTexture.h"

class LButton
{
public:
    LButton();
    void setPosition(int x, int y);
    void handleEvent(SDL_Event *e);
    void render(LTexture *&, std::vector<SDL_Rect> &);

private:
    SDL_Point mPosition;
    int mCurrentSprite;
};