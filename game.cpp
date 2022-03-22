#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
bool init();
void close();
bool loadMedia(std::string);
SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;

class LTexture
{
public:
    LTexture();
    ~LTexture();

    void free();
    // void render(int x, int y);
    int getWidth();
    int getHeight();
    bool loadFromFile(std::string);
    void setColor(Uint8 red, Uint8 green, Uint8 blue);
    void setBlendMode(SDL_BlendMode blending);
    void setAlpha(Uint8 alpha);
    void render(int x, int y);

private:
    SDL_Texture *mTexture;
    int mWidth;
    int mHeight;
} gTexture, gBackground;

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

void LTexture::free()
{
    if (mTexture != NULL)
    {
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}

int LTexture::getHeight()
{
    return mHeight;
}

int LTexture::getWidth()
{
    return mWidth;
}

void LTexture::render(int x, int y)
{
    SDL_RenderCopy(gRenderer, mTexture, NULL, NULL);
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
    SDL_Texture *gTexture = SDL_CreateTextureFromSurface(gRenderer, gSurface);
    if (gTexture == NULL)
    {
        printf("Texture could not be created! SDL Error: %s\n", SDL_GetError());
        return success;
    }
    this->mWidth = gSurface->w;
    this->mHeight = gSurface->h;
    this->mTexture = gTexture;
    SDL_FreeSurface(gSurface);
    return this->mTexture != NULL;
}

void LTexture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
    SDL_SetTextureColorMod(mTexture, red, green, blue);
}

void LTexture::setAlpha(Uint8 alpha){
    SDL_SetTextureAlphaMod( this->mTexture, alpha );
}


void LTexture::setBlendMode(SDL_BlendMode blending){
    SDL_SetTextureBlendMode(this->mTexture, blending);
}

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

    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;

    IMG_Quit();
    SDL_Quit();
}

bool loadMedia(std::vector<std::string> str)
{
    bool success = true;
    if (!gTexture.loadFromFile(str[0]))
    {
        printf("Failed to load sprite sheet texture!\n");
        success = false;
    }
    gTexture.setBlendMode(SDL_BLENDMODE_BLEND);

    if (!gBackground.loadFromFile(str[1]))
    {
        printf("Failed to load sprite sheet texture!\n");
        success = false;
    }

    return success;
}

int main(int argc, char *argv[])
{
    bool success = init();
    if (!success)
    {
        return 0;
    }
    std::vector<std::string> str({"img/fadeout.png", "img/fadein.png"});
    bool quit = true;
    // loadMedia("img/colors.png") ? quit = true : quit = false;
    loadMedia(str);
    Uint8 a = 255;
    while (quit)
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
                switch (e.key.keysym.sym)
                {
                case SDLK_w:
                    a+32 > 255 ? a = 255 : a+=32;
                    break;
                case SDLK_s:
                    a > 32 ? a-=32 : a = 0;
                    break;
                }
            }
        }
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);

        gBackground.render(0, 0);

        gTexture.setAlpha(a);
        gTexture.render(0, 0);

        SDL_RenderPresent(gRenderer);
    }

    close();
}