#include "LTexture.h"

class Dot
{
public:
    static const int DOT_WIDTH = 20;
    static const int DOT_HEIGHT = 20;
    static const int DOT_VEL = 10;

    Dot(SDL_Renderer* &);

    void handleEvent(SDL_Event &e);
    void move(Uint32);
    void render(SDL_Renderer* &);
    void windowing();
    void update(Uint32 , bool&);

private:
    SDL_Texture* mTexture;
    int mPosX, mPosY;
    int mDirX, mDirY;
};