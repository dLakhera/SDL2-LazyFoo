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
    mCollider = {mPosX,mPosY, lSurface->w, lSurface->h};
    SDL_FreeSurface(lSurface);
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

void Dot::move()
{
    mPosX += mDirX * DOT_VEL;
    mPosY += mDirY * DOT_VEL;
    windowing();
}

void Dot::render(SDL_Renderer* &renderer, SDL_Rect& camera)
{
    SDL_Rect renderQuad = {mPosX-camera.x, mPosY-camera.y, DOT_WIDTH, DOT_HEIGHT};
    SDL_RenderCopy(renderer, mTexture, NULL, &renderQuad);
}

void Dot::windowing()
{
    if (mPosX + DOT_WIDTH > LEVEL_WIDTH)
    {
        mPosX = LEVEL_WIDTH - DOT_WIDTH;
    }
    else if (mPosX < 0)
    {
        mPosX = DOT_WIDTH / 2;
    }
    if (mPosY + DOT_HEIGHT > LEVEL_HEIGHT)
    {
        mPosY = LEVEL_HEIGHT - DOT_HEIGHT;
    }
    else if (mPosY < 0)
    {
        mPosY = DOT_HEIGHT / 2;
    }
}

void Dot::update(bool &quit)
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
    move();
}

bool Dot::checkCollision(SDL_Rect &wall)
{
    int topWall = wall.y;
    int bottomWall = wall.y + wall.h;
    int leftWall = wall.x;
    int rightWall = wall.x + wall.w;

    int topDot = mCollider.y;
    int bottomDot = mCollider.y + mCollider.h;
    int leftDot = mCollider.x;
    int rightDot = mCollider.x + mCollider.w;

    if (bottomWall <= topDot)
    {
        return false;
    }

    if (topWall >= bottomDot)
    {
        return false;
    }

    if (rightWall <= leftDot)
    {
        return false;
    }

    if (leftWall >= rightDot)
    {
        return false;
    }

    return true;
}

int Dot::getPosX()
{
    return mPosX;
}

int Dot::getPosY()
{
    return mPosY;
}
