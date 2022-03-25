#include "include/global.h"
#include <iostream>
TTF_Font *gFont = NULL;

LTexture::LTexture()
{
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
    mTexName = "default name";
}

LTexture::~LTexture()
{
    free();
}

void LTexture::free()
{
    if (mTexture != NULL)
    {
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}

int LTexture::getHeight()
{
    return mHeight;
}

int LTexture::getWidth()
{
    return mWidth;
}

void LTexture::render(int x, int y, SDL_Rect *clip)
{
    SDL_Rect renderQuad = {x, y, mWidth, mHeight};

    if (clip != NULL)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }
    SDL_RenderCopy(gRenderer, mTexture, clip, &renderQuad);
}

void LTexture::render()
{
    SDL_RenderCopy(gRenderer, this->mTexture, NULL, NULL);
}

bool LTexture::loadFromFile(std::string str)
{
    free();
    bool success = true;
    SDL_Surface *lSurface = IMG_Load(str.c_str());
    if (lSurface == NULL)
    {
        printf("Surface could not be created! SDL Error: %s\n", SDL_GetError());
        success = false;
        return success;
    }
    SDL_Texture *lTexture = SDL_CreateTextureFromSurface(gRenderer, lSurface);
    if (lTexture == NULL)
    {
        printf("Texture could not be created! SDL Error: %s\n", SDL_GetError());
        return success;
    }

    this->mWidth = lSurface->w;
    this->mHeight = lSurface->h;
    this->mTexName = str;
    this->mTexture = lTexture;
    SDL_FreeSurface(lSurface);
    return this->mTexture != NULL;
}

void LTexture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
    SDL_SetTextureColorMod(mTexture, red, green, blue);
}

void LTexture::setAlpha(Uint8 alpha)
{
    SDL_SetTextureAlphaMod(this->mTexture, alpha);
}

void LTexture::setBlendMode(SDL_BlendMode blending)
{
    SDL_SetTextureBlendMode(this->mTexture, blending);
}

bool LTexture::loadFromRenderedText(std::string text, SDL_Color textColor)
{
    free();
    bool success = true;
    SDL_Surface *gSurface = TTF_RenderText_Solid(gFont, text.c_str(), textColor);
    if (gSurface == NULL)
    {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
        return !success;
    }

    mTexture = SDL_CreateTextureFromSurface(gRenderer, gSurface);
    if (mTexture == NULL)
    {
        printf("Unable to render text texture! SDL_ttf Error: %s\n", TTF_GetError());
        return !success;
    }
    else
    {
        mWidth = gSurface->w;
        mHeight = gSurface->h;
    }
    SDL_FreeSurface(gSurface);
    return success;
}

void LTexture::print() {
    std::cout << mTexName << std::endl;
}