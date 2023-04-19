#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "CommonFunc.h"
#include "BaseObject.h"
#include "LTexture.h"
#include "Cat.h"
#include "Shark.h"
#include "Bonus.h"
#include "PlayerPower.h"
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
	TTF_Quit();
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
        background_ = Mix_LoadWAV("sound_background.mp3");
        intro_ = Mix_LoadWAV("sound_intro.mp3");
        injured_ = Mix_LoadWAV("sound_injured.wav");
        cat_bullet = Mix_LoadWAV("sound_meow.mp3");
        success_eat = Mix_LoadWAV("sound_eat_fish.mp3");
        if (background_ == NULL || intro_ == NULL || injured_ == NULL||cat_bullet == NULL)
        {
            cout << "Fail to load sound";
            return false;
        }
        if (TTF_Init() == -1) return false;
        g_font = TTF_OpenFont("PressStart2P.ttf", 18);
        if (g_font == NULL) {
            cout << "Fail to load font";
            return false;
        }
    }
	return true;
}

void InitIntroAndEnd(LTexture &intro, LTexture &gModulatedTexture)
{
    intro.loadFromFile("intro.png");

	gModulatedTexture.loadFromFile( "img_fish1.png" ) ;
    gModulatedTexture.setColor(0xFF,0,0);

    intro.setColor(255,255,255);
}

bool LoadBackGround(const int& num)
{
    string img_background;
    switch(num)
    {
        case 1:
            img_background = "img_bg_underwater.png";
            break;
        case 2:
            img_background = "img_bg_sky.jpg";
            break;
        case 3:
            img_background = "img_bg_universe.jpg";
            break;
        case 4:
            img_background = "img_bg_ground.jpg";
            break;
    }
    bool check_loadbg = g_background.LoadImg(img_background, g_screen);
    if (check_loadbg == false) {
        cout << "Couldn't find image\n";
        return false;
    }
    return true;
}

void CreateThreatList (vector<Shark*> &ThreatList)
{
    for (int i = 0; i < SHARK_NUM; i++) {
        ThreatList.push_back(new Shark());
        //ThreatsList[ThreatsList.size()-1]->LoadImg("sharksheet.png",g_screen);
        int shark_y = rand() % 400;
        ThreatList[i]->SetRect(SCREEN_WIDTH + 400*i, shark_y);
        ThreatList[i]->SetAnimation();
        }
}
#endif // GAME_H_INCLUDED
