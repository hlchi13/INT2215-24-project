#include "PlayerPower.h"

PlayerPower::PlayerPower()
{
    number = 0;
}

PlayerPower::~PlayerPower()
{

}

void PlayerPower::AddPos(const int&x)
{
    pos_list.push_back(x);
}

void PlayerPower::Init(SDL_Renderer* des)
{
    LoadImg("img_heart.png", des);
    number = 3;
    AddPos(0);
    AddPos(40);
    AddPos(80);
}

void PlayerPower::Show(SDL_Renderer* des)
{
    for (int i = 0; i < (int)pos_list.size(); i++)
	{
		rect_.x = pos_list.at(i);
		rect_.y = 0;
		rect_.w = HEART_WIDTH;
		rect_.h = HEART_HEIGHT;
		SDL_RenderCopy(des, p_object, NULL, &rect_);
	}
}
void PlayerPower::Decrease()
{
    number--;
    pos_list.pop_back();
}

void PlayerPower::Increase()
{
    number++;

}
