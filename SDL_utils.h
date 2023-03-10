#ifndef SDL_UT_H_INCLUDED
#define SDL_UT_H_INCLUDED

#include <iostream>
#include <SDL.h>

void logSDLError(std::ostream& os, const std::string &msg, bool fatal = false);

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer,
	int screenWidth, int screenHeight, const char* windowTitle) ;

void quitSDL(SDL_Window* window, SDL_Renderer* renderer);

void waitUntilKeyPressed();


#endif // SDL_UT_H_INCLUDED
