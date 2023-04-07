#include "Cat.h"

Cat::Cat()
{
	frame_ = 0;
	x_val = 0;
	y_val = 0;

	width_frame_ = 0;
	height_frame_ = 0;

	count_injured_times = 0;
}

Cat::~Cat()
{

}
bool Cat::LoadImg(std::string path, SDL_Renderer* screen)
{
	bool ret = BaseObject::LoadImg(path, screen);

	if (ret == true)
	{
		width_frame_ = 64;
		height_frame_ = 48;
	}
	return ret;
}

SDL_Rect Cat::GetRectFrame()
{
	SDL_Rect rect;
	rect.x = rect_.x;
	rect.y = rect_.y;
	rect.h = height_frame_;
	rect.w = width_frame_;
	return rect;
}

void Cat::HandleInputAction(SDL_Event event)
{
    if (event.type == SDL_KEYDOWN) { // bam phim xuong
        switch(event.key.keysym.sym) {
            case SDLK_UP:
                y_val -= 10;
                break;
            case SDLK_DOWN:
                y_val += 10;
                break;
            case SDLK_LEFT:
                x_val -= 10;
                break;

            case SDLK_RIGHT:
                x_val += 10;
                break;
            default:
                break;
        }
    }
    else if(event.type == SDL_KEYUP) {
        switch(event.key.keysym.sym) {
            case SDLK_UP:

                break;
            case SDLK_DOWN:

                break;
            case SDLK_LEFT:

                break;

            case SDLK_RIGHT:


                break;
        }
    }
}

void Cat::HandleMove()
{
    rect_.x = x_val;
    rect_.y = y_val;
    if (rect_.x < 0) rect_.x = 0;
    if (rect_.y < 0) rect_.y = 0;
    if (rect_.x + 64 > SCREEN_WIDTH)
        rect_.x = SCREEN_WIDTH - 64;
    if (rect_.y + 48 > SCREEN_HEIGHT)
        rect_.y = SCREEN_HEIGHT - 48;
}

void Cat::SetAnimation()
{
	if (width_frame_ > 0 && height_frame_ > 0)
	{
		frame_idle[0].x = 0;
		frame_idle[0].y = 0;
		frame_idle[0].w = width_frame_;
		frame_idle[0].h = height_frame_;

		frame_idle[1].x = width_frame_;
		frame_idle[1].y = 0;
		frame_idle[1].w = width_frame_;
		frame_idle[1].h = height_frame_;

		frame_idle[2].x = 2*width_frame_;
		frame_idle[2].y = 0;
		frame_idle[2].w = width_frame_;
		frame_idle[2].h = height_frame_;

		frame_idle[3].x = 3*width_frame_;
		frame_idle[3].y = 0;
		frame_idle[3].w = width_frame_;
		frame_idle[3].h = height_frame_;

		frame_idle[4].x = 4*width_frame_;
		frame_idle[4].y = 0;
		frame_idle[4].w = width_frame_;
		frame_idle[4].h = height_frame_;

		frame_idle[5].x = 5*width_frame_;
		frame_idle[5].y = 0;
		frame_idle[5].w = width_frame_;
		frame_idle[5].h = height_frame_;

		frame_idle[6].x = 6*width_frame_;
		frame_idle[6].y = 0;
		frame_idle[6].w = width_frame_;
		frame_idle[6].h = height_frame_;

		frame_idle[7].x = 7*width_frame_;
		frame_idle[7].y = 0;
		frame_idle[7].w = width_frame_;
		frame_idle[7].h = height_frame_;

		frame_idle[8].x = 8*width_frame_;
		frame_idle[8].y = 0;
		frame_idle[8].w = width_frame_;
		frame_idle[8].h = height_frame_;

		frame_idle[9].x = 9*width_frame_;
		frame_idle[9].y = 0;
		frame_idle[9].w = width_frame_;
		frame_idle[9].h = height_frame_;

	}
}

void Cat::ShowAnimation(SDL_Renderer* des)
{

    LoadImg("catsheet.png", des);

	frame_ ++;
    if (frame_>=10)
        frame_ = 0;

    SDL_Rect* current_clip = &frame_idle[frame_];// trang thai hien tai o frame thu frame_

    SDL_Rect cat_rect = { rect_.x, rect_.y, width_frame_*1.5,height_frame_*1.5 }; // o toa do nao voi chieu dai chieu rong

    SDL_RenderCopy(des, p_object, current_clip, &cat_rect);

}
