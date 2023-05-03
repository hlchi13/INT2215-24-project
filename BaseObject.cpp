#include "BaseObject.h"

BaseObject::BaseObject()
{
	rect_.x = 0;
	rect_.y = 0;
	p_object = NULL;

}

BaseObject::~BaseObject()
{
    Free();
}

bool BaseObject::LoadImg(std::string path, SDL_Renderer* screen){
    Free();
	SDL_Texture* new_texture = NULL;

	SDL_Surface* load_surface = IMG_Load(path.c_str());
	if (load_surface == NULL) {
        cout << "Unable to load image " << path << " SDL_image Error: " << IMG_GetError();
        return false;
	}
	{
		new_texture = SDL_CreateTextureFromSurface(screen, load_surface);
		if (new_texture == NULL)
		{
		    cout << "Unable to create texture from " << path << " SDL Error: " << SDL_GetError();
			return false;
		}
		SDL_FreeSurface(load_surface);
	}
	p_object = new_texture;

	return p_object != NULL;
}

void BaseObject::Free() {
    if (p_object != NULL)
    {
        SDL_DestroyTexture(p_object);
        p_object = NULL;
        rect_.w = 0;
        rect_.h = 0;
    }
}

void BaseObject::Show(SDL_Renderer* src)
{
    SDL_RenderCopy(src, p_object, NULL, &rect_);
}
