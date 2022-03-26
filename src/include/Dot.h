#include "LTexture.h"

class Dot
{
public:
    static const int DOT_WIDTH = 20;
    static const int DOT_HEIGHT = 20;
    static const int DOT_VEL = 10;

    Dot(SDL_Renderer* &);

    void handleEvent(SDL_Event &e);
    void move(SDL_Rect &);
    void render(SDL_Renderer* &);
    void windowing();
    void update(bool&, SDL_Rect&);
    bool checkCollision(SDL_Rect& );
private:
    SDL_Texture* mTexture;
    int mPosX, mPosY;
    int mDirX, mDirY;
    SDL_Rect mCollider;
};