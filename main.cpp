#include <chrono>
#include "SDL_utils.h"
#include"Game.h"
using namespace std;

int score = 0;
int main(int argc, char* argv[])
{

    int num_bg = 2;
    if (InitData() == false)
		return -1;
	if (LoadBackGround(num_bg) == false)
		return -1;

    bool is_quit = false;

    srand(time(NULL));
    int frameDelay = 1000/FPS;
    Uint32 frameStart;
    int frameTime;

    rect_screen.x = 0;
    rect_screen.y = 0;
    rect_screen.w = SCREEN_WIDTH;
    rect_screen.h = SCREEN_HEIGHT;

    static SDL_Rect rectPress { rectPress.x = 10 ,  rectPress.y = 200 ,   rectPress.w = 458 , rectPress.h = 88  }  ;
    static LTexture gModulatedTexture(g_screen,rect_screen), intro(g_screen,rect_screen) ;
    InitIntroAndEnd(intro, gModulatedTexture);

	// Show intro
    int iii = 0;
    Mix_PlayChannel( -1,intro_ , 100 );
    while(!is_quit)
    {
            while (SDL_PollEvent(&g_event)!=0) {
                if (g_event.key.keysym.sym == SDLK_s) {
                    is_quit = true;
                }
            };
            if (is_quit) break;
            iii++;
            SDL_RenderClear(g_screen);
            intro.setAlpha(iii); intro.renderCopy();
            SDL_RenderPresent( g_screen );
            SDL_Delay(45);
            if(iii>=255) break;
    }

     while(!is_quit)
    {
            while (SDL_PollEvent(&g_event)!=0) {
                if (g_event.key.keysym.sym == SDLK_s) {
                    is_quit = true;
                    break;
                }
            }
            if (is_quit) break;
            intro.renderCopy();
            SDL_RenderPresent( g_screen );
            SDL_Delay(25);
    }
    Mix_HaltChannel(-1);
    is_quit = false;
    Mix_PlayChannel( -1,background_ , 100 );

    // Game player
    Cat cat_obj;
    Cat cat_injured;

    vector<Shark*> ThreatsList;
    CreateThreatList(ThreatsList);

    PlayerPower player;
    player.Init(g_screen);

    Bonus fish;

    while(!is_quit) {

        while(SDL_PollEvent(&g_event))
        {
            switch (g_event.type) {
                case SDL_QUIT:
                    is_quit = true;
                    break;
                case SDL_KEYDOWN:
                    if (g_event.key.keysym.sym == SDLK_ESCAPE)
                    break;
            }
            cat_obj.HandleInputAction(g_event, g_screen, cat_bullet);
        }
        frameStart = SDL_GetTicks();
		SDL_RenderClear(g_screen);
        g_background.ShowBackground(g_screen);

        player.Show(g_screen);

        cat_obj.ControlBullet(g_screen);
        cat_obj.ShowAnimation(g_screen);
        cat_obj.HandleMove();
        //cat_obj.ControlBullet(g_screen);

        fish.ShowBonus(g_screen);
        fish.HandleMove();

        for(int i=0;i < SHARK_NUM;i++)
        {

            ThreatsList[i]-> set_x_val(10);
            ThreatsList[i]->ShowSharkAnimation(g_screen);
            ThreatsList[i]->HandleMove();

            vector<Bullet*> cat_bullet_list = cat_obj.GetBulletList();

            bool check_coll = CommonFunc::CheckCollision(cat_obj.GetRect(), ThreatsList[i]->GetRect());
            if (check_coll) {

                cat_injured.SetRect(cat_obj.GetRect().x, cat_obj.GetRect().y);
                cat_injured.SetShownInjured(true);
                player.Decrease();
                //Mix_PlayChannel(-1, injured_, 10);
                //ThreatsList.erase(ThreatsList.begin()+i);
            } else
            {
                cat_injured.SetShownInjured(false);
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
							obj_threat->Reset(SCREEN_WIDTH);

						}
					}
				}
			}
		}
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
	ThreatsList.clear();
    close();
    return 0;
}
