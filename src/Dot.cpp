#include "include/Dot.h"
#include "include/constants.h"
#include <iostream>

Dot::Dot(SDL_Renderer* &renderer)
{
    SDL_Surface *lSurface = SDL_LoadBMP(dotBMPFilePath.c_str());
    if (lSurface == NULL)
        throw "Failed to load BMP Image as Surface!";

    SDL_SetColorKey(lSurface, SDL_TRUE, SDL_MapRGB(lSurface->format, 0xFF, 0xFF, 0xFF));
    mTexture = SDL_CreateTextureFromSurface(renderer, lSurface);
    if (mTexture == NULL)
    {
        std::cout << SDL_GetError() << std::endl;
        throw "Failed to load BMP Image as Texture!";
    }
    mPosX = DOT_WIDTH / 2;
    mPosY = DOT_HEIGHT / 2;
}

void Dot::handleEvent(SDL_Event &e)
{
    const Uint8 *currentKeyStates = SDL_GetKeyboardState(NULL);
    mDirY = 0, mDirX = 0;

    if (currentKeyStates[SDL_SCANCODE_UP])
    {
        mDirY = -1;
    }
    else if (currentKeyStates[SDL_SCANCODE_DOWN])
    {
        mDirY = 1;
    }

    if (currentKeyStates[SDL_SCANCODE_LEFT])
    {
        mDirX = -1;
    }
    else if (currentKeyStates[SDL_SCANCODE_RIGHT])
    {
        mDirX = 1;
    }
}

void Dot::move(Uint32 lastFrameTicks)
{
    mPosX += mDirX * DOT_VEL * (SDL_GetTicks() - lastFrameTicks);
    mPosY += mDirY * DOT_VEL * (SDL_GetTicks() - lastFrameTicks);
    windowing();
    lastFrameTicks = SDL_GetTicks();
}

void Dot::render(SDL_Renderer* &renderer)
{
    SDL_Rect renderQuad = {mPosX, mPosY, DOT_WIDTH, DOT_HEIGHT};
    SDL_RenderCopy(renderer, mTexture, NULL, &renderQuad);
}

void Dot::windowing()
{
    if (mPosX > SCREEN_WIDTH)
    {
        mPosX = SCREEN_WIDTH - DOT_WIDTH / 2;
    }
    else if (mPosX < 0)
    {
        mPosX = DOT_WIDTH / 2;
    }
    if (mPosY > SCREEN_HEIGHT)
    {
        mPosY = SCREEN_HEIGHT - DOT_HEIGHT / 2;
    }
    else if (mPosY < 0)
    {
        mPosY = DOT_HEIGHT / 2;
    }
}

void Dot::update(Uint32 lastFrameTicks, bool &quit)
{
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0)
    {
        if (e.type == SDL_QUIT)
        {
            quit = false;
        }
    }
    handleEvent(e);
    move(lastFrameTicks);
}
