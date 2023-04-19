#ifndef CAT_H_INCLUDED
#define CAT_H_INCLUDED

#include "BaseObject.h"
#include "Bullet.h"

const int LIVES = 5;
const int MAX_INJURED = 5;

class Cat : public BaseObject
{
public:
    Cat();
    ~Cat();
    void HandleInputAction(SDL_Event event, SDL_Renderer* src, Mix_Chunk* cat_bullet);
    void HandleMove();
    void ShowAnimation(SDL_Renderer* des);

    void SetBulletList(vector<Bullet*> _bullet_list_){
        bullet_list = _bullet_list_ ;
    }
    void SetWidth(const int w, const int h) {rect_.w = w; rect_.h = h;};
	void ControlBullet(SDL_Renderer* g_renderer);
	vector <Bullet*> GetBulletList() {  return bullet_list; } ;

    void ShowInjuredAnimation(SDL_Renderer* des);
    bool GetShowInjured() {return is_shown_injured;};
    void SetShownInjured(bool x) {is_shown_injured = x;};
private:
    float x_val; // khoang cach giua 2 vi tri
    float y_val;

    vector <Bullet*> bullet_list;
    SDL_Rect frame_idle[10];
    SDL_Rect frame_injured[10];

    int cat_w;
    int cat_h;

    int frame_ = 0;
    int frame_injured_;
    int count_injured_times = 0;
    bool is_shown_injured = false;

};

#endif // CAT_H_INCLUDED
