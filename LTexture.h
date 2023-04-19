#ifndef LTEXTURE_H_INCLUDED
#define LTEXTURE_H_INCLUDED

#include "CommonFunc.h"

class LTexture
{
public:
    LTexture(SDL_Renderer* gRenderer, SDL_Rect rect_);
    ~LTexture();
    bool loadFromFile (std::string path);
    void free();
    void setColor( Uint8 red, Uint8 green, Uint8 blue );
    void setAlpha( Uint8 alpha );
    void renderCopy ();
    int getWidth() {return width;};
    int getHeight() {return height;};
private:
    SDL_Texture* gTexture;
    SDL_Renderer* gRen;
    SDL_Rect rect;
    int width;
    int height;
};

#endif // LTEXTURE_H_INCLUDED
