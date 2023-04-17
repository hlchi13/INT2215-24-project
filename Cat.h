#ifndef CAT_H_INCLUDED
#define CAT_H_INCLUDED

#include "BaseObject.h"

#define MAX_HURT 3
#define CAT_WIDTH 96
#define CAT_HEIGHT 72
class Cat : public BaseObject
{
public:
    Cat();
    ~Cat();
    void HandleInputAction(SDL_Event event);
    void HandleMove();
    void SetAnimation();
    void ShowAnimation(SDL_Renderer* des);
    void ShowInjuredAnimation(SDL_Renderer* des);
    bool GetShowInjured() {return is_shown_injured;};
    void SetShownInjured(bool x) {is_shown_injured = x;};
private:
    float x_val; // khoang cach giua 2 vi tri
    float y_val;

    SDL_Rect frame_idle[10];
    SDL_Rect frame_injured[10];

    int cat_w;
    int cat_h;

    int frame_ = 0;
    int frame_injured_;
    int count_injured_times = 0;
    bool is_shown_injured = false;

};

#endif // CAT_H_INCLUDED
