#ifndef SHARK_H_INCLUDED
#define SHARK_H_INCLUDED

#include "CommonFunc.h"
#include "BaseObject.h"

#define SHARK_WIDTH  64
#define SHARK_HEIGHT 64
class Shark : public BaseObject
{
public:
    Shark();
    ~Shark();
    void SetAnimation();
    void ShowSharkAnimation (SDL_Renderer* des);
    void HandleMove();
private:
    SDL_Rect frame_shark[7];
    int frame_;

    int x_val;
    int y_val;

};

#endif // SHARK_H_INCLUDED
