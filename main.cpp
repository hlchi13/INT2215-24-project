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

    Cat cat_obj;
    cat_obj.SetRect(0, SCREEN_HEIGHT/2 - 64/2);
    cat_obj.SetAnimation();

    Shark shark_obj;
    shark_obj.SetAnimation();

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

		SDL_RenderClear(g_screen);
        g_background.ShowBackground(g_screen);

        shark_obj.ShowSharkAnimation(g_screen);
        shark_obj.HandleMove();

        cat_obj.ShowAnimation(g_screen);
        cat_obj.HandleMove();

        SDL_RenderPresent(g_screen);
    }

    close();
    return 0;
}
