#pragma once
#include "LButton.h"

extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
extern TTF_Font *gFont;
extern SDL_Window *gWindow;
extern SDL_Renderer *gRenderer;
extern int WALKING_ANIMATION_FRAMES;
extern LTexture gTexture;
extern int BUTTON_WIDTH;
extern int BUTTON_HEIGHT;
extern int TOTAL_BUTTONS;
extern std::vector<LButton> gButtons;
extern std::vector<SDL_Rect> gButtonOnSprite;

extern enum LButtonSprite
{
    BUTTON_SPRITE_MOUSE_OUT,
    BUTTON_SPRITE_MOUSE_OVER_MOTION,
    BUTTON_SPRITE_MOUSE_DOWN,
    BUTTON_SPRITE_MOUSE_UP,
    BUTTON_SPRITE_TOTAL
};
