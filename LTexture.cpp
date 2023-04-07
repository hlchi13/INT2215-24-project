#include "LTexture.h"
#include "CommonFunc.h"

LTexture::LTexture(SDL_Renderer* gRenderer, SDL_Rect rect_)
{
    gTexture = NULL;
    width = 0;
    height = 0;
    gRen = gRenderer;
    rect = rect_;
}

LTexture::~LTexture()
{

}


bool LTexture::loadFile(std::string path)
{
    gTexture = CommonFunc::LoadImage (path, gRen);
    return gTexture!=NULL;
}

void LTexture::renderCopy()
{
    SDL_RenderCopy(gRen, gTexture, NULL, &rect);
}
