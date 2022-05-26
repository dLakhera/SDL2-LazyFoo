#include "include/LTexture.h"
#include "include/Utils.h"
#include "include/models.h"
#include "include/constants.h"
#include "include/Dot.h"
#include <iostream>
#include <exception>

void handleCamera(SDL_Rect&, Dot&);

int main(int argc, char *argv[])
{
    SDL_Renderer *renderer = NULL;
    SDL_Window *window = NULL;
    try
    {
        Utils::init(renderer, window);
        Dot dot(renderer);
        bool quit = true;
        LTexture gBGTexture;
        gBGTexture.loadFromFile("/Users/droidlakhera/Desktop/Projects/sdl2/kMag/res/img/mario-bg.png", renderer);
        int scrollingOffset = 0;
        while (quit)
        {
            SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
            SDL_RenderClear(renderer);
            --scrollingOffset;
            if (scrollingOffset < -gBGTexture.getWidth())
            {
                scrollingOffset = 0;
            }
            gBGTexture.render(scrollingOffset, 0, NULL, renderer);
            gBGTexture.render(scrollingOffset + gBGTexture.getWidth(), 0, NULL, renderer);
            dot.update(quit);
            dot.render(renderer);
            SDL_RenderPresent(renderer);
        }
    }
    catch (const char *e)
    {
        std::cout << "Exiting due to exception:\n\t" << e << std::endl;
    }
    Utils::close(renderer, window);
}
