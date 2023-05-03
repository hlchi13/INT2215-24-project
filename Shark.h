#ifndef SHARK_H_INCLUDED
#define SHARK_H_INCLUDED

#include "CommonFunc.h"
#include "BaseObject.h"

class Shark : public BaseObject
{
public:
    Shark();
    ~Shark();
    void ShowSharkAnimation (SDL_Renderer* des);
    void SetWidth(const int w, const int h) {rect_.w = w; rect_.h = h;};
    void HandleMove();
    void Reset(const int &x_border);
    void set_x_val(const int &val) {x_val = val;};
    void set_y_val(const int &val) {y_val = val;};

private:
    SDL_Rect frame_shark[7];
    int frame_;
    int x_val;
    int y_val;
    int num;
};

#endif // SHARK_H_INCLUDED
