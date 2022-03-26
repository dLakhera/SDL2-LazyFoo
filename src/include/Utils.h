#pragma once
#include "LTexture.h"
#include "models.h"

namespace Utils
{
    void init(SDL_Renderer* &, SDL_Window* &);
    void loadMedia(const std::string str, LTexture* &texture, SDL_Renderer *renderer);
    void loadMedia(SDL_Renderer *renderer, std::vector<LTexture> &);
    void close(SDL_Renderer *&, SDL_Window *&);
    void close(LTexture *&, SDL_Renderer *&, SDL_Window *&);
    void update(bool &, SDL_Renderer* &, std::vector<LTexture> &);
    KButton handleEvent();
}