#include <chrono>
#include "SDL_utils.h"
#include"Game.h"
using namespace std;

int main(int argc, char* argv[])
{

    if (InitData() == false)
		return -1;
    srand(time(NULL));
    int frameDelay = 1000/FPS;
    Uint32 frameStart;
    int frameTime;

    GameText Tex, end_, your_score, textX, High_ScoreText, High_Score;
    rect_screen.x = 0;
    rect_screen.y = 0;
    rect_screen.w = SCREEN_WIDTH;
    rect_screen.h = SCREEN_HEIGHT;

    static LTexture gModulatedTexture(g_screen,rect_screen);

	// Show intro
    int tmp = showIntro();
    if (tmp == 2)
	{
		return 0;
	}
    if (tmp == 0)
    {
        int choose = ChooseBackGround();
        switch(choose)
        {
            case 0:
                LoadBackGround(0);
                break;
            case 1:
                LoadBackGround(1);
                break;
            case 2:
                LoadBackGround(2);
                break;
            case 3:
                LoadBackGround(3);
                break;
            case 4:
                is_quit = true;
                return 0;

        }
    }
    Mix_HaltChannel(-1);
    is_quit = false;


    // Game player
    Cat cat_obj;
    Cat cat_injured;

    vector<Shark*> ThreatsList;
    CreateThreatList(ThreatsList);

    Cat player;

    Bonus fish;

    GameText Score, number_life;

    Mix_HaltChannel(-1);
    Mix_PlayChannel( -1,background_ , 100 );
    CatLife(player, textX, number_life, g_screen);
    while(!is_quit) {

        while(SDL_PollEvent(&g_event))
        {
            switch (g_event.type) {
                case SDL_QUIT:
                    is_quit = true;
                    break;
                case SDL_KEYDOWN:
                    if (g_event.key.keysym.sym == SDLK_ESCAPE)
                    is_quit = true;
                    break;
            }
            cat_obj.HandleInputAction(g_event, g_screen, cat_bullet);
        }
        frameStart = SDL_GetTicks();
		SDL_RenderClear(g_screen);
        g_background.ShowBackground(g_screen);

        number_life.ShowNum(g_font, text_color, g_screen);
        player.Show(g_screen);
        textX.Present(g_screen);
        cat_obj.ControlBullet(g_screen);
        cat_obj.ShowAnimation(g_screen);
        cat_obj.HandleMove();
        //cat_obj.ControlBullet(g_screen);

        Score.ShowNum(g_font, text_color, g_screen);

        for(int i=0;i < SHARK_NUM;i++)
        {

            if (Score.GetValue() >= 0 && Score.GetValue() <= 500) {
                ThreatsList[i]->set_x_val(SPEED_THREAT1);
            } else if(Score.GetValue() > 500)
            {
                ThreatsList[i]->set_x_val(SPEED_THREAT2);

            }

            ThreatsList[i]->ShowSharkAnimation(g_screen);
            ThreatsList[i]->HandleMove();

            vector<Bullet*> cat_bullet_list = cat_obj.GetBulletList();

            bool check_coll = CommonFunc::CheckCollision(cat_obj.GetRect(), ThreatsList[i]->GetRect());
            if (check_coll) {
                ThreatsList[i]->Reset(SCREEN_WIDTH + 10*i);

                cat_injured.SetRect(cat_obj.GetRect().x, cat_obj.GetRect().y);
                cat_injured.ShowInjuredAnimation(g_screen);

                number_life.IncreaseValue(-1);

                Score.IncreaseValue(INJURED_SCORE);
                Mix_PlayChannel(-1, injured_, 0);
            }
        }
        std::vector<Bullet*> bullet_arr = cat_obj.GetBulletList();
		for (int r = 0; r < (int) bullet_arr.size(); r++)
		{
			Bullet* p_bullet = bullet_arr.at(r);
			if (p_bullet != NULL)
			{
				for (int t = 0; t < (int) ThreatsList.size(); t++)
				{
					Shark* obj_threat = ThreatsList.at(t);
					if (obj_threat != NULL)
					{
						SDL_Rect tRect = obj_threat->GetRect();

						SDL_Rect bRect = p_bullet->GetRect();
						bool bCol = CommonFunc::CheckCollision(bRect, tRect);

						if (bCol)
						{

							cat_obj.RemoveBullet(r);
							Score.IncreaseValue(KILL_SHARK_SCORE);
							obj_threat->Reset(SCREEN_WIDTH+20*t);

						}
					}
				}
			}
		}

		if (number_life.GetValue()<=0) is_quit= true;
		 SDL_RenderPresent(g_screen);
        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    for (int i = 0; i < (int) ThreatsList.size(); i++)
	{
		Shark* p_threat = ThreatsList.at(i);
		if (p_threat != NULL)
		{
			p_threat->Free();
			p_threat = NULL;
		}
	}
    Mix_HaltChannel(-1);

    GameText pressToEsc;
    pressToEsc.LoadText(g_font_intro, "Press ESC to quit", text_color,g_screen );
    pressToEsc.SetRect(SCREEN_WIDTH/2 - pressToEsc.GetRect().w/2, SCREEN_HEIGHT - 100);

	int i=0,times=0;
    is_quit = false ;
    gModulatedTexture.setColor(243,143,25);

    InitEnd(end_, your_score, Score, High_ScoreText, High_Score);

    Mix_PlayChannel(-1, game_over, 10);
    while(times!=3)
    {
            while (SDL_PollEvent(&g_event)!=0) {
                switch (g_event.type)
                {
                    case SDL_QUIT:
                        is_quit = true;
                        break;
                    case SDL_KEYDOWN:
                        if (g_event.key.keysym.sym==SDLK_ESCAPE) {
                            is_quit = true;
                        }
                        break;
                }

            };

            if (is_quit) break;
            i++;
            g_background.ShowBackground(g_screen);

            end_.Present(g_screen);

            your_score.Present(g_screen);
            pressToEsc.Present(g_screen);
            Score.ShowNum(g_font,text_color,g_screen) ;
            High_ScoreText.Present(g_screen);
            High_Score.ShowNum(g_font, text_color, g_screen);
            SDL_RenderPresent( g_screen );
            SDL_Delay(35);
            if(i==255)times++;
    }
	ThreatsList.clear();
    close();
    return 0;
}
