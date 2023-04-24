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

class GameFunctions : public BaseObject
{
public:
    bool InitData();
    bool CheckMouse(int &x, int &y, SDL_Rect rect_mouse);
    int ShowIntro();
    int ChooseBackGround();
    bool LoadBackGround(const int& num);
    void GetHighScore();
    void InitEnd();
    void InitLife();
    void ShowLife();
    void CreateThreatList ();
    std::vector<Shark*> MakeThreatList();
    void Run();
    void close();

private:
    int frameDelay = 1000/FPS;
    Uint32 frameStart;
    int frameTime;
    bool is_quit;
    GameText text_g_o, textX, Your_Score, High_ScoreText ;
    Cat cat_obj;
    Cat cat_injured;
    vector<Shark*> SharksList;
    Cat heart;
    Bonus* fish;
    GameText Score, number_life, High_Score;// number

    BaseObject g_background;
    int high_score;

};
#endif // GAME_H_INCLUDED
