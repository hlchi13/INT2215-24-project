#include "Shark.h"

Shark::Shark()
{
    frame_ = 0;

    x_val = 0;
    y_val = 0;

    shark_w = 2.5*64;
    shark_h = 2.5*37;

    rect_.w = shark_w;
    rect_.h = shark_h;
    num = rand()%2;
}


Shark::~Shark()
{

}

void Shark::SetAnimation()
{
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
void Shark::ShowSharkAnimation(SDL_Renderer* des)
{
    bool ret =LoadImg("img//sharksheet.png", des);
    if (!ret) cout << "fail";
    else {
    frame_++;
    if (frame_>=7) frame_= 0;

    SDL_Rect* current_clip = &frame_shark[frame_];
    SDL_Rect shark_rect = { rect_.x, rect_.y, shark_w,shark_h }; // o toa do nao voi chieu dai chieu rong
    SDL_RenderCopy(des, p_object, current_clip, &shark_rect);
    }
}

void Shark::HandleMove()
{
    rect_.x -= x_val;
    if (rect_.x < -shark_w) {
        rect_.x = SCREEN_WIDTH + 2*shark_w;
    }
    rect_.y += y_val;
    if (rect_.y < 20) {
        rect_.y = 20;
        rect_.y += y_val;
    } else if (rect_.y + shark_h > SCREEN_HEIGHT)
    {
        rect_.y = SCREEN_HEIGHT - shark_h;
        rect_.y -= y_val;
    }
    rect_.w = shark_w;
    rect_.h = shark_h;
}

void Shark::Reset(const int &x_border)
{
    rect_.x = x_border;
    rect_.y = rand()%400;
}

