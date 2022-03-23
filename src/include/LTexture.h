#pragma once
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include <vector>

class LTexture
{
public:
    LTexture();
    ~LTexture();

    void free();
    int getWidth();
    int getHeight();
    bool loadFromFile(std::string);
    bool loadFromRenderedText(std::string text, SDL_Color textColor);
    void setColor(Uint8 red, Uint8 green, Uint8 blue);
    void setBlendMode(SDL_BlendMode blending);
    void setAlpha(Uint8 alpha);
    void render(int x, int y, SDL_Rect *clip = NULL, double angle = 0.0, SDL_Point *center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

private:
    SDL_Texture *mTexture;
    int mWidth;
    int mHeight;
};