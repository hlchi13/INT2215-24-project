#include <chrono>
#include"GameFunctions.h"
using namespace std;

int main(int argc, char* argv[])
{
    srand(time(0));
    GameFunctions game;
    if (game.InitData() == false)
        return 0;
    bool play = 1;
    do {
        game.Replay();
        bool show = game.ShowIntro();
        if (!show)
        {
            break;
        }
        game.Run();
        play = game.ShowEnd();
    } while(play);
    return 0;
}
