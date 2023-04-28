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
    void MakeBonusList();
    void ManageBonusObjectList();
    void Run();
    void close();

private:
    bool is_quit;
    GameText text_g_o, textX, Your_Score, High_ScoreText ;
    Cat cat_obj;
    Cat cat_injured;
    Cat heart;

    vector<Shark*> SharksList;
    vector<Bonus*> BonusObjectList;
    Bonus fish;
    GameText Score, number_life, High_Score;// number

    BaseObject g_background;
    SDL_Texture* background_g;
    int high_score;

};
#endif // GAME_H_INCLUDED
