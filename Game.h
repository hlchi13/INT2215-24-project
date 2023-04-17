#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "CommonFunc.h"
#include "BaseObject.h"
#include "LTexture.h"
#include "Cat.h"
#include "Shark.h"
#include "Bonus.h"
BaseObject g_background;

void close()
{
	g_background.Free();

	SDL_DestroyRenderer(g_screen);
	g_screen = NULL;

	SDL_DestroyWindow(g_window);
	g_window = NULL;

	Mix_CloseAudio();
	IMG_Quit();
	SDL_Quit();
}

bool InitData()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) return false;
	g_window = SDL_CreateWindow("Cat and Shark", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
								SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (g_window == NULL)
	{
		return false;
	}
    g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
    if (g_screen == NULL) return false;
    else
    {
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
        SDL_RenderSetLogicalSize(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);
        int imgFlags = IMG_INIT_PNG;
        if (!(IMG_Init(imgFlags) && imgFlags))
            return false;
        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048)== -1)
        {
            return false;
        }
        m_background = Mix_LoadMUS("game_background.mp3");
        game_intro = Mix_LoadMUS("game_intro.mp3");

    }
	return true;
}

bool LoadBackGround()
{
	bool ret = g_background.LoadImg("background.png", g_screen);
	if (ret == false)
		return false;
	return true;
}

#endif // GAME_H_INCLUDED
