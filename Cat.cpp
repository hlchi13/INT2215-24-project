#include "Cat.h"

Cat::Cat()
{
	frame_ = 0;
	x_pos = 0;
	y_pos = 0;
	x_val = 0;
	y_val = 0;

	width_frame_ = 0;
	height_frame_ = 0;

	input_type_.left_ = 0;
	input_type_.down_ = 0;
	input_type_.up_ = 0;
	input_type_.down_ = 0;
	status_ = -1;
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
                input_type_.up_ = 1;
                y_val -= height_frame_/4;
                break;
            case SDLK_DOWN:
                input_type_.down_ = 1;
                y_val += height_frame_/4;
                break;
            case SDLK_LEFT:
                status_ = WALK_LEFT;
                input_type_.left_ = 1;
                x_val -= 0.8;
                break;

            case SDLK_RIGHT:
                status_ = WALK_RIGHT;
                input_type_.right_ = 1;
                x_val +=0.8;
                break;
            default:
                break;
        }
    }
    else if(event.type == SDL_KEYUP) {
        switch(event.key.keysym.sym) {
            case SDLK_UP:
                y_val += height_frame_/4;
                break;
            case SDLK_DOWN:
                y_val -= height_frame_/4;
                break;
            case SDLK_LEFT:
                input_type_.left_= 0;
                x_val += width_frame_/4;
                break;

            case SDLK_RIGHT:
                input_type_.right_ = 0;
                x_val -= width_frame_/4;
                break;
        }
    }
}

void Cat::HandleMove()
{
    rect_.x += x_val;

    if (rect_.x < 0||rect_.x + CAT_WIDTH >= SCREEN_WIDTH - 60)
    {
        rect_.x -= x_val;//gan lai vi tri ban dau
    }
    rect_.y += y_val;
    if (rect_.y < 5 || rect_.y + CAT_HEIGHT >= SCREEN_HEIGHT - 5)
    {
        rect_.y -= y_val;
    }
}

void Cat::SetAnimation()
{
	if (width_frame_ > 0 && height_frame_ > 0)
	{
		frame_forward[0].x = 0;
		frame_forward[0].y = 0;
		frame_forward[0].w = width_frame_;
		frame_forward[0].h = height_frame_;

		frame_forward[1].x = width_frame_;
		frame_forward[1].y = 0;
		frame_forward[1].w = width_frame_;
		frame_forward[1].h = height_frame_;

		frame_forward[2].x = 2*width_frame_;
		frame_forward[2].y = 0;
		frame_forward[2].w = width_frame_;
		frame_forward[2].h = height_frame_;

		frame_forward[3].x = 3*width_frame_;
		frame_forward[3].y = 0;
		frame_forward[3].w = width_frame_;
		frame_forward[3].h = height_frame_;

		frame_forward[4].x = 4*width_frame_;
		frame_forward[4].y = 0;
		frame_forward[4].w = width_frame_;
		frame_forward[4].h = height_frame_;

		frame_forward[5].x = 5*width_frame_;
		frame_forward[5].y = 0;
		frame_forward[5].w = width_frame_;
		frame_forward[5].h = height_frame_;

		frame_forward[6].x = 6*width_frame_;
		frame_forward[6].y = 0;
		frame_forward[6].w = width_frame_;
		frame_forward[6].h = height_frame_;

		frame_forward[7].x = 7*width_frame_;
		frame_forward[7].y = 0;
		frame_forward[7].w = width_frame_;
		frame_forward[7].h = height_frame_;

		frame_forward[8].x = 8*width_frame_;
		frame_forward[8].y = 0;
		frame_forward[8].w = width_frame_;
		frame_forward[8].h = height_frame_;

		frame_forward[9].x = 9*width_frame_;
		frame_forward[9].y = 0;
		frame_forward[9].w = width_frame_;
		frame_forward[9].h = height_frame_;

	}
}

void Cat::ShowAnimation(SDL_Renderer* des)
{
    if (status_ == WALK_RIGHT) {
        LoadImg("cat.png", des);
    }
	if (input_type_.left_ == 1 || input_type_.right_ == 1)
	{
		frame_++;
	}
	else
	{
		frame_ = 0;
	}
	if (frame_ >= 10)
	{
		frame_ = 0;
	}

    SDL_Rect* current_clip = &frame_forward[frame_];// trang thai hien tai o frame thu frame_

    SDL_Rect renderQuad = { rect_.x, rect_.y, width_frame_,height_frame_ }; // o toa do nao voi chieu dai chieu rong

    SDL_RenderCopy(des, p_object, current_clip, &renderQuad);

}


/**bool Cat::LoadCatImg(std::string path, SDL_Renderer* render)
{
    fly_up = CommonFunc::LoadImage(path.c_str(), render);
    if (fly_up == NULL) {
        return false;
    }
    return true;
}

*/

/**void Cat::SetAnimation()
{
    frame_normal[0].x = 0;
    frame_normal[0].y = 0 + frame_height;
    frame_normal[0].w = frame_width;
    frame_normal[0].h = frame_height;

    frame_normal[1].x = 2*frame_width;
    frame_normal[1].y = 0 + frame_height;
    frame_normal[1].w = frame_width;
    frame_normal[1].h = frame_height;

}

void Cat::ShowAnimation(SDL_Renderer* src)
{
    LoadCatImg("cat.png", src );
    if (input_type_.right_== 1)
    {
        frame++;
    }
    else
    {
        frame = 0;
    }

    rect_.x = x_val;
    rect_.y = y_val;

    SDL_Rect* current_clip_ = &frame_normal[frame];
    SDL_Rect renderQ = {rect_.x, rect_.y, frame_width, frame_height};
    SDL_RenderCopy(src, p_object, current_clip_, &renderQ );
    SDL_RenderPresent(src);
}
*/
