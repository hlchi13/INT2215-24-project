#ifndef GAMETEXT_H_INCLUDED
#define GAMETEXT_H_INCLUDED

#include "CommonFunc.h"
#include "BaseObject.h"

class GameText: public BaseObject
{
public:
    bool LoadText(TTF_Font *gFont, std::string textureText, SDL_Color textColor, SDL_Renderer *gRenderer); // load text
    void Present( SDL_Renderer *ren); // present any text
    void ShowNum (TTF_Font *gFont, SDL_Color textColor, SDL_Renderer *gRenderer); // only number
    void SetValue(int val) {value_ = val ;} ;
    int GetValue(){return value_ ;} ;
    void IncreaseValue(int x) ;//score va life
private:
    string ConvertIntToString();
    int value_ = 0;
};

#endif // GAMETEXT_H_INCLUDED
