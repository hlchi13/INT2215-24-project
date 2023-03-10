#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "SDL_utils.h"

using namespace std;

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 600;
const char* WINDOW_TITLE = "Cat and Shark";

SDL_Texture* loadTexture (string path, SDL_Renderer* renderer);

int main(int argc, char* argv[])
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);

    SDL_Texture* background = loadTexture("background.jpg", renderer);
    SDL_RenderCopy(renderer, background, NULL, NULL);

    SDL_RenderPresent(renderer);
    SDL_RenderClear(renderer);

    waitUntilKeyPressed();
    quitSDL(window, renderer);
    return 0;
}
SDL_Texture* loadTexture (string path, SDL_Renderer* renderer)
{
    SDL_Texture* newTexture = nullptr;
    SDL_Surface* loadSurface = IMG_Load(path.c_str());
    if (loadSurface == nullptr) {
        cout << "Fail to load image" << endl;
    } else
    {
        newTexture = SDL_CreateTextureFromSurface(renderer, loadSurface);
        if (newTexture == nullptr)
            cout << "Fail to load image" << endl;
        SDL_FreeSurface(loadSurface);
    }
    return newTexture;
}
