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
	bool success = true;
	int ret = SDL_Init(SDL_INIT_EVERYTHING);
	if (ret < 0) return false;

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	g_window = SDL_CreateWindow("Cat and Shark", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
								SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (g_window == NULL)
	{
		success = false;
	}
	else
	{
		g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
		if (g_screen == NULL) success = false;
		else
		{
			SDL_RenderSetLogicalSize(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) && imgFlags))
				success = false;
            if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048)== -1)
            {
                success = false;
            }
            m_background = Mix_LoadMUS("game_background.mp3");
            game_intro = Mix_LoadMUS("game_intro.mp3");
		}
	}
	return success;
}

bool LoadBackGround()
{
	bool ret = g_background.LoadImg("background.png", g_screen);
	if (ret == false)
		return false;
	return true;
}

/**void CreateAndInitAndPutThreatInList(vector<Shark*> &ThreatsList)
{
    srand(time(NULL));
    for (int i = 0; i < SHARK_NUM; i++) {
        ThreatsList.push_back(new Shark);
        //ThreatsList[ThreatsList.size()-1]->LoadImg("sharksheet.png",g_screen);
        ThreatsList[ThreatsList.size()-1]->SetAnimation();
        int shark_y = rand() % SCREEN_HEIGHT;
        ThreatsList[ThreatsList.size()-1]->SetRect(SCREEN_WIDTH *(ThreatsList.size()+1), shark_y);
        }
}

void ShowThreatsList(vector<Shark*> ThreatsList, SDL_Rect cat_rect)
{
    for(int i=0;i<SHARK_NUM;i++)
    {
        ThreatsList[i]-> set_x_val(10);
        ThreatsList[i]->ShowSharkAnimation(g_screen);
        if (CommonFunc::CheckCollision(cat_rect, ThreatsList[i]->GetRect())) {
            cout << "YES";
        }
        ThreatsList[i]->HandleMove();
        SDL_Delay(10);
    }
}*/
#endif // GAME_H_INCLUDED
