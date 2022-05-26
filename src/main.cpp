#include "include/LTexture.h"
#include "include/Utils.h"
#include "include/models.h"
#include "include/constants.h"
#include "include/Dot.h"
#include <iostream>
#include <exception>

void handleCamera(SDL_Rect &, Dot &);

int main(int argc, char *argv[])
{
    SDL_Renderer *renderer = NULL;
    SDL_Window *window = NULL;
    TTF_Font *gFont = NULL;
    try
    {
        bool quit = true;

        Utils::init(renderer, window, gFont);
        SDL_StartTextInput();

        LTexture gBGTexture;
        LTexture gInputTextTexture;
        LTexture gPromptText;

        SDL_Color color = {0, 0, 0, 0xFF};
        std::string inputText = "Some Text";

        gBGTexture.loadFromFile("/Users/droidlakhera/Desktop/Projects/sdl2/kMag/res/img/mario-bg.png", renderer);
        gInputTextTexture.loadFromRenderedText(inputText, color, renderer, gFont);
        gPromptText.loadFromRenderedText("Enter Text: ", color, renderer, gFont);
        while (quit)
        {
            bool renderText = false;
            SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
            SDL_RenderClear(renderer);
            gBGTexture.render(0, 0, NULL, renderer);
            Utils::update(quit, renderer, renderText, inputText);
            if (renderText)
            {
                if (inputText != "")
                {
                    gInputTextTexture.loadFromRenderedText(inputText.c_str(), color, renderer, gFont);
                }
                else
                {
                    gInputTextTexture.loadFromRenderedText(" ", color, renderer, gFont);
                }
            }
            gPromptText.render((SCREEN_WIDTH - gPromptText.getWidth()) / 2, 0, NULL, renderer);
            gInputTextTexture.render((SCREEN_WIDTH - gInputTextTexture.getWidth()) / 2, gPromptText.getHeight(), NULL, renderer);
            SDL_RenderPresent(renderer);
        }
        SDL_StopTextInput();
    }
    catch (const char *e)
    {
        std::cout << "Exiting due to exception:\n\t" << e << std::endl;
    }
    Utils::close(renderer, window);
}
