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

static Mix_Music* g_music = NULL;
static Mix_Chunk* hurt = NULL;
static Mix_Chunk* intro = NULL;
static Mix_Chunk* g_over = NULL;

const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 600;
const int SCREEN_BPP = 32;
const int RENDER_DRAW_COLOR = 0xff;
const int FRAME_PER_SECOND = 25;

namespace CommonFunc
{
    SDL_Texture* LoadImage (std::string path, SDL_Renderer* ren);
	void ApplySurface(SDL_Renderer *renderer, SDL_Texture *src, int x, int y, int w, int h);
	void CleanUp();
}
#endif // COMMONFUNC_H_INCLUDED
