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
	if (load_surface != NULL)
	{
		new_texture = SDL_CreateTextureFromSurface(screen, load_surface);
		if (new_texture != NULL)
		{
			rect_.w = load_surface->w;
			rect_.h = load_surface->h;
		}
		SDL_FreeSurface(load_surface);
	}
	p_object = new_texture;

	return p_object != NULL;
}

void BaseObject::Render(SDL_Renderer* des, const SDL_Rect* clip)
{
	SDL_Rect renderquad = { rect_.x, rect_.y, rect_.w, rect_.h };
	SDL_RenderCopy(des, p_object, clip, &renderquad);

}
void BaseObject::ShowBackground(SDL_Renderer* des)
{
    rect_background.x = 0;
    rect_background.y = 0;
    rect_background.w = SCREEN_WIDTH;
    rect_background.h = SCREEN_HEIGHT;

    SDL_RenderCopy(des, p_object,NULL, &rect_background);
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
    BaseObject::Render(src, &rect_);
}
