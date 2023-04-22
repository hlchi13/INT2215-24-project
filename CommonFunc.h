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
static SDL_Rect rect_screen;

static Mix_Chunk* background_ = NULL;
static Mix_Chunk* intro_ = NULL;
static Mix_Chunk* injured_ = NULL;
static Mix_Chunk* success_eat = NULL;
static Mix_Chunk* cat_bullet = NULL;
static Mix_Chunk* game_over = NULL;

static TTF_Font* g_font = NULL;
static TTF_Font* g_font_intro = NULL;
static TTF_Font* g_font_end = NULL;

const SDL_Color text_color = {243, 143, 10};// orange
const SDL_Color text_intro = {50, 50, 200}; // blue
const SDL_Color text_end = {244, 10, 10};

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 500;
const int SHARK_NUM = 30;
const int FPS = 20;

const int AVOID_SHARK_SCORE = 1;
const int INJURED_SCORE = - 200;
const int KILL_SHARK_SCORE = 100;
const int GET_BONUS_YELLOW_SCORE = 20;
const int GET_BONUS_RED_SCORE = 40;
const int GET_BONUS_BLUE_SCORE = 60;

const int LIFES = 5;
const int MAX_INJURED = LIFES;

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
