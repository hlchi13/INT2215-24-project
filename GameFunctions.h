#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <fstream>
#include "CommonFunc.h"
#include "BaseObject.h"
#include "LTexture.h"
#include "Cat.h"
#include "Shark.h"
#include "Bonus.h"
#include "Bullet.h"
#include "GameText.h"

BaseObject g_background;
int high_score;

bool is_quit = false;

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
        background_ = Mix_LoadWAV("sound//background.mp3");
        intro_ = Mix_LoadWAV("sound//intro.mp3");
        injured_ = Mix_LoadWAV("sound//injured.wav");
        cat_bullet = Mix_LoadWAV("sound//meow.mp3");
        success_eat = Mix_LoadWAV("sound//eat_fish.mp3");
        game_over = Mix_LoadWAV("sound//game_over.mp3");
        if (background_ == NULL || intro_ == NULL || injured_ == NULL||cat_bullet == NULL
            ||success_eat == NULL|| game_over == NULL)
        {
            cout << "Fail to load sound";
            return false;
        }
        if (TTF_Init() == -1) return false;
        g_font = TTF_OpenFont("PressStart2P.ttf", 20);
        g_font_intro = TTF_OpenFont("PressStart2P.ttf", 30);
        g_font_end = TTF_OpenFont("PressStart2P.ttf", 77);
        if (g_font == NULL) {
            cout << "Fail to load font";
            return false;
        }
    }
	return true;
}

int showIntro()
{
    SDL_Rect rect_bg_intro = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    LTexture bg_intro(g_screen, rect_bg_intro);
    bg_intro.loadFromFile("img//intro.jpg");

    SDL_Rect rect_sound = {10, 10, 20, 20};
    LTexture sound_(g_screen, rect_sound);
    sound_.loadFromFile("img//sound.png");
    sound_.setColor(243,100, 10);

    Mix_PlayChannel( -1,intro_ , 100 );

    const int text_n = 3;
    GameText intro_t[text_n];
    string text[text_n] = {"Play", "How To Play", "Exit" };
    SDL_Color colorIntro[2] = { {243, 156, 18}, {255, 0, 0} };
    SDL_Rect rect_intro[text_n];
    bool selected[text_n] = {0, 0, 0};
    for (int i = 0; i < text_n; i++) {
        intro_t[i].LoadText(g_font_intro, text[i], colorIntro[0], g_screen);
        intro_t[i].SetRect(200, 150 + 70*i);
        rect_intro[i] = intro_t[i].GetRect();
    }

	int x, y;
	while (!is_quit)
	{
		while (SDL_PollEvent(&g_event))
		{
			switch (g_event.type)
			{
                case SDL_QUIT:
                {
                    is_quit = true;
                    return 2;
                }
                case SDL_MOUSEMOTION:
                    x = g_event.motion.x;
                    y = g_event.motion.y;
                    for (int i = 0; i < text_n; i++)
                    {
                        if (x >= rect_intro[i].x && x <= rect_intro[i].x + rect_intro[i].w
                            && y >= rect_intro[i].y && y <= rect_intro[i].y + rect_intro[i].h)
                        {
                            if (!selected[i])
                            {
                                Mix_PlayChannel(-1, cat_bullet, 0);
                                selected[i] = 1;
                                intro_t[i].LoadText(g_font_intro, text[i], colorIntro[1], g_screen);
                            }
                        }
                        else
                        {
                            if (selected[i])
                            {
                                selected[i] = 0;
                                intro_t[i].LoadText(g_font_intro, text[i], colorIntro[0], g_screen);
                            }
                        }
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    x = g_event.button.x;
                    y = g_event.button.y;
                    for (int i = 0; i < text_n; i++)
                    {
                        if (x >= rect_intro[i].x && x <= rect_intro[i].x + rect_intro[i].w
                            && y >= rect_intro[i].y && y <= rect_intro[i].y + rect_intro[i].h)
                        {
                            return i;
                        }
                    }
                    break;
                case SDL_KEYDOWN:
                    if (g_event.key.keysym.sym == SDLK_ESCAPE)
                    {
                        return 2;
                    }
                default:
                {
                    break;
                }
            }
        }
        SDL_RenderClear(g_screen);

		bg_intro.renderCopy();
		sound_.renderCopy();

		for (int i = 0; i < text_n; i++)
		{
            intro_t[i].Present(g_screen);
		}
		SDL_RenderPresent(g_screen);
	}

	return 2;
}

int ChooseBackGround()
{
    bool running = true;
    SDL_Rect rect_bg_choose = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    LTexture choose(g_screen, rect_bg_choose);
    choose.loadFromFile("img//intro.jpg");

    SDL_Rect rect_sound = {10, 10, 20, 20};
    LTexture sound_(g_screen, rect_sound);
    sound_.loadFromFile("img//sound.png");
    sound_.setColor(243,100, 10);

    GameText choose_bg[5];
    int x, y;
    SDL_Color select = {255, 0, 0};
    string text[5] = {"Underwater", "Sky", "Universe", "Ground", "Exit"};
    SDL_Rect rect_choose[5];

    bool selected[5] = {0, 0, 0, 0 ,0};
    for (int i = 0; i < 5; i++) {

        choose_bg[i].LoadText(g_font, text[i], text_intro, g_screen );
        choose_bg[i].SetRect(100, 10+i*50);
        rect_choose[i] = choose_bg[i].GetRect();
        //TTF_SizeText(g_font, text[i].c_str(), &rect_text[i].w, &rect_text[i].h);

        cout << rect_choose[i].w << " " << rect_choose[i].h <<endl;
    }


    while(running)
    {
        while(SDL_PollEvent(&g_event))
        {
            switch(g_event.type)
            {
                case SDL_QUIT:
                    running = false;
                    return 4;
                case SDL_KEYDOWN:
                    if (g_event.key.keysym.sym == SDLK_ESCAPE)
                    {
                        running = false;
                    }
                    return 4;
                case SDL_MOUSEMOTION:
                    x = g_event.motion.x;
                    y = g_event.motion.y;
                    for (int i = 0; i < 5; i++)
                    {
                        if (x >=rect_choose[i].x && x <= rect_choose[i].x+rect_choose[i].w
                            && y >= rect_choose[i].y && y <= rect_choose[i].y+rect_choose[i].h)
                        {
                            if (!selected[i])
                            {
                                Mix_PlayChannel(-1, cat_bullet, 0);

                                selected[i] = 1;
                                choose_bg[i].LoadText(g_font, text[i], select, g_screen);
                            }
                        }
                        else
                        {
                            if (selected[i])
                            {
                                selected[i] = 0;
                                choose_bg[i].LoadText(g_font, text[i], text_intro, g_screen);
                            }
                        }
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    x = g_event.motion.x;
                    y = g_event.motion.y;
                    for (int i = 0; i < 5; i++)
                    {
                        if (x >=rect_choose[i].x && x <= rect_choose[i].x+rect_choose[i].w
                            && y >= rect_choose[i].y && y <= rect_choose[i].y+rect_choose[i].h)
                        {
                            return i;
                        }
                    }
            }
        }

        SDL_RenderClear(g_screen);
        choose.renderCopy();
        sound_.renderCopy();
        for (int i = 0; i < 5; i++) {
            choose_bg[i].Present(g_screen);
        }
        SDL_RenderPresent(g_screen);

    }
    return 4;
}

bool LoadBackGround(const int& num)
{
    string img_background;
    switch(num)
    {
        case 0:
            img_background = "img//bg_underwater.png";
            break;
        case 1:
            img_background = "img//bg_sky.jpg";
            break;
        case 2:
            img_background = "img//bg_universe.jpg";
            break;
        case 3:
            img_background = "img//bg_ground.jpg";
            break;
    }
    bool check_loadbg = g_background.LoadImg(img_background, g_screen);
    if (check_loadbg == false) {
        cout << "Couldn't find image\n";
        return false;
    }
    return true;
}

void getHighScore(GameText &High_Score, GameText &Score)
{
    ifstream read("HighScore.txt");// mo file HighScore de doc
    read >> high_score; // doc so trong file
    read.close(); // dong file
    if (Score.GetValue() > high_score) // neu score moi lon hon score cu duoc ghi trong file
    {
        high_score = Score.GetValue();// thi gan score trong file bang score moi
        ofstream file("HighScore.txt"); // mo file de ghi
        file << Score.GetValue(); // ghi lai score moi
        file.close();
    }
    High_Score.SetValue(high_score);// gan high score cho gametext
}

void InitEnd(GameText &end_, GameText &Your_Score, GameText &Score, GameText &High_ScoreText, GameText &High_Score)
{
    end_.LoadText(g_font_end, "GAME OVER", text_end, g_screen);
    end_.SetRect(SCREEN_WIDTH/2 - end_.GetRect().w/2 ,SCREEN_HEIGHT/2-end_.GetRect().h);

    Your_Score.LoadText(g_font, "SCORE: ", text_color, g_screen);
    Your_Score.SetRect(SCREEN_WIDTH/2-Your_Score.GetRect().w, end_.GetRect().y+ end_.GetRect().h+ 10);

    Score.SetRect(Your_Score.GetRect().x+Your_Score.GetRect().w+20, Your_Score.GetRect().y);

    High_ScoreText.LoadText(g_font, "HIGH SCORE: ", text_color, g_screen);
    High_ScoreText.SetRect(SCREEN_WIDTH/2-High_ScoreText.GetRect().w, Score.GetRect().y+Score.GetRect().h + 10);

    getHighScore(High_Score, Score);
    High_Score.SetRect(High_ScoreText.GetRect().x + High_ScoreText.GetRect().w + 20, Score.GetRect().y+Score.GetRect().h + 10);
}

void ShowEnd(GameText &end_, GameText &Your_Score, GameText &Score, GameText &High_ScoreText, GameText &High_Score)
{
    end_.Present(g_screen);
    Your_Score.Present(g_screen);
    Score.ShowNum(g_font,text_color,g_screen) ;
    High_ScoreText.Present(g_screen);
    High_Score.ShowNum(g_font, text_color, g_screen);
}


void InitLife(Cat &life, GameText &textX, GameText &number_life)
{
    life.LoadImg("img//heart.png", g_screen);
    life.SetWidth(40, 25);
    life.SetRect(SCREEN_WIDTH/2 - life.GetRect().w, 0);

    textX.LoadText(g_font, "x", text_color, g_screen);
    textX.SetRect(SCREEN_WIDTH/2 - life.GetRect().w + 50, life.GetRect().h/2-textX.GetRect().h/2);

    number_life.SetValue(LIFES);
    number_life.SetRect(SCREEN_WIDTH/2 - life.GetRect().w+50+life.GetRect().w, life.GetRect().h/2-textX.GetRect().h/2);
}

void ShowLife(Cat &heart, GameText &textX, GameText &number_life)
{
    number_life.ShowNum(g_font, text_color, g_screen);
    heart.Show(g_screen);
    textX.Present(g_screen);
}
void CreateThreatList (vector<Shark*> &ThreatList)
{
    for (int i = 0; i < SHARK_NUM; i++) {
        ThreatList.push_back(new Shark());

        int shark_y = rand() % 400;
        ThreatList[i]->SetRect(SCREEN_WIDTH + 400*i, shark_y);
        ThreatList[i]->SetAnimation();
        }
}

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

#endif // GAME_H_INCLUDED
