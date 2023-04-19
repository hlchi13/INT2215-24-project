#ifndef PLAYERPOWER_H_INCLUDED
#define PLAYERPOWER_H_INCLUDED

#include "BaseObject.h"
#define HEART_WIDTH 40
#define HEART_HEIGHT 25
class PlayerPower : public BaseObject
{
public:
    PlayerPower();
    ~PlayerPower();
    void AddPos(const int &x);
    void Show(SDL_Renderer* des);
    void Init(SDL_Renderer* des);
    void Decrease();
    void Increase();
private:
    int number;
    vector <int> pos_list;
};

#endif // PLAYERPOWER_H_INCLUDED
