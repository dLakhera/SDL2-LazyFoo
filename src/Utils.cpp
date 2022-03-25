#include "include/Utils.h"
#include "include/global.h"
#include "include/models.h"
#include "include/constants.h"
#include <iostream>

SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;
std::vector<LTexture> gKButtons;

void Utils::init()
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
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
            if (gRenderer == NULL)
            {
                printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
                throw "Init failed()!";
            }
            else
            {
                SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags))
                {
                    printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                    throw "Init failed()!";
                }
            }
        }
    }
    loadMedia();
}

void Utils::loadMedia()
{
    gKButtons.clear();
    gKButtons.resize(str.size(), LTexture());
   
    for (int i = 0; i < str.size(); i++)
    {
        gKButtons[i].loadFromFile(str[i].c_str());
    }
}

void Utils::loadMedia(const std::string str, LTexture &gTexture)
{
    gTexture.loadFromFile(str.c_str());
}

void Utils::close()
{
    gTexture.free();

    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;

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

void Utils::update(bool &quit){
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