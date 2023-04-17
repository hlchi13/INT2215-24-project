#ifndef BONUS_H_INCLUDED
#define BONUS_H_INCLUDED

#include "Cat.h"
#include "Shark.h"

#define BONUS_WIDTH 60
#define BONUS_HEIGHT 30

class Bonus : public BaseObject
{
public:
    Bonus();
    //~Bonus();
    void HandleMove();
    void ShowBonus(SDL_Renderer* des);
private:
    int x_val;
    int y_val;

    int width_ = 110;
    int height_= 50;

    int num = rand()%3+1;
    string random_fish;

};


#endif // BONUS_H_INCLUDED
