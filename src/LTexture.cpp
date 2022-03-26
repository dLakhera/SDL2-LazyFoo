#include "include/global.h"
#include <iostream>

TTF_Font* gFont = NULL;
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

void LTexture::render(int x, int y, SDL_Rect *clip, SDL_Renderer* renderer)
{
    SDL_Rect renderQuad = {x, y, mWidth, mHeight};

    if (clip != NULL)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }
    SDL_RenderCopy(renderer, mTexture, clip, &renderQuad);
}

void LTexture::render(SDL_Renderer* renderer)
{
    SDL_RenderCopy(renderer, this->mTexture, NULL, NULL);
}

void LTexture::loadFromFile(std::string str, SDL_Renderer* renderer)
{
    free();
    
    SDL_Surface *lSurface = IMG_Load(str.c_str());
    if (lSurface == NULL)
    {
        printf("Surface could not be created! SDL Error: %s\n", SDL_GetError());
        throw "LTexture::loadFromFile surface loading failed!";
    }
    SDL_Texture *lTexture = SDL_CreateTextureFromSurface(renderer, lSurface);
    if (lTexture == NULL)
    {
        printf("Texture could not be created! SDL Error: %s\n", SDL_GetError());
        throw "LTexture::loadFromFile texture loading failed!";
    }

    this->mWidth = lSurface->w;
    this->mHeight = lSurface->h;
    this->mTexName = str;
    this->mTexture = lTexture;
    SDL_FreeSurface(lSurface);
    if(mTexture  == NULL) {
        throw "LTexture::loadFromFile mTexture updation failed!";
    }
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

void LTexture::loadFromRenderedText(std::string text, SDL_Color textColor, SDL_Renderer *renderer)
{
    free();
    SDL_Surface *gSurface = TTF_RenderText_Solid(gFont, text.c_str(), textColor);
    if (gSurface == NULL)
    {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
        throw "LTexture::loadFromRenderedText font loading failed!";
    }

    mTexture = SDL_CreateTextureFromSurface(renderer, gSurface);
    if (mTexture == NULL)
    {
        printf("Unable to render text texture! SDL_ttf Error: %s\n", TTF_GetError());
        throw "LTexture::loadFromRenderedText texture loading failed!";
    }
    else
    {
        mWidth = gSurface->w;
        mHeight = gSurface->h;
    }
    SDL_FreeSurface(gSurface);
}

void LTexture::print() {
    std::cout << mTexName << std::endl;
}