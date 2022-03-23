#pragma once
#include "include/LTexture.h"
#include "include/Utils.h"
#include "include/global.h"
#include <iostream>

int SCREEN_WIDTH = 640;
int SCREEN_HEIGHT = 480;
int WALKING_ANIMATION_FRAMES = 4;
LTexture gTexture;

int main(int argc, char *argv[])
{
    bool success = init();
    if (!success)
    {
        return 0;
    }
    bool quit = true;
    loadMedia("/Users/droidlakhera/Desktop/Projects/sdl2/kMag/res/fonts/lazy.ttf", gTexture);
    double degrees = 0.0;
    SDL_RendererFlip flipType = SDL_FLIP_NONE;
    while (quit)
    {
        SDL_Event e;
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quit = false;
            }
        }
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);

        gTexture.render((SCREEN_WIDTH - gTexture.getWidth()) / 2, (SCREEN_HEIGHT - gTexture.getHeight()) / 2);
        SDL_RenderPresent(gRenderer);
    }

    close();
}