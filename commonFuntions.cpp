#include "CommonFuntions.h"

SDL_Texture* CommonFunc::LoadImage(std::string path, SDL_Renderer* ren)
{
    SDL_Texture* newTexture = nullptr;
    SDL_Surface* loadSurface = IMG_Load(path.c_str());
    if (loadSurface == nullptr) {
        cout << "Fail to load image" << endl;
    } else
    {
        newTexture = SDL_CreateTextureFromSurface(ren, loadSurface);
        if (newTexture == nullptr)
            cout << "Fail to load image" << endl;
        SDL_FreeSurface(loadSurface);
    }
    return newTexture;
}

void CommonFunc::ApplySurface(SDL_Renderer* renderer, SDL_Texture* src, int x, int y, int w, int h)
{
    SDL_Rect obj;
    obj.x = x;
    obj.y = y;
    obj.w = w;
    obj.h = h;
    SDL_RenderCopy(renderer, src, NULL, &obj);
    SDL_RenderPresent(renderer);
}
void CommonFunc::CleanUp() {
	SDL_DestroyWindow(g_window);
	SDL_DestroyRenderer(g_screen);
	SDL_Quit();
}
