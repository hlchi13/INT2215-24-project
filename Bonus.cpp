#include "Bonus.h"

Bonus::Bonus()
{
    rect_.x = SCREEN_WIDTH + 10;
    rect_.y = rand()%400 + 20;
    rect_.w = BONUS_WIDTH;
    rect_.h = BONUS_HEIGHT;


    switch(num)
    {
    case 1:
        random_fish = "img//fish1.png";
        break;
    case 2:
        random_fish = "img//fish2.png";
        break;
    case 3:
        random_fish = "img//fish3.png";
        break;
    }
}

void Bonus::HandleMove()
{
    rect_.x -= 10;
}
void Bonus::ShowBonus(SDL_Renderer* des)
{
    LoadImg(random_fish, des);
    SDL_Rect fish_rect = {rect_.x, rect_.y, BONUS_WIDTH, BONUS_HEIGHT};
    SDL_RenderCopy(des, p_object, NULL, &fish_rect);
}



