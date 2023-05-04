#include "Bonus.h"

Bonus::Bonus()
{
    rect_.x = SCREEN_WIDTH;
    rect_.y = rand()%400+20;
    rect_.w = BONUS_WIDTH;
    rect_.h = BONUS_WIDTH;
}

void Bonus::SetType(int type)
{
    type_ = type;
    switch(type_)
    {
    case 1:
        random_fish = "img//fish_pink.png";
        break;
    case 2:
        random_fish = "img//fish_blue.png";
        break;
    case 3:
        random_fish = "img//fish_yellow.png";
        break;
    }

}
void Bonus::HandleMove()
{
    rect_.x -= 20;
    rect_.w = BONUS_WIDTH;
    rect_.h = BONUS_HEIGHT;
}
void Bonus::ShowBonus(SDL_Renderer* des)
{
    LoadImg(random_fish, des);
    SDL_Rect fish_rect = {rect_.x, rect_.y, BONUS_WIDTH, BONUS_HEIGHT};
    SDL_RenderCopy(des, p_object, NULL, &fish_rect);
}




