#include "include/Utils.h"
#include "include/global.h"
#include "include/models.h"
#include "include/constants.h"
#include <iostream>

SDL_Window *gWindow = NULL;
std::vector<LTexture> gKButtons;

void Utils::init(SDL_Renderer* &renderer)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        throw "Init failed()!";
    }
    else
    {
        gWindow = SDL_CreateWindow("KMag", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL)
        {
            printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
            throw "Init failed()!";
        }
        else
        {
            renderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
            if (renderer == NULL)
            {
                printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
                throw "Init failed()!";
            }
        }
    }
}

void Utils::loadMedia(SDL_Renderer* renderer)
{
    gKButtons.clear();
    gKButtons.resize(str.size(), LTexture());

    for (int i = 0; i < str.size(); i++)
    {
        gKButtons[i].loadFromFile(str[i].c_str(), renderer);
    }
}

void Utils::loadMedia(const std::string str, LTexture &gTexture, SDL_Renderer *renderer)
{
    gTexture.loadFromFile(str.c_str(), renderer);
}

void Utils::close(SDL_Renderer *renderer)
{
    gTexture.free();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    renderer = NULL;

    IMG_Quit();
    SDL_Quit();
}

KButton Utils::handleEvent(/* SDL_Event *e */)
{
    KButton currentTexture = BUTTON_SPRITE_DEFAULT;
    const Uint8 *currentKeyStates = SDL_GetKeyboardState(NULL);

    if (currentKeyStates[SDL_SCANCODE_UP])
    {
        currentTexture = BUTTON_SPRITE_UP;
    }
    else if (currentKeyStates[SDL_SCANCODE_DOWN])
    {
        currentTexture = BUTTON_SPRITE_DOWN;
    }
    else if (currentKeyStates[SDL_SCANCODE_LEFT])
    {
        currentTexture = BUTTON_SPRITE_LEFT;
    }
    else if (currentKeyStates[SDL_SCANCODE_RIGHT])
    {
        currentTexture = BUTTON_SPRITE_RIGHT;
    }

    return currentTexture;
}

void Utils::update(bool &quit, SDL_Renderer* renderer)
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
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);
    gKButtons[currentSprite].render(renderer);
    SDL_RenderPresent(renderer);
}
