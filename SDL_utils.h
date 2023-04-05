#ifndef SDL_UTILS_H_INCLUDED
#define SDL_UTILS_H_INCLUDED

#include "CommonFuntions.h"

void logSDLError(std::ostream& os, const std::string &msg, bool fatal = false);

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer,
	int screenWidth, int screenHeight, const char* windowTitle) ;

void quitSDL(SDL_Window* window, SDL_Renderer* renderer);

void waitUntilKeyPressed();


#endif // SDL_UTILS_H_INCLUDED
