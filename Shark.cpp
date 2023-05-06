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
    score_ = true;
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
    SDL_RenderCopy(des, p_object, &frame_shark[frame_], &rect_);
    frame_ = (frame_+1)%7;
}

void Shark::HandleMove()
{
    rect_.x -= x_val;
    int num = rand()%2;
    switch(num) {
        case 0:
            rect_.y +=y_val;
            break;
        case 1:
            rect_.y -= y_val;
            break;
    }
    if (rect_.y + SHARK_HEIGHT > SCREEN_HEIGHT)
    {
        rect_.y = SCREEN_HEIGHT - SHARK_HEIGHT;
    }
    if (rect_.y < 40) rect_.y = 40;
    SetWidth(SHARK_WIDTH, SHARK_HEIGHT);
}

