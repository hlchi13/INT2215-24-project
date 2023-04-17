#include <iostream>
#include "SDL_utils.h"
#include"Game.h"
using namespace std;

int score = 0;
int main(int argc, char* argv[])
{

    if (InitData() == false)
		return -1;
	if (LoadBackGround() == false)
		return -1;

    bool is_quit = true;

    srand(time(NULL));
    // main player
    Cat cat_obj;
    Cat cat_injured;

    Bonus fish;

    vector<Shark*> ThreatsList;
    srand(time(NULL));
    for (int i = 0; i < SHARK_NUM; i++) {
        ThreatsList.push_back(new Shark());
        //ThreatsList[ThreatsList.size()-1]->LoadImg("sharksheet.png",g_screen);
        int shark_y = rand() % 400;
        ThreatsList[i]->SetRect(SCREEN_WIDTH + 400*i, shark_y);
        ThreatsList[i]->SetAnimation();
        }

    while(is_quit) {

        while(SDL_PollEvent(&g_event))
        {
            switch (g_event.type) {
                case SDL_QUIT:
                    is_quit = false;
                    break;
                case SDL_KEYDOWN:
                    if (g_event.key.keysym.sym == SDLK_ESCAPE) {
                        is_quit = false;
                    } else if (g_event.key.keysym.sym == SDLK_SPACE)
                    {
                        if (!Mix_PlayingMusic()) {
                            Mix_PlayMusic(m_background, 0);
                        }
                    }
                    break;
            }
            cat_obj.HandleInputAction(g_event);
        }
		SDL_RenderClear(g_screen);
        g_background.ShowBackground(g_screen);

        cat_obj.ShowAnimation(g_screen);
        cat_obj.HandleMove();

        fish.ShowBonus(g_screen);
        fish.HandleMove();

        for(int i=0;i < SHARK_NUM;i++)
        {

            ThreatsList[i]-> set_x_val(10);
            ThreatsList[i]->ShowSharkAnimation(g_screen);
            ThreatsList[i]->HandleMove();

            bool check_coll = CommonFunc::CheckCollision(cat_obj.GetRect(), ThreatsList[i]->GetRect());
            if (check_coll) {
                cat_injured.SetRect(cat_obj.GetRect().x, cat_obj.GetRect().y);
                cat_injured.SetShownInjured(true);
            } else
            {
                cat_injured.SetShownInjured(false);
                }
            if (cat_injured.GetShowInjured()== true)
            {
                cat_injured.ShowInjuredAnimation(g_screen);
            }
        }
        SDL_RenderPresent(g_screen);
    }
    close();
    return 0;
}
