#include "Cat.h"

Cat::Cat()
{
	frame_ = 0;

    cat_w = 64*1.5;
    cat_h = 48*1.5;

    rect_.x = 0;
    rect_.y = SCREEN_HEIGHT/2 - cat_h/2;

	count_injured_times = 0;

	x_pos = rect_.x;
	y_pos = rect_.y;

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

void Cat::HandleInputAction(SDL_Event event, SDL_Renderer* src, Mix_Chunk* cat_bullet)
{
    if (event.type == SDL_KEYDOWN) {
        switch(event.key.keysym.sym) {
            case SDLK_UP:
                y_pos -= cat_h/4;
                break;
            case SDLK_DOWN:
                y_pos += cat_h/4;
                break;
            case SDLK_LEFT:
                x_pos -= cat_w/5;
                break;
            case SDLK_RIGHT:
                x_pos += cat_w/5;
                break;
            case SDLK_SPACE: {
                Mix_PlayChannel(-1, cat_bullet, 0);

                Bullet* bullet_ = new Bullet();
                bool ret = bullet_->LoadImg("img//bullet.png", src);
                if(ret) {
                bullet_->SetRect(this->GetRect().x + 60, this->GetRect().y+cat_h/2);
                bullet_->SetIsMove(true);
                bullet_list.push_back(bullet_);
                }
                else cout << "Fail";
        }
                break;
            default:
                break;
        }
    }
    if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_SPACE) {



            }
    }
}

void Cat::ControlBullet(SDL_Renderer* g_renderer)
{
    for ( int i=0; i< bullet_list.size(); i++ )
    {
            if( bullet_list[i]->GetIsMove() )
            {
                bullet_list[i]->Show(g_renderer);
                bullet_list[i]->HandleMove(SCREEN_WIDTH,SCREEN_HEIGHT);

            } else {
                delete bullet_list[i];
                bullet_list.erase(bullet_list.begin()+i);
            }
    }
}

void Cat::HandleMove()
{
    rect_.x = x_pos;
    rect_.y = y_pos;

    SetWidth(cat_w, cat_h);
    if (rect_.x < 0) rect_.x = 0;
    if (rect_.y < 10) rect_.y = 10 ;
    if (rect_.x + cat_w > SCREEN_WIDTH - 50)
        rect_.x = SCREEN_WIDTH - 64;
    if (rect_.y + cat_h > SCREEN_HEIGHT)
        rect_.y = SCREEN_HEIGHT - 50;
}

void Cat::ShowAnimation(SDL_Renderer* des)
{
    LoadImg("img//cat_idle.png", des);
	frame_ ++;
    if (frame_>=10)
        frame_ = 0;

    SDL_Rect* current_clip = &frame_idle[frame_];// trang thai hien tai o frame thu frame
    SDL_Rect cat_rect = { rect_.x, rect_.y, cat_w,cat_h };
    SDL_RenderCopy(des, p_object, current_clip, &cat_rect);
    frame_injured_ = frame_;
}

void Cat::ShowInjuredAnimation(SDL_Renderer* des)
{
    if (LoadImg("img//cat_hurt.png", des)){

    frame_injured_++;
    SDL_Rect cat_rect = { rect_.x, rect_.y, cat_w,cat_h };
    SDL_RenderCopy(des, p_object, &frame_injured[frame_injured_], &cat_rect);
    count_injured_times++;
    /**if (frame_injured_>=10) {
        ShowAnimation(des);
        return ;
    }*/
    if (count_injured_times > MAX_INJURED) {
        count_injured_times = 0;
        is_shown_injured = false;
    }
    }
}

void Cat::RemoveBullet(const int& idx)
{
	int size = bullet_list.size();
	if (size > 0 && idx < size)
	{
		Bullet* p_bullet = bullet_list.at(idx);
		bullet_list.erase(bullet_list.begin() + idx);
		if (p_bullet)
		{
			delete p_bullet;
			p_bullet = NULL;
		}
	}
}
