#include <iostream>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <glad/glad.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool init();
void close();
bool loadMedia(std::vector<std::string>);

SDL_Window *gWindow = NULL;
SDL_Surface *gScreenSurface = NULL;
SDL_Renderer *renderer = NULL;
SDL_Surface *gCurrentSurface = NULL;
std::vector<SDL_Surface *> gRectSurface;

enum KeyPressSurfaces
{
    KEY_PRESS_UP,
    KEY_PRESS_DOWN,
    KEY_PRESS_LEFT,
    KEY_PRESS_RIGHT,
    KEY_PRESS_DEFAULT,
    KEY_PRESS_TOTAL
};

int main(int argc, char *argv[])
{
    bool success = init();
    if (!success)
    {
        exit(0);
    }
    std::vector<std::string> str;
    str.push_back("img/up.bmp");
    str.push_back("img/down.bmp");
    str.push_back("img/left.bmp");
    str.push_back("img/right.bmp");
    str.push_back("img/default.bmp");

    SDL_Rect stretchRect;
    stretchRect.x = 0;
    stretchRect.y = 0;
    stretchRect.w = SCREEN_WIDTH;
    stretchRect.h = SCREEN_HEIGHT;

    if (!loadMedia(str))
    {
        std::cout << "Could not load media!\nError: " << SDL_GetError() << std::endl;
    }
    SDL_bool done = SDL_FALSE;
    gCurrentSurface = gRectSurface[KEY_PRESS_DEFAULT];
    SDL_BlitSurface(gCurrentSurface, NULL, gScreenSurface, &stretchRect);
    while (!done)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                done = SDL_TRUE;
                break;
            case SDL_KEYDOWN:
            {
                const Uint8 *state = SDL_GetKeyboardState(NULL);
                if (state[SDL_SCANCODE_UP])
                {
                    gCurrentSurface = gRectSurface[KEY_PRESS_UP];
                    std::cout << "Up arrow key is pressed\n";
                }
                else if (state[SDL_SCANCODE_DOWN])
                {
                    gCurrentSurface = gRectSurface[KEY_PRESS_DOWN];
                    std::cout << "Down arrow key is pressed\n";
                }
                else if (state[SDL_SCANCODE_LEFT])
                {
                    gCurrentSurface = gRectSurface[KEY_PRESS_LEFT];
                    std::cout << "Left arrow key is pressed\n";
                }
                else if (state[SDL_SCANCODE_RIGHT])
                {
                    gCurrentSurface = gRectSurface[KEY_PRESS_RIGHT];
                    std::cout << "Right arrow key is pressed\n";
                }
            }
            break;
            default:
            {
                gCurrentSurface = gRectSurface[KEY_PRESS_DEFAULT];
            }
            break;
            }
            SDL_BlitScaled(gCurrentSurface, NULL, gScreenSurface, NULL);
            SDL_UpdateWindowSurface(gWindow);
        }
    }
    close();
}

bool init()
{
    bool success = true;
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Failed to initialise a window for the game\nError: " << SDL_GetError();
        success = false;
        return success;
    }

    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);
    auto Width = DM.w;
    auto Height = DM.h;

    gWindow = SDL_CreateWindow("TheInternal", (Width - SCREEN_WIDTH) / 2, (Height - SCREEN_HEIGHT) / 2, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    if (gWindow == NULL)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        success = false;
        return success;
    }
    else
    {
        int imgFlags = IMG_INIT_PNG;
        if (!(IMG_Init(imgFlags) & imgFlags))
        {
            printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
            success = false;
        }
        gScreenSurface = SDL_GetWindowSurface(gWindow);
    }
    gRectSurface.assign(KEY_PRESS_TOTAL, NULL);
    renderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    return success;
}

bool loadMedia(std::vector<std::string> str)
{
    bool success = true;
    for (int i = 0; i < str.size(); i++)
    {
        SDL_Surface *gImageSurface = SDL_LoadBMP(str[i].c_str());
        if (gImageSurface == NULL)
        {
            std::cout << "Failed to load media:" << i + 1 << " - " << str[i] << std::endl;
            success = false;
            break;
        }
        SDL_Surface *gOptimisedSurface = NULL;
        gOptimisedSurface = SDL_ConvertSurface(gImageSurface, gScreenSurface->format, 0);
        gRectSurface[i] = gOptimisedSurface;
    }
    return success;
}

void close()
{
    for (int i = 0; i < 5; i++)
    {
        SDL_FreeSurface(gRectSurface[i]);
        gRectSurface[i] = NULL;
    }

    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    SDL_Quit();
}
