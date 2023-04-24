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
using namespace std;
static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;
static SDL_Rect rect_screen;

static Mix_Music* background_ = NULL;
static Mix_Music* intro_ = NULL;
static Mix_Chunk* selected_ = NULL;
static Mix_Chunk* injured_ = NULL;
static Mix_Chunk* success_eat = NULL;
static Mix_Chunk* cat_bullet = NULL;
static Mix_Chunk* s_game_over = NULL;

static TTF_Font* g_font = NULL;
static TTF_Font* g_font_intro = NULL;
static TTF_Font* g_font_end = NULL;
static TTF_Font* g_font_choose = NULL;

const SDL_Color color_text = {242, 226, 224};
const SDL_Color color_intro = {0, 119, 179};
const SDL_Color color_end = {244, 10, 10};
const SDL_Color color_select = {192, 66, 138};
const SDL_Color color_exit = {255, 0, 0};

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 500;
const int SHARK_NUM = 30;
const int FPS = 20;

const int INJURED_SCORE = - 150;
const int KILL_SHARK_SCORE = 100;
const int GET_BONUS_YELLOW_SCORE = 20;
const int GET_BONUS_RED_SCORE = 40;
const int GET_BONUS_BLUE_SCORE = 60;

const int LIFES = 3;
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
