#include"GameText.h"
bool GameText::LoadText(TTF_Font *gFont, std::string textureText, SDL_Color textColor, SDL_Renderer *gRenderer )
{
	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
	if( textSurface == NULL )
	{
		cout << "Unable to render text surface! SDL_ttf Error\n";
        TTF_GetError();
	}
	else
	{
		//Create texture from surface pixels
        p_object = SDL_CreateTextureFromSurface( gRenderer, textSurface );
		if( p_object == NULL )
		{
			cout <<  "Unable to create texture from rendered text! SDL Error\n";
			SDL_GetError();
		}
		else
		{
			//Get text dimensions
			rect_.w = textSurface->w;
			rect_.h = textSurface->h;
		}
		//Get rid of old surface
		SDL_FreeSurface(textSurface);
	}

	//Return success
	return p_object != NULL;
}

void GameText::Present(SDL_Renderer *ren)
{
    SDL_RenderCopy(ren,p_object,NULL,&rect_);
}

string GameText::ConvertIntToString(){
    int v = value_ ;
    string stringText ;
    if(v<=0) stringText = '0' ;
    while(v){
        stringText =(char)(v%10+'0') + stringText ;
        v/=10;
    }
    return stringText ;
}

void GameText::ShowNum (TTF_Font *gFont, SDL_Color textColor, SDL_Renderer *gRenderer)
{
    if (LoadText(gFont,ConvertIntToString(),textColor,gRenderer))
    {
        SDL_RenderCopy(gRenderer,p_object,NULL,&rect_);;
    }
}
