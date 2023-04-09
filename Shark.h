#ifndef SHARK_H_INCLUDED
#define SHARK_H_INCLUDED

#include "CommonFunc.h"
#include "BaseObject.h"

#define F_SHARK_WIDTH  64
#define F_SHARK_HEIGHT 64
class Shark : public BaseObject
{
public:
    Shark();
    ~Shark();
    void SetAnimation();
    void ShowSharkAnimation (SDL_Renderer* des);
    void HandleMove();
    void ShowShark(SDL_Renderer* des);
private:
    SDL_Rect frame_shark[7];
    int frame_;

    float x_val;

};

#endif // SHARK_H_INCLUDED
