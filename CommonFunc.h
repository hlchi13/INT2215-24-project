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
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 500;

static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;
static SDL_Rect rect_screen = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

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

const SDL_Color color_text = {255, 255, 255}; //
const SDL_Color color_intro = {0, 119, 179}; // blue
const SDL_Color color_end = {244, 10, 10}; // red
const SDL_Color color_select = {245, 103, 51}; //
const SDL_Color color_exit = {255, 0, 0};

const int SHARK_NUM = 30;
const int FPS = 25;
const int AVOID_SCORE = 50;
const int INJURED_SCORE = -100;
const int KILL_SHARK_SCORE = 30;
const int GET_BONUS_SCORE_PINK = 10;
const int GET_BONUS_SCORE = 20;
const int LIFES = 5;

const int CAT_WIDTH = 64*1.5;
const int CAT_HEIGHT = 48*1.5;
const int SHARK_WIDTH = 160;
const int SHARK_HEIGHT = 92;
const int BONUS_WIDTH = 60;
const int BONUS_HEIGHT = 30;

const int CAT_SPEED = 10;
const int SHARK_SPEED1 = 10;
const int SHARK_SPEED2 = 15;
const int SHARK_SPEED3 = 25;

namespace CommonFunc
{
    SDL_Texture* LoadImage (std::string path, SDL_Renderer* ren);
	bool CheckCollision (const SDL_Rect &obj1, const SDL_Rect &obj2);
	void CleanUp();
}
#endif // COMMONFUNC_H_INCLUDED
