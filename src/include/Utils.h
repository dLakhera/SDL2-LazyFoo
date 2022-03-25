#pragma once
#include "LTexture.h"
#include "models.h"

namespace Utils{
    bool init();
    bool loadMedia(const std::string str, LTexture &gTexture);
    bool loadMedia(std::vector<std::string> &str);
    void close();
    KButton handleEvent();
}