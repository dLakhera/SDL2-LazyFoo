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
    void loadFromFile(std::string, SDL_Renderer* renderer);
    void loadFromRenderedText(std::string text, SDL_Color textColor, SDL_Renderer* &renderer, TTF_Font* &font);
    void setColor(Uint8 red, Uint8 green, Uint8 blue);
    void setBlendMode(SDL_BlendMode blending);
    void setAlpha(Uint8 alpha);
    void render(int x, int y, SDL_Rect *clip = NULL, SDL_Renderer *renderer = NULL);
    void render(SDL_Renderer *);
    void print();
    
private:
    SDL_Texture *mTexture;
    std::string mTexName;
    int mWidth;
    int mHeight;
};