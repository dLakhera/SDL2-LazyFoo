#pragma once
#include "LTexture.h"
#include "models.h"

namespace Utils
{
    void init(SDL_Renderer* &);
    void loadMedia(const std::string str, LTexture &gTexture, SDL_Renderer *renderer);
    void loadMedia(SDL_Renderer *renderer);
    void close(SDL_Renderer *);
    void update(bool &, SDL_Renderer* );
    KButton handleEvent();
}