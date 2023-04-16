#include <iostream>
#include "SDL_utils.h"
#include"Game.h"
using namespace std;


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
    cat_obj.LoadImg("cat_idle.png", g_screen);


    vector<Shark*> ThreatsList;
    srand(time(NULL));
    for (int i = 0; i < SHARK_NUM; i++) {
        ThreatsList.push_back(new Shark);
        //ThreatsList[ThreatsList.size()-1]->LoadImg("sharksheet.png",g_screen);
        int shark_y = rand() % 400;
        ThreatsList[i]->SetRect(SCREEN_WIDTH + 400*i, shark_y);
        ThreatsList[i]->SetAnimation();
        }

    while(is_quit) {

        while(SDL_PollEvent(&g_event))
        {
            if (g_event.type == SDL_QUIT || g_event.key.keysym.sym == SDLK_ESCAPE)
            {
                is_quit = false;
                break;

            }
            cat_obj.HandleInputAction(g_event);
        }
        SDL_RenderPresent(g_screen);
		SDL_RenderClear(g_screen);
        g_background.ShowBackground(g_screen);

        cat_obj.ShowAnimation(g_screen);
        cat_obj.HandleMove();

        for(int i=0;i < SHARK_NUM;i++)
        {

            ThreatsList[i]-> set_x_val(10);
            ThreatsList[i]->ShowSharkAnimation(g_screen);
            ThreatsList[i]->HandleMove();

            bool check_coll = CommonFunc::CheckCollision(cat_obj.GetRect(), ThreatsList[i]->GetRect());
            if (check_coll) {
                cat_obj.SetShownInjured(true);
            } else cat_obj.SetShownInjured(false);

            if(cat_obj.GetShowInjured()== false) continue;
            else cat_obj.ShowInjuredAnimation(g_screen);


        }
    }
    //delete [] shark_obj;
    close();
    return 0;
}
