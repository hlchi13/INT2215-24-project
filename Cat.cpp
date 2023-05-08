#include "Cat.h"

Cat::Cat()
{
    frame_ = 0;
    x_val = 0;
    y_val = 0;

    rect_.x = 0;
    rect_.y = SCREEN_HEIGHT/2 - CAT_HEIGHT/2;
    rect_.w = CAT_WIDTH;
    rect_.h = CAT_HEIGHT;

    count_times = 0;
    is_shown_injured = false;
    is_idle = true;
    is_forward = false;
    is_backward = false;
    preX = 0;
    preY = 0;
    //cat idle
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
    //cat forward
    frame_forward[0].x = 0;
    frame_forward[0].y = 47;
    frame_forward[0].w = 64;
    frame_forward[0].h = 48;

    frame_forward[1].x = 64;
    frame_forward[1].y = 47;
    frame_forward[1].w = 64;
    frame_forward[1].h = 47;

    frame_forward[2].x = 0;
    frame_forward[2].y = 47;
    frame_forward[2].w = 64;
    frame_forward[2].h = 48;

    frame_forward[3].x = 64;
    frame_forward[3].y = 47;
    frame_forward[3].w = 64;
    frame_forward[3].h = 47;

    frame_forward[4].x = 0;
    frame_forward[4].y = 47;
    frame_forward[4].w = 64;
    frame_forward[4].h = 48;

    frame_forward[5].x = 64;
    frame_forward[5].y = 47;
    frame_forward[5].w = 64;
    frame_forward[5].h = 47;

    frame_forward[6].x = 0;
    frame_forward[6].y = 47;
    frame_forward[6].w = 64;
    frame_forward[6].h = 48;
    //backward
    frame_backward[0].x = 0;
    frame_backward[0].y = 144;
    frame_backward[0].w = 64;
    frame_backward[0].h = 48;

    frame_backward[1].x = 64;
    frame_backward[1].y = 144;
    frame_backward[1].w = 64;
    frame_backward[1].h = 48;

    frame_backward[2].x = 64*2;
    frame_backward[2].y = 144;
    frame_backward[2].w = 64;
    frame_backward[2].h = 48;

    frame_backward[3].x = 0;
    frame_backward[3].y = 144;
    frame_backward[3].w = 64;
    frame_backward[3].h = 48;

    frame_backward[4].x = 64;
    frame_backward[4].y = 144;
    frame_backward[4].w = 64;
    frame_backward[4].h = 48;

    frame_backward[5].x = 64*2;
    frame_backward[5].y = 144;
    frame_backward[5].w = 64;
    frame_backward[5].h = 48;

    frame_backward[6].x = 0;
    frame_backward[6].y = 144;
    frame_backward[6].w = 64;
    frame_backward[6].h = 48;
    //injured
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
}
Cat::~Cat()
{

}

void Cat::HandleInputAction(SDL_Event event, SDL_Renderer* src, Mix_Chunk* cat_bullet,
                            GameText &Score, GameText &number_life, GameText &num_bullet)
{
    if (event.type == SDL_MOUSEMOTION) {
        //frame_ = 0;
        SDL_GetMouseState(&mouseX, &mouseY);
        SetRect(mouseX - CAT_WIDTH, mouseY);
        if (preX < mouseX ) {
            is_forward = true;
            is_backward = false;
            is_idle = false;
        }
        else if (preX > mouseX)
        {
            is_backward = true;
            is_forward = false;
            is_idle = false;
        }
        else
        {
            is_idle = true;
            is_backward = false;
            is_forward = false;
        }
        preX = mouseX;
        preY = mouseY;
    }
      if(event.type==SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT){
            if (Score.GetValue() >= 500 || number_life.GetValue() <=2) {
                is_idle = true;
                is_backward = false;
                is_forward = false;
                if (num_bullet.GetValue() > 0) {
                    Bullet* bullet_ = new Bullet();
                    Mix_PlayChannel(-1, cat_bullet, 0);
                    bullet_->LoadImg("img//bullet.png", src);
                    bullet_->SetRect(this->GetRect().x + 60, this->GetRect().y+CAT_HEIGHT/2);
                    bullet_->SetIsMove(true);
                    bullet_list.push_back(bullet_);
                    num_bullet.IncreaseValue(-1);
                }
            }
        }
}

void Cat::ControlBullet(SDL_Renderer* g_renderer)
{
    for ( int i=0; i < (int)bullet_list.size(); i++ )
    {
        if(bullet_list[i]->GetIsMove())
        {
            bullet_list[i]->Show(g_renderer);
            bullet_list[i]->HandleMove(SCREEN_WIDTH);

        } else {
            delete bullet_list[i];
            bullet_list.erase(bullet_list.begin()+i);
        }
    }
}

void Cat::HandleMove()
{
    if (rect_.x < 0) rect_.x = 0;
    if (rect_.y < 25) rect_.y = 25 ;
    if (rect_.x + CAT_WIDTH > SCREEN_WIDTH)
        rect_.x = SCREEN_WIDTH - CAT_WIDTH;
    if (rect_.y + CAT_HEIGHT > SCREEN_HEIGHT)
        rect_.y = SCREEN_HEIGHT -CAT_HEIGHT;
}

void Cat::ShowAnimation(SDL_Renderer* des)
{
    if (is_forward) {
        SDL_RenderCopy(des, p_object, &frame_forward[frame_], &rect_);
        frame_ = (frame_+1)%7;
        count_times++;
        if (count_times >= MAX_SHOWN_TIMES) {
            count_times = 0;
            is_forward = false;
            is_idle = true;
        }
    }
    else if (is_backward) {
        SDL_RenderCopy(des, p_object, &frame_backward[frame_], &rect_);
        frame_ = (frame_+1)%7;
        count_times++;
        if (count_times >= MAX_SHOWN_TIMES) {
            count_times = 0;
            is_backward = false;
            is_idle = true;
        }
    }
    else if (is_idle)
    {
        SDL_RenderCopy(des, p_object, &frame_idle[frame_], &rect_);
        frame_ = (frame_+1)%7;
    }
}

bool Cat::LoadInjured(string path, SDL_Renderer* ren)
{
    injured = CommonFunc::LoadImage(path.c_str(), ren);
    if (injured == NULL) {
        return false;
    }
    return true;
}
void Cat::ShowInjured(SDL_Renderer* des)
{
    SDL_RenderCopy(des,injured,&frame_injured[frame_] , &rect_);
    frame_ = (frame_+1)%7;
    count_times++;
    if (count_times >= MAX_SHOWN_TIMES)
    {
        is_shown_injured = false;
        count_times = 0;
    }
}

void Cat::RemoveBullet(const int& idx)
{
    Bullet* p_bullet = bullet_list.at(idx);
    bullet_list.erase(bullet_list.begin() + idx);
    if (p_bullet)
    {
        delete p_bullet;
        p_bullet = NULL;
    }
}

