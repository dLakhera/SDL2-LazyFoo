#include "include/LTexture.h"
#include "include/global.h"
#include "include/Utils.h"
#include "include/models.h"
#include "include/constants.h"
#include "include/Dot.h"
#include <iostream>
#include <exception>

std::vector<SDL_Rect> gButtonOnSprite;
std::vector<LButton> gButtons;

LTexture gTexture;

int main(int argc, char *argv[])
{
    SDL_Renderer *renderer = NULL;
    try
    {
        Utils::init(renderer);
        Dot dot(renderer);
        bool quit = true;
        SDL_Rect wall = {300, 40, 40, 400};
        while (quit)
        {
            SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
            SDL_RenderClear(renderer);

            SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
            SDL_RenderDrawRect(renderer, &wall);

            dot.update(quit, wall);
            dot.render(renderer);
            SDL_RenderPresent(renderer);
        }
    }
    catch (const char *e)
    {
        std::cout << "Exiting due to exception:\n\t" << e << std::endl;
    }
    Utils::close(renderer);
}
