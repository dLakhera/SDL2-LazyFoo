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
    std::vector<SDL_Rect> gSprites(WALKING_ANIMATION_FRAMES);
    loadMedia("img/stickman.png", gTexture, gSprites);
    int frames = 0;
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

        gTexture.render((SCREEN_WIDTH - gTexture.getWidth()) / 2, (SCREEN_HEIGHT - gTexture.getHeight()) / 2, &gSprites[frames/4]);
        SDL_RenderPresent(gRenderer);
        frames++;
        if(frames/4 >= WALKING_ANIMATION_FRAMES) {
            frames = 0;
        }
    }

    close();
}