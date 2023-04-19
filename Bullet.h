#ifndef BULLET_H_INCLUDED
#define BULLET_H_INCLUDED

#include "BaseObject.h"

class Bullet : public BaseObject
{
public:
    Bullet();
    ~Bullet();
    void HandleMove(const int x_border, const int y_border);
    void SetIsMove(bool x) {is_move = x;};
    bool GetIsMove() {return is_move;};
    void ShowBullet(SDL_Renderer* ren);
private:
    int x_val;
    int y_val;
    bool is_move;
};
#endif // BULLET_H_INCLUDED
