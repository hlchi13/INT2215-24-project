#ifndef CAT_H_INCLUDED
#define CAT_H_INCLUDED

#include "BaseObject.h"

#define MAX_HURT 3
class Cat : public BaseObject
{
public:
    Cat();
    ~Cat();
    void HandleInputAction(SDL_Event event);
    void HandleMove();
    SDL_Rect GetRectFrame();
    void SetAnimation();
    void ShowAnimation(SDL_Renderer* des);
    void ShowHurtAnimation(SDL_Renderer* des);
    void DoPlayer();
private:
    float x_val; // khoang cach giua 2 vi tri
    float y_val;

    SDL_Texture* fly_up;
    SDL_Texture* fly_down;
    SDL_Texture* fly_forward;
    SDL_Texture* fly_backward;

    SDL_Rect frame_idle[10];
    SDL_Rect frame_injured[6];

    int width_frame_;
    int height_frame_;

    int cat_w;
    int cat_h;

    int frame_ = 0;
    int hurt_ = 0;
    int count_hurt_times;

};

#endif // CAT_H_INCLUDED
