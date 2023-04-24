#include <chrono>
#include"GameFunctions.h"
using namespace std;

int main(int argc, char* argv[])
{
    srand(time(0));
    GameFunctions mainloop;
    if (mainloop.InitData() == false)
		return 0;
    mainloop.Run();
    return 0;
}
