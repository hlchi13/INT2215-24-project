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
    free();
}


bool LTexture::loadFile(std::string path)
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
	//Modulate texture rgb
	SDL_SetTextureColorMod( gTexture, red, green, blue );
}
void LTexture::setAlpha( Uint8 alpha )
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod( gTexture, alpha );
}

void LTexture::renderCopy()
{
    SDL_RenderCopy(gRen, gTexture, NULL, &rect);
}
