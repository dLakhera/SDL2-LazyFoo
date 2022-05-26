#include "LTexture.h"

class Dot
{
public:
    static const int DOT_WIDTH = 20;
    static const int DOT_HEIGHT = 20;
    static const int DOT_VEL = 10;

    Dot(SDL_Renderer* &);

    void handleEvent(SDL_Event &e);
    void move();
    void render(SDL_Renderer *&);
    void render(SDL_Renderer *&, SDL_Rect& camera);
    void windowing();
    void update(bool&);
    bool checkCollision(SDL_Rect& );
    int getPosX();
    int getPosY();
private:
    SDL_Texture* mTexture;
    int mPosX, mPosY;
    int mDirX, mDirY;
    SDL_Rect mCollider;
};