#include "include/LTexture.h"
#include "include/global.h"
#include "include/Utils.h"
#include "include/models.h"
#include "include/constants.h"
#include <iostream>
#include <exception>

std::vector<SDL_Rect> gButtonOnSprite;
std::vector<LButton> gButtons;

LTexture gTexture;

int main(int argc, char *argv[])
{
    try
    {
        Utils::init();
        bool quit = true;
        while (quit)
        {
            Utils::update(quit);
        }
    } catch(const char* e) {
        std::cout << "Exiting due to exception:\n\t" << e << std::endl;
    }
    Utils::close();
}
