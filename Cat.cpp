#include "Cat.h"

Cat::Cat()
{
	frame_ = 0;
	x_val_ = 0;
	y_val_ = 0;
    rect_.x = 0;
    rect_.y = SCREEN_HEIGHT/2 - CAT_HEIGHT/2;
    rect_.w = CAT_WIDTH;
    rect_.h = CAT_HEIGHT;

	count_injured_times_ = 0;
	is_shown_injured = false;
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

void Cat::HandleInputAction(SDL_Event event, SDL_Renderer* src, Mix_Chunk* cat_bullet,
                            GameText &Score, GameText &number_life)
{
    if(event.type==SDL_KEYUP && event.key.repeat==0){

      switch(event.key.keysym.sym){
         case SDLK_UP:
             y_val_+= CAT_SPEED;
             break;
         case SDLK_DOWN:
            y_val_-= CAT_SPEED;
            break;
         case SDLK_LEFT:
             x_val_+= CAT_SPEED;
             break;
         case SDLK_RIGHT:
            x_val_-= CAT_SPEED;
             break;
        }
       }
      else if(event.type==SDL_KEYDOWN && event.key.repeat==0){
          switch(event.key.keysym.sym){
             case SDLK_UP:
                 y_val_-=CAT_SPEED;
                 break;
             case SDLK_DOWN:
                 y_val_+=CAT_SPEED;
                break;
             case SDLK_LEFT:
                 x_val_-=CAT_SPEED;
                 break;
             case SDLK_RIGHT:
                x_val_+=CAT_SPEED;
                 break;
             case SDLK_SPACE:
                if (Score.GetValue() >= 500 || number_life.GetValue() <=3) {
                Mix_PlayChannel(-1, cat_bullet, 0);

                Bullet* bullet_ = new Bullet();
                bool ret = bullet_->LoadImg("img//bullet.png", src);
                if(ret) {
                bullet_->SetRect(this->GetRect().x + 60, this->GetRect().y+CAT_HEIGHT/2);
                bullet_->SetIsMove(true);
                bullet_list.push_back(bullet_);
                }
                else cout << "Fail";
                 }
             break;
          }
      }
}

void Cat::ControlBullet(SDL_Renderer* g_renderer)
{
    for ( int i=0; i< (int)bullet_list.size(); i++ )
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
    rect_.x +=x_val_;
    rect_.y += y_val_;
    if (rect_.x < 0) rect_.x = 0;
    if (rect_.y < 25) rect_.y = 25 ;
    if (rect_.x + CAT_WIDTH > SCREEN_WIDTH)
        rect_.x = SCREEN_WIDTH - CAT_WIDTH;
    if (rect_.y + CAT_HEIGHT > SCREEN_HEIGHT)
        rect_.y = SCREEN_HEIGHT -CAT_HEIGHT;
}

void Cat::ShowAnimation(SDL_Renderer* des)
{
    SDL_RenderCopy(des, p_object, &frame_idle[frame_], &rect_);
    frame_ = (frame_+1)%10; // tra ve so nho hon 10 va tang them 1 sau moi lan
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
    frame_ = (frame_+1)%10;
    count_injured_times_++;
    if ( count_injured_times_ >= MAX_INJURED_TIMES )
    {
        is_shown_injured = false ;
        count_injured_times_ = 0 ;
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

