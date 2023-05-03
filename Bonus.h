#ifndef BONUS_H_INCLUDED
#define BONUS_H_INCLUDED

#include "Cat.h"
#include "Shark.h"

class Bonus : public BaseObject
{
public:
    Bonus();
    //~Bonus();
    void HandleMove();
    void ShowBonus(SDL_Renderer* des);
    void SetType(int type);
    int GetType() {return type_;};
private:
    int x_val;
    int type_;
    int count_= 0;
    string random_fish;

};


#endif // BONUS_H_INCLUDED
