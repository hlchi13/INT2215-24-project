#include "LTexture.h"

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
    free();
}


bool LTexture::loadFromFile(std::string path)
{
    gTexture = CommonFunc::LoadImage (path, gRen);
    return gTexture!=NULL;
}

void LTexture::free()
{
	if( gTexture != NULL )
	{
		SDL_DestroyTexture( gTexture );
		gTexture = NULL;
		width = 0;
		height = 0;
	}
}

void LTexture::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
	SDL_SetTextureColorMod( gTexture, red, green, blue );
}

void LTexture::render()
{
    SDL_RenderCopy(gRen, gTexture,NULL, &rect);
}
