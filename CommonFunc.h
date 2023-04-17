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

static Mix_Music* m_background = NULL;
static Mix_Music* game_intro = NULL;
static Mix_Chunk* injured = NULL;
static Mix_Chunk* game_over = NULL;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 500;
const int SHARK_NUM = 6;

const int MAX_INJURED_TIMES = 5;

const int AVOID_SHARK_SCORE = 1;
const int INJURED_SCORE = - 200;
const int GET_BONUS_YELLOW_SCORE = 20;
const int GET_BONUS_RED_SCORE = 40;
const int GET_BONUS_BLUE_SCORE = 60;

const int SPEED_THREAT1 = 10;
const int SPEED_THREAT2 = 15;
const int SPEED_THREAT3 = 20;
const int SPEED_THREAT4 = 30;


namespace CommonFunc
{
    SDL_Texture* LoadImage (std::string path, SDL_Renderer* ren);
	void ApplySurface(SDL_Renderer *renderer, SDL_Texture *src, int x, int y, int w, int h);
	bool CheckCollision (const SDL_Rect &obj1, const SDL_Rect &obj2);
	void CleanUp();
}
#endif // COMMONFUNC_H_INCLUDED
