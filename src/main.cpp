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
    SDL_Rect camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    try
    {
        Utils::init(renderer, window);
        Dot dot(renderer);
        bool quit = true;
        LTexture gBGTexture;
        gBGTexture.loadFromFile("/Users/droidlakhera/Desktop/Projects/sdl2/kMag/res/img/bg.png", renderer);
        while (quit)
        {
            SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
            SDL_RenderClear(renderer);
            gBGTexture.render(0, 0, &camera, renderer);
            handleCamera(camera, dot);
            dot.update(quit);
            dot.render(renderer, camera);
            SDL_RenderPresent(renderer);
        }
    }
    catch (const char *e)
    {
        std::cout << "Exiting due to exception:\n\t" << e << std::endl;
    }
    Utils::close(renderer, window);
}

void handleCamera(SDL_Rect& camera, Dot &dot){
    camera.x = (dot.getPosX() + Dot::DOT_WIDTH / 2) - SCREEN_WIDTH / 2;
    camera.y = (dot.getPosY() + Dot::DOT_HEIGHT / 2) - SCREEN_HEIGHT / 2;

    if (camera.x < 0)
    {
        camera.x = 0;
    }
    if (camera.y < 0)
    {
        camera.y = 0;
    }
    if (camera.x > LEVEL_WIDTH - camera.w)
    {
        camera.x = LEVEL_WIDTH - camera.w;
    }
    if (camera.y > LEVEL_HEIGHT - camera.h)
    {
        camera.y = LEVEL_HEIGHT - camera.h;
    }
}