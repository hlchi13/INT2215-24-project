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
    void set_x_val(const int &val) {x_val = val;};
    void set_y_val(const int &val) {y_val = val;};
    int get_x_val() {return x_val;};
    bool GetToIncreaseScore() {return score_;};
    void SetToIncreaseScore(bool x) {score_  = x;};

private:
    SDL_Rect frame_shark[7];
    int frame_;
    int x_val;
    int y_val;
    int num;
    bool score_;
};

#endif // SHARK_H_INCLUDED
