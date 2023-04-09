#include "Shark.h"

Shark::Shark()
{
    frame_ = 0;

    rect_.x = SCREEN_WIDTH + 10;
    rect_.y = rand()% 500;
    rect_.w = F_SHARK_WIDTH;
    rect_.h = F_SHARK_HEIGHT;

}


Shark::~Shark()
{

}

void Shark::SetAnimation()
{
    frame_shark[0].x = 0;
    frame_shark[0].y = 0;
    frame_shark[0].w = F_SHARK_WIDTH;
    frame_shark[0].h = F_SHARK_HEIGHT;

    frame_shark[1].x = 0 + F_SHARK_WIDTH;
    frame_shark[1].y = 0;
    frame_shark[1].w = F_SHARK_WIDTH;
    frame_shark[1].h = F_SHARK_HEIGHT;

    frame_shark[2].x = 0 + 2*F_SHARK_WIDTH;
    frame_shark[2].y = 0;
    frame_shark[2].w = F_SHARK_WIDTH;
    frame_shark[2].h = F_SHARK_HEIGHT;

    frame_shark[3].x = 0 + 3*F_SHARK_WIDTH;
    frame_shark[3].y = 0;
    frame_shark[3].w = F_SHARK_WIDTH;
    frame_shark[3].h = F_SHARK_HEIGHT;

    frame_shark[4].x = 0 + 4*F_SHARK_WIDTH;
    frame_shark[4].y = 0;
    frame_shark[4].w = F_SHARK_WIDTH;
    frame_shark[4].h = F_SHARK_HEIGHT;

    frame_shark[5].x = 0 + 5*F_SHARK_WIDTH;
    frame_shark[5].y = 0;
    frame_shark[5].w = F_SHARK_WIDTH;
    frame_shark[5].h = F_SHARK_HEIGHT;

    frame_shark[6].x = 0 + 6*F_SHARK_WIDTH;
    frame_shark[6].y = 0;
    frame_shark[6].w = F_SHARK_WIDTH;
    frame_shark[6].h = F_SHARK_HEIGHT;
}
void Shark::ShowSharkAnimation(SDL_Renderer* des)
{
    LoadImg("sharksheet.png", des);
    frame_++;
    if (frame_>=7) frame_= 0;

    SDL_Rect* current_clip = &frame_shark[frame_];
    SDL_Rect shark_rect = { rect_.x, rect_.y, F_SHARK_WIDTH*2,F_SHARK_WIDTH*2 }; // o toa do nao voi chieu dai chieu rong
    SDL_RenderCopy(des, p_object, current_clip, &shark_rect);
    SDL_Delay(100);
}

void Shark::HandleMove()
{
    rect_.x -= 10;
    if (rect_.x < - 2*F_SHARK_WIDTH) rect_.x = SCREEN_WIDTH;
}

void Shark::ShowShark(SDL_Renderer* des)
{
    LoadImg("shark1.png", des);
    SDL_Rect shark_rect = { rect_.x, rect_.y, F_SHARK_WIDTH*2,F_SHARK_WIDTH*2 }; // o toa do nao voi chieu dai chieu rong
    SDL_RenderCopy(des, p_object, NULL, &shark_rect);
}
