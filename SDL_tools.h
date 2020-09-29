#ifndef SDL_TOOLS_H
#define SDL_TOOLS_H

//--------------------------------------------------------------------------------

#include <string>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_framerate.h"

//--------------------------------------------------------------------------------

// ladowanie obrazka z danej sciezki
SDL_Surface* LoadImage(std::string fileName);

//--------------------------------------------------------------------------------

// przerysowanie jednej powierzchni na druga na okreslonej pozycji
void ApplySurface(SDL_Surface *src, SDL_Surface *dest, int x, int y);

//--------------------------------------------------------------------------------

SDL_Color ColorRGB(int r, int g, int b);

//--------------------------------------------------------------------------------

#endif