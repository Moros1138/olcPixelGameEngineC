#ifndef OLC_ENGINESDL_H
#define OLC_ENGINESDL_H
#include "olc_Engine.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_image.h>

static SDL_Window*   olc_Window;
static SDL_Renderer* olc_Renderer;
static SDL_Rect rViewport;
typedef struct
{
    int id;
    SDL_Texture* t;
} texturedata;

static SDL_Texture** vTextures;
static int nActiveTexture = -1;
static int nTextureID = 0;
static int nOpenSlot = 0;



#endif