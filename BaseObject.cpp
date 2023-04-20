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

bool BaseObject::LoadImg(string path, SDL_Renderer* screen){
    Free();
	SDL_Texture* new_texture = NULL;

	SDL_Surface* load_surface = IMG_Load(path.c_str());
	if (load_surface == NULL) {
        cout << "fail";
        return false;
	}
	{
		new_texture = SDL_CreateTextureFromSurface(screen, load_surface);
		if (new_texture == NULL)
		{
		    cout << "Fail to load img";
			return false;
		}
		SDL_FreeSurface(load_surface);
	}
	p_object = new_texture;

	return p_object != NULL;
}

void BaseObject::ShowBackground(SDL_Renderer* des)
{
    rect_screen.x = 0;
    rect_screen.y = 0;
    rect_screen.w = SCREEN_WIDTH;
    rect_screen.h = SCREEN_HEIGHT;

    SDL_RenderCopy(des, p_object,NULL, &rect_screen);
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
