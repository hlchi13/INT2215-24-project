#include "CommonFunc.h"

SDL_Texture* CommonFunc::LoadImage(std::string path, SDL_Renderer* ren)
{
    SDL_Texture* newTexture = nullptr;
    SDL_Surface* loadSurface = IMG_Load(path.c_str());
    if (loadSurface == nullptr) {
        cout << "Unable to load image " << path << " SDL_image Error: " << IMG_GetError();
    } else
    {
        newTexture = SDL_CreateTextureFromSurface(ren, loadSurface);
        if (newTexture == nullptr)
            cout << "Unable to create texture from " << path << " SDL Error: " << SDL_GetError();
        SDL_FreeSurface(loadSurface);
    }
    return newTexture;
}

void CommonFunc::CleanUp() {
	SDL_DestroyWindow(g_window);
	SDL_DestroyRenderer(g_screen);
	SDL_Quit();
}

bool CommonFunc::CheckCollision(const SDL_Rect &obj1, const SDL_Rect &obj2) // 1 main 2 threat
{
    int left_1 = obj1.x - 9*1.5;
    int right_1 = obj1.x + obj1.w - 8*1.5; // chieu dai that cua vat
    int top_1 = obj1.y - 4*1.5;
    int bot_1 = obj1.y + obj1.h - 8*1.5;

    int left_2 = obj2.x;
    int right_2 = obj2.x + obj2.w;
    int top_2 = obj2.y;
    int bot_2 = obj2.y + obj2.h;

    if (left_1 > right_2 || left_2 > right_1) return false;
    if (top_1 > bot_2 || top_2 > bot_1) return false;
    return true;
}
