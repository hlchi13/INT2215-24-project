#ifndef LTEXTURE_H_INCLUDED
#define LTEXTURE_H_INCLUDED

#include "CommonFunc.h"
#include "BaseObject.h"
class LTexture
{
public:
    LTexture(SDL_Renderer* gRenderer, SDL_Rect rect_);
    ~LTexture();
    bool loadFromFile (std::string path);
    void free();
    void render ();
private:
    SDL_Texture* gTexture;
    SDL_Renderer* gRen;
    SDL_Rect rect;
    int width;
    int height;
};

#endif // LTEXTURE_H_INCLUDED
