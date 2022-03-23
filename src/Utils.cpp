#include "include/Utils.h"
#include "include/global.h"

SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;

bool init(/* std::vector<SDL_Rect> &gButtonOnSprite */)
{
    bool success = true;
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        gWindow = SDL_CreateWindow("KMag", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL)
        {
            printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
            if (gRenderer == NULL)
            {
                printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            }
            else
            {
                SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags))
                {
                    printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                    success = false;
                }
                if (TTF_Init() == -1)
                {
                    printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
                    success = false;
                }
            }
        }
    }
    gButtonOnSprite[0] = {0, 0, 200, 300};
    gButtonOnSprite[1] = {0, 200, 200, 300};
    gButtonOnSprite[2] = {0, 400, 200, 300};
    gButtonOnSprite[3] = {0, 600, 200, 300};
    return success;
}

bool loadMedia(const std::string str, LTexture &gTexture)
{
    bool success = true;
    gFont = TTF_OpenFont(str.c_str(), 28);
    if (gFont == NULL)
    {
        printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
        success = false;
        return success;
    }

    SDL_Color textColor = {0, 0, 0};
    if (!gTexture.loadFromRenderedText("The quick brown fox jumps over the lazy dog", textColor))
    {
        printf("Failed to render text texture!\n");
        success = false;
    }
    gButtons[0].setPosition(0, 0);
    gButtons[1].setPosition(SCREEN_WIDTH - BUTTON_WIDTH, 0);
    gButtons[2].setPosition(0, SCREEN_HEIGHT - BUTTON_HEIGHT);
    gButtons[3].setPosition(SCREEN_WIDTH - BUTTON_WIDTH, SCREEN_HEIGHT - BUTTON_HEIGHT);
    return success;
}

void close()
{
    gTexture.free();

    TTF_CloseFont(gFont);
    gFont = NULL;

    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}
