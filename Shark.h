#ifndef SHARK_H_INCLUDED
#define SHARK_H_INCLUDED

#include "CommonFunc.h"
#include "BaseObject.h"

#define F_SHARK_WIDTH  64
#define F_SHARK_HEIGHT 37

class Shark : public BaseObject
{
public:
    Shark();
    ~Shark();
    void SetAnimation();
    void ShowSharkAnimation (SDL_Renderer* des);
    void HandleMove();
    void ShowShark(SDL_Renderer* des);

    void set_x_val(const int &val) {x_val = val;};
    void set_y_val(const int &val) {y_val = val;};

private:
    SDL_Rect frame_shark[7];
    int frame_;

    int x_val;
    int y_val;

    int shark_w;
    int shark_h;
};

#endif // SHARK_H_INCLUDED
