#include "include/Utils.h"
#include "include/global.h"
#include "include/models.h"
#include <iostream>

SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;
std::vector<LTexture> gKButtons;

bool Utils::init()
{
    bool success = true;
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        gWindow = SDL_CreateWindow("KMag", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL)
        {
            printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
            if (gRenderer == NULL)
            {
                printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            }
            else
            {
                SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags))
                {
                    printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                    success = false;
                }
            }
        }
    }
    gButtonOnSprite.resize(4);
    gButtonOnSprite[0] = {0, 0, 200, 300};
    gButtonOnSprite[1] = {0, 200, 200, 300};
    gButtonOnSprite[2] = {0, 400, 200, 300};
    gButtonOnSprite[3] = {0, 600, 200, 300};
    return success;
}

bool Utils::loadMedia(std::vector<std::string> &str)
{
    gKButtons.clear();
    gKButtons.resize(str.size(), LTexture());
    bool success = true;
   
    for (int i = 0; i < str.size(); i++)
    {
        if (!gKButtons[i].loadFromFile(str[i]))
        {
            printf("Failed to render text texture!\n");
            success = false;
        }
    }
    return success;
}

bool Utils::loadMedia(const std::string str, LTexture &gTexture)
{
    bool success = true;
    if (!gTexture.loadFromFile(str.c_str()))
    {
        printf("Failed to render text texture!\n");
        success = false;
    }
    gButtons[0].setPosition(0, 0);
    gButtons[1].setPosition(SCREEN_WIDTH - BUTTON_WIDTH, 0);
    gButtons[2].setPosition(0, SCREEN_HEIGHT - BUTTON_HEIGHT);
    gButtons[3].setPosition(SCREEN_WIDTH - BUTTON_WIDTH, SCREEN_HEIGHT - BUTTON_HEIGHT);
    return success;
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