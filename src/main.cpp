#pragma once
#include "include/LTexture.h"
#include "include/Utils.h"
#include "include/global.h"
#include <iostream>

int SCREEN_WIDTH = 640;
int SCREEN_HEIGHT = 480;
int WALKING_ANIMATION_FRAMES = 4;
int BUTTON_WIDTH = 300;
int BUTTON_HEIGHT = 200;
int TOTAL_BUTTONS = 4;
LTexture gTexture;
std::vector<SDL_Rect> gButtonOnSprite;
std::vector<LButton> gButtons;


int main(int argc, char *argv[])
{
    gButtonOnSprite.resize(4);
    gButtons.resize(4);
    bool success = init();
    if (!success)
    {
        return 0;
    }
    bool quit = true;
    loadMedia("/Users/droidlakhera/Desktop/Projects/sdl2/kMag/res/img/button.png", gTexture);
    while (quit)
    {
        SDL_Event e;
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quit = false;
            }
            for (int i = 0; i < TOTAL_BUTTONS; ++i)
            {
                gButtons[i].handleEvent(&e);
            }
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);

        {
            gButtons[i].render();
        }
        gTexture.render((SCREEN_WIDTH - gTexture.getWidth()) / 2, (SCREEN_HEIGHT - gTexture.getHeight()) / 2);
        SDL_RenderPresent(gRenderer);
    }

    close();
}