#include "Bullet.h"

Bullet::Bullet()
{
    rect_.x = 0;
    rect_.y = 0;
    rect_.w = 40;
    rect_.h = 20;

    x_val = 0;
    y_val = 0;
    is_move = false;
}

Bullet::~Bullet()
{

}

void Bullet::HandleMove(const int x_border, const int y_border)
{
    rect_.x += 25;
    if (rect_.x + rect_.w > x_border) {
        is_move = false;
    }
}
