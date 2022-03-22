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
std::vector<SDL_Rect> gSprites(4);
SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;

class LTexture
{
public:
    LTexture();
    ~LTexture();

    void free();
    void render(int x, int y, SDL_Rect *rec);
    int getWidth();
    int getHeight();
    bool loadFromFile(std::string);

private:
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

void LTexture::render(int x, int y, SDL_Rect *clip)
{
    SDL_Rect renderQuad = {x, y, mWidth, mHeight};
    if (clip != NULL)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }
    SDL_RenderCopy(gRenderer, mTexture, clip, &renderQuad);
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
    this->mTexture = gTexture;
    SDL_FreeSurface(gSurface);
    return this->mTexture != NULL;
}

LTexture gTexture;

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

bool loadMedia(std::string str)
{
    bool success = true;
    if (!gTexture.loadFromFile(str))
    {
        printf("Failed to load sprite sheet texture!\n");
        success = false;
    }
    gSprites[0] = {0, 0, 100, 100};
    gSprites[1] = {0, 100, 100, 100};
    gSprites[2] = {100, 0, 100, 100};
    gSprites[3] = {100, 100, 100, 100};
    return success;
}

int main(int argc, char *argv[])
{
    bool success = init();
    if (!success)
    {
        return 0;
    }

    bool quit = true;
    loadMedia("img/dots.png") ? quit = true : quit = false;
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

        gTexture.render(0, 0, &gSprites[0]);
        gTexture.render(SCREEN_WIDTH - gSprites[1].w, 0, &gSprites[1]);
        gTexture.render(0, SCREEN_HEIGHT - gSprites[2].h, &gSprites[2]);
        gTexture.render(SCREEN_WIDTH - gSprites[3].w, SCREEN_HEIGHT - gSprites[3].h, &gSprites[3]);

        SDL_RenderPresent(gRenderer);
    }

    close();
}