#include "include/LTexture.h"
#include "include/global.h"
#include "include/Utils.h"
#include "include/models.h"
#include <iostream>

std::vector<SDL_Rect> gButtonOnSprite;
std::vector<LButton> gButtons;

int SCREEN_WIDTH = 640;
int SCREEN_HEIGHT = 480;
int WALKING_ANIMATION_FRAMES = 4;
int BUTTON_WIDTH = 300;
int BUTTON_HEIGHT = 200;
int TOTAL_BUTTONS = 5;

LTexture gTexture;

int main(int argc, char *argv[])
{
    bool success = Utils::init();
    if (!success)
    {
        return 0;
    }
    bool quit = true;
    std::vector<std::string> str = {
        "/Users/droidlakhera/Desktop/Projects/sdl2/kMag/res/img/up.png",
        "/Users/droidlakhera/Desktop/Projects/sdl2/kMag/res/img/down.png",
        "/Users/droidlakhera/Desktop/Projects/sdl2/kMag/res/img/left.png",
        "/Users/droidlakhera/Desktop/Projects/sdl2/kMag/res/img/right.png",
        "/Users/droidlakhera/Desktop/Projects/sdl2/kMag/res/img/default.png",
    };
    if (!Utils::loadMedia(str))
    {
        return 0;
    }
    while (quit)
    {
        SDL_Event e;
        KButton currentSprite = BUTTON_SPRITE_DEFAULT;
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quit = false;
            }
        }
        currentSprite = Utils::handleEvent();
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);
        gKButtons[currentSprite].render();
        SDL_RenderPresent(gRenderer);
    }
    Utils::close();
}
