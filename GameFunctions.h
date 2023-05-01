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
    GameFunctions();
    ~GameFunctions();
    bool InitData();
    bool CheckMouse(int &x, int &y, SDL_Rect rect_mouse);
    bool CheckToIncreaseScore(SDL_Rect cat, SDL_Rect shark);
    void ShowIntro();
    int ChooseBackGround();
    bool LoadBackGround(const int& num);
    void InitLife();
    void ShowLife();
    void CreateThreatList ();
    void MakeBonusList();
    void ManageBonusObjectList();
    void GetHighScore();
    void Reset();
    void InitEnd();
    void Run();
    void close();

private:
    bool is_quit, running;
    GameText Game_over, textX, Your_Score, High_ScoreText;
    Cat cat_obj;
    Cat heart;

    vector<Shark*> SharksList;
    vector<Bonus*> BonusList;
    GameText Score, number_life, High_Score;// number

    BaseObject g_background;
    SDL_Texture* background_g;
    int high_score;
    enum Menu {INTRO, HTP, CHOOSE};
    Menu menu_num;

};
#endif // GAME_H_INCLUDED
