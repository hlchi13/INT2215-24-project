#ifndef GAMEBASE_H_INCLUDED
#define GAMEBASE_H_INCLUDED

#include "CommonFunc.h"

class BaseObject {

public:
    BaseObject(); // constructor
    ~BaseObject(); // destructor
    bool LoadImg (string path, SDL_Renderer* screen);
    void SetRect (const int& x, const int& y) {rect_.x = x; rect_.y = y;};
    void Render(SDL_Renderer* des, const SDL_Rect* clip);
    SDL_Rect GetRect() { return rect_;	}
	SDL_Texture * GetObject() {  return p_object; }
	void ShowBackground(SDL_Renderer* des);
	void Show(SDL_Renderer* src);
	void Free();

protected:
    SDL_Texture* p_object;
    SDL_Rect rect_;
} ;

#endif // GAMEBASE_H_INCLUDED
