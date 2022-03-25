#pragma once
#include "LTexture.h"
#include "models.h"

namespace Utils{
    void init();
    void loadMedia(const std::string str, LTexture &gTexture);
    void loadMedia();
    void close();
    void update(bool &);
    KButton handleEvent();
}