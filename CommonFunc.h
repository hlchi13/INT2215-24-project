#ifndef COMMONFUNC_H_INCLUDED
#define COMMONFUNC_H_INCLUDED

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <vector>
#include <string>

#include"LTexture.h"
#include "SDL_utils.h"
using namespace std;
static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;

static SDL_Rect rect_background;
static SDL_Rect rect_screen;

const int BKGROUND_WIDTH = 1920;
const int BKGROUND_HEIGHT = 3240;

const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 600;
const int SCREEN_BPP = 32;
 // 7 la so PIXEL screen bi day xuong .
const int PIXEL = 7 ;
const int PIXEL_LIM = (2*BKGROUND_HEIGHT/3)%PIXEL ;
const int PIXEL_START = BKGROUND_HEIGHT/3 + (2*BKGROUND_HEIGHT/3)%PIXEL - PIXEL ;
const int RENDER_DRAW_COLOR = 0xff;

namespace CommonFunc
{
    SDL_Texture* LoadImage (std::string path, SDL_Renderer* ren);
	void ApplySurface(SDL_Renderer *renderer, SDL_Texture *src, int x, int y, int w, int h);
	void CleanUp();
}
#endif // COMMONFUNC_H_INCLUDED
