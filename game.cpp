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
bool loadMediaBMPasSurface(std::vector<std::string>);
bool loadMediaPNGasSurface(std::string);
bool loadPngAsTexture_(std::vector<std::string>);
SDL_Texture *loadPngAsTexture(std::string);



SDL_Window *gWindow = NULL;
// SDL_Surface *gScreenSurface = NULL;
SDL_Renderer *renderer = NULL;
SDL_Surface *gCurrentSurface = NULL;
SDL_Surface *gPNGImage = NULL;
// std::vector<SDL_Surface *> gRectSurface;
std::vector<SDL_Texture *> gRectSurface;

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
    loadPngAsTexture_(str);

    // SDL_Rect stretchRect;
    // stretchRect.x = 0;
    // stretchRect.y = 0;
    // stretchRect.w = SCREEN_WIDTH;
    // stretchRect.h = SCREEN_HEIGHT;

    // if (!loadMediaBMPasSurface(str))
    // {
    //     std::cout << "Could not load media!\nError: " << SDL_GetError() << std::endl;
    // }
    SDL_bool done = SDL_FALSE;
    // loadMediaPNGasSurface("img/loaded.png");
    SDL_Texture *gTexture = loadPngAsTexture("img/loaded.png");
    // gCurrentSurface = gTexture;
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, gTexture, NULL, NULL);

    // SDL_BlitSurface(gCurrentSurface, NULL, gScreenSurface, &stretchRect);
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
                    // gCurrentSurface = gRectSurface[KEY_PRESS_UP];
                    SDL_RenderClear(renderer);
                    SDL_RenderCopy(renderer, gRectSurface[KEY_PRESS_UP], NULL, NULL);

                    std::cout << "Up arrow key is pressed\n";
                }
                else if (state[SDL_SCANCODE_DOWN])
                {
                    // gCurrentSurface = gRectSurface[KEY_PRESS_DOWN];
                    SDL_RenderClear(renderer);
                    SDL_RenderCopy(renderer, gRectSurface[KEY_PRESS_DOWN], NULL, NULL);

                    std::cout << "Down arrow key is pressed\n";
                }
                else if (state[SDL_SCANCODE_LEFT])
                {
                    // gCurrentSurface = gRectSurface[KEY_PRESS_LEFT];
                    SDL_RenderClear(renderer);
                    SDL_RenderCopy(renderer, gRectSurface[KEY_PRESS_LEFT], NULL, NULL);

                    std::cout << "Left arrow key is pressed\n";
                }
                else if (state[SDL_SCANCODE_RIGHT])
                {
                    // gCurrentSurface = gRectSurface[KEY_PRESS_RIGHT];
                    SDL_RenderClear(renderer);
                    SDL_RenderCopy(renderer, gRectSurface[KEY_PRESS_RIGHT], NULL, NULL);

                    std::cout << "Right arrow key is pressed\n";
                }
            }
            break;
            default:
            {
                // gCurrentSurface = gRectSurface[KEY_PRESS_DEFAULT];
                // gCurrentSurface = gTexture;
                SDL_RenderClear(renderer);
                SDL_RenderCopy(renderer, gTexture, NULL, NULL);
            }
            break;
            }
            // SDL_BlitScaled(gCurrentSurface, NULL, gScreenSurface, NULL);
            // SDL_UpdateWindowSurface(gWindow);
            SDL_RenderPresent(renderer);
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
        // gScreenSurface = SDL_GetWindowSurface(gWindow);
    }
    gRectSurface.assign(KEY_PRESS_TOTAL, NULL);
    renderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
    {
        printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    }
    return success;
}

// bool loadMediaPNGasSurface(std::string str)
// {
//     bool success = true;
//     SDL_Surface *gPngImage = IMG_Load(str.c_str());
//     if (gPngImage == NULL)
//     {
//         std::cout << "Image didn\'t load\nError: " << IMG_GetError() << std::endl;
//         success = false;
//         return success;
//     }

//     gPNGImage = SDL_ConvertSurface(gPngImage, gScreenSurface->format, 0);
//     if (gPNGImage == NULL)
//     {
//         printf("Unable to optimize image %s! SDL Error: %s\n", str.c_str(), SDL_GetError());
//         success = false;
//         return success;
//     }

//     SDL_FreeSurface(gPngImage);
//     return success;
// }

// bool loadMediaBMPasSurface(std::vector<std::string> str)
// {
//     bool success = true;
//     for (int i = 0; i < str.size(); i++)
//     {
//         SDL_Surface *gImageSurface = SDL_LoadBMP(str[i].c_str());
//         if (gImageSurface == NULL)
//         {
//             std::cout << "Failed to load media:" << i + 1 << " - " << str[i] << std::endl;
//             success = false;
//             break;
//         }
//         SDL_Surface *gOptimisedSurface = NULL;
//         gOptimisedSurface = SDL_ConvertSurface(gImageSurface, gScreenSurface->format, 0);
//         gRectSurface[i] = gOptimisedSurface;
//     }
//     return success;
// }

SDL_Texture *loadPngAsTexture(std::string str)
{
    SDL_Surface *gSurface = IMG_Load(str.c_str());
    if (gSurface == NULL)
    {
        std::cout << "Failed to load surface\nError: " << SDL_GetError() << std::endl;
        return NULL;
    }

    SDL_Texture *gTexture = SDL_CreateTextureFromSurface(renderer, gSurface);
    if (gTexture == NULL)
    {
        std::cout << "Failed to load Texture\nError: " << SDL_GetError() << std::endl;
        return NULL;
    }

    return gTexture;
}

bool loadPngAsTexture_(std::vector<std::string> str)
{
    SDL_Texture *texture = NULL;
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
        texture = SDL_CreateTextureFromSurface(renderer, gImageSurface);
        // SDL_Surface *gOptimisedSurface = NULL;
        // gOptimisedSurface = SDL_ConvertSurface(gImageSurface, gScreenSurface->format, 0);
        // gRectSurface[i] = gOptimisedSurface;
        gRectSurface[i] = texture;
    }

    return success;
}

void close()
{
    for (int i = 0; i < 5; i++)
    {
        SDL_DestroyTexture(gRectSurface[i]);
        gRectSurface[i] = NULL;
    }

    SDL_DestroyWindow(gWindow);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(gWindow);
    renderer = NULL;
    gWindow = NULL;

    SDL_Quit();
}
