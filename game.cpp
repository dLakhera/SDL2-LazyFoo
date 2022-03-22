#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include <cmath>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
bool init();
void close();
SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;

class LTexture {
public:
    LTexture();
    ~LTexture();

    void free();
    void render(int x, int y);
    int getWidth();
    int getHeight();
    bool loadFromFile(std::string);

private : 
    SDL_Texture *mTexture;
    int mWidth;
    int mHeight;
};

LTexture::LTexture()
{
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
}

LTexture::~LTexture()
{
    free();
}

void LTexture::free() {
    if (mTexture != NULL)
    {
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}

int LTexture::getHeight() {
    return mHeight;
}

int LTexture::getWidth()
{
    return mWidth;
}

void LTexture::render(int x, int y)
{
    SDL_Rect renderQuad = {x, y, mWidth, mHeight};
    SDL_RenderCopy(gRenderer, mTexture, NULL, &renderQuad);
}

bool LTexture ::loadFromFile(std::string str)
{
    free();
    bool success = true;
    SDL_Surface *gSurface = IMG_Load(str.c_str());
    if (gWindow == NULL)
    {
        printf("Surface could not be created! SDL Error: %s\n", SDL_GetError());
        success = false;
        return success;
    }
    SDL_SetColorKey(gSurface, SDL_TRUE, SDL_MapRGB(gSurface->format, 0, 0xFF, 0xFF));
    SDL_Texture *gTexture = SDL_CreateTextureFromSurface(gRenderer, gSurface);
    if (gTexture == NULL)
    {
        printf("Texture could not be created! SDL Error: %s\n", SDL_GetError());
        return success;
    }
    this->mWidth = gSurface->w;
    this->mHeight = gSurface->h;
    SDL_FreeSurface(gSurface);
    this->mTexture = gTexture;
    return this->mTexture != NULL;
}

LTexture gTexture;
LTexture gBackground;

bool init()
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
            }
        }
    }

    return success;
}

void close()
{
    gTexture.free();
    gBackground.free();

    // Destroy window
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;

    // Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char *argv[])
{
    bool success = init();
    if (!success)
    {
        return 0;
    }

    bool quit = true;
    if(!gTexture.loadFromFile("img/guy.png")){
        printf("Texture could not be created! SDL Error: %s\n", SDL_GetError());
        return 0;
    }
    if (!gBackground.loadFromFile("img/bg.png"))
    {
        printf("Texture could not be created! SDL Error: %s\n", SDL_GetError());
        return 0;
    }
    while (quit)
    {
        SDL_Event e;
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quit = false;
            }
        }
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);

        gBackground.render(0, 0);
        gTexture.render(240, 190);

        SDL_RenderPresent(gRenderer);
    }

    close();
}