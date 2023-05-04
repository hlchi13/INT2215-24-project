#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <fstream>
#include "CommonFunc.h"
#include "BaseObject.h"
#include "LTexture.h"
#include "Cat.h"
#include "Shark.h"
#include "Bonus.h"
#include "Bullet.h"
#include "GameText.h"
enum Menu {INTRO, HTP, CHOOSE};
enum Gameplay {PLAY, GAMEOVER};
class GameFunctions : public BaseObject
{
public:
    GameFunctions();
    ~GameFunctions();
    bool InitData();
    bool CheckMouse(int &x, int &y, SDL_Rect rect_mouse);
    bool ShowIntro();
    bool LoadBackGround(const int& num);
    void ShowLife();
    void CreateThreatList ();
    void CreateBonusList();
    void GetHighScore();
    void Replay();
    void Run();
    bool ShowEnd();
    void close();

private:
    bool is_quit, running;
    GameText Game_over, textX, Your_Score, High_ScoreText, show_bullet;
    Cat cat_obj;
    Cat heart;

    SDL_Texture* g_background;
    vector<Shark*> SharkList;
    vector<Bonus*> BonusList;
    vector<Bullet*> BulletList;
    GameText Score, number_life, High_Score;// number

    int high_score;
    Menu menu;
    Gameplay game;
    int frameDelay = 1000/FPS;
    Uint32 frameStart;
    int frameTime;

};
#endif // GAME_H_INCLUDED
