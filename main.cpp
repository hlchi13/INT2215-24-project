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
    do {
        game.Replay();
        bool show = game.ShowIntro();
        if (!show)
        {
            break;
        }
        game.Run();
        re_play = game.ShowEnd();
    } while(re_play);

    return 0;
}
