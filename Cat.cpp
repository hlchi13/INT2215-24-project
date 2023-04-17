#include "Cat.h"

Cat::Cat()
{
	frame_ = 0;
	x_val = 0;
	y_val = SCREEN_HEIGHT/2 - CAT_HEIGHT/2; // vi tri ban dau cua cat

    cat_w = CAT_WIDTH;
    cat_h = CAT_HEIGHT;

    rect_.x = 0;
    rect_.y = SCREEN_HEIGHT/2 - CAT_HEIGHT/2;
    rect_.w = CAT_WIDTH;
    rect_.h = CAT_HEIGHT;
	count_injured_times = 0;

    frame_idle[0].x = 0;
    frame_idle[0].y = 0;
    frame_idle[0].w = 64;
    frame_idle[0].h = 48;

    frame_idle[1].x = 64;
    frame_idle[1].y = 0;
    frame_idle[1].w = 64;
    frame_idle[1].h = 48;

    frame_idle[2].x = 2*64;
    frame_idle[2].y = 0;
    frame_idle[2].w = 64;
    frame_idle[2].h = 48;

    frame_idle[3].x = 3*64;
    frame_idle[3].y = 0;
    frame_idle[3].w = 64;
    frame_idle[3].h = 48;

    frame_idle[4].x = 4*64;
    frame_idle[4].y = 0;
    frame_idle[4].w = 64;
    frame_idle[4].h = 48;

    frame_idle[5].x = 5*64;
    frame_idle[5].y = 0;
    frame_idle[5].w = 64;
    frame_idle[5].h = 48;

    frame_idle[6].x = 6*64;
    frame_idle[6].y = 0;
    frame_idle[6].w = 64;
    frame_idle[6].h = 48;

    frame_idle[7].x = 7*64;
    frame_idle[7].y = 0;
    frame_idle[7].w = 64;
    frame_idle[7].h = 48;

    frame_idle[8].x = 8*64;
    frame_idle[8].y = 0;
    frame_idle[8].w = 64;
    frame_idle[8].h = 48;

    frame_idle[9].x = 9*64;
    frame_idle[9].y = 0;
    frame_idle[9].w = 64;
    frame_idle[9].h = 48;


    frame_injured[0].x = 0;
    frame_injured[0].y = 0;
    frame_injured[0].w = 64;
    frame_injured[0].h = 48;

    frame_injured[1].x = 0+64;
    frame_injured[1].y = 0;
    frame_injured[1].w = 64;
    frame_injured[1].h = 48;

    frame_injured[2].x = 2*64;
    frame_injured[2].y = 0;
    frame_injured[2].w = 64;
    frame_injured[2].h = 48;

    frame_injured[3].x = 3*64;
    frame_injured[3].y = 0;
    frame_injured[3].w = 64;
    frame_injured[3].h = 48;

    frame_injured[4].x = 4*64;
    frame_injured[4].y = 0;
    frame_injured[4].w = 64;
    frame_injured[4].h = 48;

    frame_injured[5].x = 5*64;
    frame_injured[5].y = 0;
    frame_injured[5].w = 64;
    frame_injured[5].h = 48;

    frame_injured[6].x = 6*64;
    frame_injured[6].y = 0;
    frame_injured[6].w = 64;
    frame_injured[6].h = 48;

    frame_injured[7].x = 7*64;
    frame_injured[7].y = 0;
    frame_injured[7].w = 64;
    frame_injured[7].h = 48;

    frame_injured[8].x = 8*64;
    frame_injured[8].y = 0;
    frame_injured[8].w = 64;
    frame_injured[8].h = 48;

    frame_injured[9].x = 9*64;
    frame_injured[9].y = 0;
    frame_injured[9].w = 64;
    frame_injured[9].h = 48;
}
Cat::~Cat()
{

}

void Cat::HandleInputAction(SDL_Event event)
{
    if (event.type == SDL_KEYDOWN) {
        switch(event.key.keysym.sym) {
            case SDLK_UP:
                y_val -= cat_h/4;
                break;
            case SDLK_DOWN:
                y_val += cat_h/4;
                break;
            case SDLK_LEFT:
                x_val -= cat_w/5;
                break;
            case SDLK_RIGHT:
                x_val += cat_w/5;
                break;
            default:
                break;
        }
    }
}

void Cat::HandleMove()
{
    rect_.x = x_val;
    rect_.y = y_val;
    if (rect_.x < 0) rect_.x = 0;
    if (rect_.y < 10) rect_.y = 10 ;
    if (rect_.x + cat_w > SCREEN_WIDTH - 50)
        rect_.x = SCREEN_WIDTH - 64;
    if (rect_.y + cat_h > SCREEN_HEIGHT)
        rect_.y = SCREEN_HEIGHT - 50;
}

void Cat::ShowAnimation(SDL_Renderer* des)
{
    LoadImg("img_cat_idle.png", des);
	frame_ ++;
    if (frame_>=10)
        frame_ = 0;

    SDL_Rect* current_clip = &frame_idle[frame_];// trang thai hien tai o frame thu frame
    SDL_Rect cat_rect = { rect_.x, rect_.y, cat_w,cat_h }; // o toa do nao voi chieu dai chieu rong
    SDL_RenderCopy(des, p_object, current_clip, &cat_rect);
    frame_injured_ = frame_;
}

void Cat::ShowInjuredAnimation(SDL_Renderer* des)
{
    if (LoadImg("cat_hurt1.png", des)){

    frame_injured_++;
    SDL_Rect cat_rect = { rect_.x, rect_.y, cat_w,cat_h };
    SDL_RenderCopy(des, p_object, &frame_injured[frame_injured_], &cat_rect);
    count_injured_times++;
    if (frame_injured_>=10) {
        ShowAnimation(des);
        return ;
    }
    if (count_injured_times > MAX_INJURED_TIMES) {
        count_injured_times = 0;
        is_shown_injured = false;
    }
    }
}

