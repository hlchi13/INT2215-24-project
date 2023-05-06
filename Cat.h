#ifndef CAT_H_INCLUDED
#define CAT_H_INCLUDED

#include "BaseObject.h"
#include "Bullet.h"
#include "GameText.h"

const int MAX_INJURED_TIMES = 15;
const int MAX_SHOWN_TIMES = 20;
class Cat : public BaseObject
{
public:
    Cat();
    ~Cat();
    void HandleInputAction(SDL_Event event, SDL_Renderer* src, Mix_Chunk* cat_bullet,
                           GameText &Score, GameText &number_life);
    void HandleMove();
    void ShowAnimation(SDL_Renderer* des);
    bool GetShowFoward() {return is_forward;};
    void ShowFor(SDL_Renderer* des);
    void SetBulletList(vector<Bullet*> _bullet_list_){
        bullet_list = _bullet_list_ ;
    }
    void SetWidth(const int w, const int h) {rect_.w = w; rect_.h = h;};
	void ControlBullet(SDL_Renderer* g_renderer);
	vector <Bullet*> GetBulletList() {  return bullet_list; } ;
	void RemoveBullet(const int& idx);
    void set_0_val() {x_val = 0; y_val = 0;};
	bool LoadInjured(string path, SDL_Renderer* ren);
    void ShowInjured(SDL_Renderer* des);
    bool GetShowInjured() {return is_shown_injured;};
    void SetShownInjured(bool x) {is_shown_injured = x;};

private:
    int x_val;
    int y_val;
    vector <Bullet*> bullet_list;
    SDL_Rect frame_idle[10];
    SDL_Rect frame_injured[10];
    SDL_Rect frame_forward[2];
    SDL_Rect frame_backward[4];

    SDL_Texture* injured;
    int frame_;
    int count_injured_times_ = 0;
    int count_times = 0;
    bool is_idle;
    bool is_shown_injured;
    bool is_forward;
    bool is_backward;
    int mouseX, mouseY;
    int preX, preY;

};

#endif // CAT_H_INCLUDED
