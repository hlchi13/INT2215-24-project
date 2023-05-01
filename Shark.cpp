#include "Shark.h"

Shark::Shark()
{
    frame_ = 0;

    x_val = 0;
    y_val = 0;

    rect_.x = SCREEN_WIDTH + 10;
    rect_.y = rand()%(SCREEN_HEIGHT - SHARK_HEIGHT) + 25;
    rect_.w = SHARK_WIDTH;
    rect_.h = SHARK_HEIGHT;
    num = rand()%2;

    frame_shark[0].x = 0;
    frame_shark[0].y = 0;
    frame_shark[0].w = 64;
    frame_shark[0].h = 37;

    frame_shark[1].x = 64;
    frame_shark[1].y = 0;
    frame_shark[1].w = 64;
    frame_shark[1].h = 37;

    frame_shark[2].x = 2*64;
    frame_shark[2].y = 0;
    frame_shark[2].w = 64;
    frame_shark[2].h = 37;

    frame_shark[3].x = 3*64;
    frame_shark[3].y = 0;
    frame_shark[3].w = 64;
    frame_shark[3].h = 37;

    frame_shark[4].x = 4*64;
    frame_shark[4].y = 0;
    frame_shark[4].w = 64;
    frame_shark[4].h = 37;

    frame_shark[5].x = 5*64;
    frame_shark[5].y = 0;
    frame_shark[5].w = 64;
    frame_shark[5].h = 37;

    frame_shark[6].x = 6*64;
    frame_shark[6].y = 0;
    frame_shark[6].w = 64;
    frame_shark[6].h = 37;
}


Shark::~Shark()
{

}

void Shark::ShowSharkAnimation(SDL_Renderer* des)
{
    //SDL_Rect shark_rect = { rect_.x, rect_.y, shark_w,shark_h }; // o toa do nao voi chieu dai chieu rong
    SDL_RenderCopy(des, p_object, &frame_shark[frame_], &rect_);
    frame_ = (frame_+1)%7;
}

void Shark::HandleMove()
{
    rect_.x -= x_val;
    if (rect_.y + SHARK_HEIGHT > SCREEN_HEIGHT)
    {
        rect_.y = SCREEN_HEIGHT - SHARK_HEIGHT;
    }
    rect_.y += y_val;
    SetWidth(SHARK_WIDTH, SHARK_HEIGHT);
}

void Shark::Reset(const int &x_border)
{
    rect_.x = x_border;
    rect_.y = rand()%400 + 25;
}

