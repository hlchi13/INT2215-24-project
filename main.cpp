#include <chrono>
#include"GameFunctions.h"
using namespace std;

int main(int argc, char* argv[])
{
    srand(time(0));
    GameFunctions game;
    if (game.InitData() == false)
		return 0;
    game.Run();
    return 0;
}
