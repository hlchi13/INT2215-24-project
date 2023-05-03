#include <chrono>
#include"GameFunctions.h"
using namespace std;

int main(int argc, char* argv[])
{
    srand(time(0));
    GameFunctions game;
    if (game.InitData() == false)
		return 0;
    bool re_play = 1;
    while(re_play) {
        game.Replay();
        bool show = game.ShowIntro();
        if (!show)
        {
            break;
        }
        game.Run();
        re_play = game.ShowEnd();
    }

    return 0;
}
