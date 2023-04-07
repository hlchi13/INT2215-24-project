#ifndef CAT_H_INCLUDED
#define CAT_H_INCLUDED

#include "BaseObject.h"

#define CAT_WIDTH 48
#define CAT_HEIGHT 48

class Cat : public BaseObject
{
public:
    Cat();
    ~Cat();
    bool LoadImg(std::string path, SDL_Renderer* render);
    void HandleInputAction(SDL_Event event);
    void HandleMove();
    SDL_Rect GetRectFrame();
    void SetAnimation();
    void ShowAnimation(SDL_Renderer* src);
    void DoPlayer();
private:
    float x_val; // khoang cach giua 2 vi tri
    float y_val;

    SDL_Texture* fly_up;
    SDL_Texture* fly_down;
    SDL_Texture* fly_forward;
    SDL_Texture* fly_backward;

    SDL_Rect frame_idle[10];


    int width_frame_;
    int height_frame_;

    int frame_ = 0;
    int count_injured_times;

};

#endif // CAT_H_INCLUDED
