#include "include/global.h"

LTexture::LTexture()
{
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
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

void LTexture::render(int x, int y, SDL_Rect *clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
    SDL_Rect renderQuad = {x, y, mWidth, mHeight};
    if (clip != NULL)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }
    SDL_RenderCopyEx(gRenderer, mTexture, clip, &renderQuad, angle, center, flip);
}

bool LTexture::loadFromFile(std::string str)
{
    free();
    bool success = true;
    SDL_Surface *gSurface = IMG_Load(str.c_str());
    if (gWindow == NULL)
    {
        printf("Surface could not be created! SDL Error: %s\n", SDL_GetError());
        success = false;
        return success;
    }
    SDL_SetColorKey(gSurface, SDL_TRUE, SDL_MapRGB(gSurface->format, 0, 0xFF, 0xFF));
    SDL_Texture *gTexture = SDL_CreateTextureFromSurface(gRenderer, gSurface);
    if (gTexture == NULL)
    {
        printf("Texture could not be created! SDL Error: %s\n", SDL_GetError());
        return success;
    }
    this->mWidth = gSurface->w;
    this->mHeight = gSurface->h;
    this->mTexture = gTexture;
    SDL_FreeSurface(gSurface);
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