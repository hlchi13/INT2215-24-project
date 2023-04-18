#ifndef PLAYERPOWER_H_INCLUDED
#define PLAYERPOWER_H_INCLUDED

#include "BaseObject.h"
#define HEART_WIDTH 50
#define HEART_HEIGHT 40
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
