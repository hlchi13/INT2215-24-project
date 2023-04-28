#ifndef BONUS_H_INCLUDED
#define BONUS_H_INCLUDED

#include "Cat.h"
#include "Shark.h"

const int MAX_COUNT = 3;
class Bonus : public BaseObject
{
public:
    Bonus();
    //~Bonus();
    void HandleMove();
    void ShowBonus(SDL_Renderer* des);
    void SetType(int type);
    int GetType() {return type_;};
    void SetIsShown(bool x) {is_shown = x;};
    bool GetIsShown() {return is_shown;};
    void HandleCount();
private:
    int x_val;
    bool is_shown = true;
    int type_;
    int count_= 0;
    string random_fish;

};


#endif // BONUS_H_INCLUDED
