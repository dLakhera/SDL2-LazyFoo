#include "include/Utils.h"
#include "include/LButton.h"
#include "include/models.h"
#include "include/constants.h"
#include <iostream>

std::vector<LTexture> gKButtons;

void Utils::init(SDL_Renderer *&renderer, SDL_Window *&window, TTF_Font *&gFont)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0 or TTF_Init() < 0)
    {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        throw "Init failed()!";
    }
    else
    {
        window = SDL_CreateWindow("KMag", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == NULL)
        {
            printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
            throw "Init failed()!";
        }
        else
        {
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if (renderer == NULL)
            {
                printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
                throw "Init failed()!";
            }
        }

        gFont = TTF_OpenFont("/Users/droidlakhera/Desktop/Projects/sdl2/kMag/res/fonts/lazy.ttf", 28);
        if (gFont == NULL)
        {
            printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
            throw "Init failed()!";
        }
    }
}

void Utils::loadMedia(SDL_Renderer *renderer, std::vector<LTexture> &kButtons)
{
    kButtons.clear();
    kButtons.resize(str.size(), LTexture());

    for (int i = 0; i < str.size(); i++)
    {
        kButtons[i].loadFromFile(str[i].c_str(), renderer);
    }
}

void Utils::loadMedia(const std::string str, LTexture *&texture, SDL_Renderer *renderer)
{
    texture->loadFromFile(str.c_str(), renderer);
}

void Utils::close(LTexture *&texture, SDL_Renderer *&renderer, SDL_Window *&window)
{
    texture->free();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = NULL;
    renderer = NULL;

    IMG_Quit();
    SDL_Quit();
}

void Utils::close(SDL_Renderer *&renderer, SDL_Window *&window)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = NULL;
    renderer = NULL;

    IMG_Quit();
    SDL_Quit();
}

KButton Utils::handleEvent(/* SDL_Event *e */)
{
    KButton currentTexture = BUTTON_SPRITE_DEFAULT;
    const Uint8 *currentKeyStates = SDL_GetKeyboardState(NULL);

    if (currentKeyStates[SDL_SCANCODE_UP])
    {
        currentTexture = BUTTON_SPRITE_UP;
    }
    else if (currentKeyStates[SDL_SCANCODE_DOWN])
    {
        currentTexture = BUTTON_SPRITE_DOWN;
    }
    else if (currentKeyStates[SDL_SCANCODE_LEFT])
    {
        currentTexture = BUTTON_SPRITE_LEFT;
    }
    else if (currentKeyStates[SDL_SCANCODE_RIGHT])
    {
        currentTexture = BUTTON_SPRITE_RIGHT;
    }

    return currentTexture;
}

void Utils::update(bool &quit, SDL_Renderer *&renderer, std::vector<LTexture> &kButtons)
{
    SDL_Event e;
    KButton currentSprite = BUTTON_SPRITE_DEFAULT;
    while (SDL_PollEvent(&e) != 0)
    {
        if (e.type == SDL_QUIT)
        {
            quit = false;
        }
    }
    currentSprite = Utils::handleEvent();
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);
    kButtons[currentSprite].render(renderer);
    SDL_RenderPresent(renderer);
}
void Utils::update(bool & quit, SDL_Renderer *& renderer, bool& renderText, std::string &inputText)
{
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0)
    {
        if (e.type == SDL_QUIT)
        {
            quit = false;
        }
        else if (e.type == SDL_KEYDOWN)
        {
            if (e.key.keysym.sym == SDLK_BACKSPACE && inputText.length() > 0)
            {
                inputText.pop_back();
                renderText = true;
            }
            else if (e.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL)
            {
                SDL_SetClipboardText(inputText.c_str());
            }
            else if (e.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL)
            {
                inputText = SDL_GetClipboardText();
                renderText = true;
            }
        }
        else if (e.type == SDL_TEXTINPUT)
        {
            if (!(SDL_GetModState() & KMOD_CTRL && (e.text.text[0] == 'c' || e.text.text[0] == 'C' || e.text.text[0] == 'v' || e.text.text[0] == 'V')))
            {
                inputText += e.text.text;
                renderText = true;
            }
        }
    }
}
