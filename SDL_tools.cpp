#include "SDL_tools.h"

//--------------------------------------------------------------------------------

SDL_Surface* LoadImage(std::string fileName)
{
   SDL_Surface *loaded = NULL;
   SDL_Surface *optimized = NULL;

   loaded = IMG_Load(fileName.c_str());

   if(NULL != loaded)
   {
      optimized = SDL_DisplayFormatAlpha(loaded);

      SDL_FreeSurface(loaded);
   }

   return optimized;
}

//--------------------------------------------------------------------------------

void ApplySurface(SDL_Surface *src, SDL_Surface *dest, int x, int y)
{
   SDL_Rect offset;
   offset.x = x;
   offset.y = y;

   SDL_BlitSurface(src, NULL, dest, &offset);
}

//--------------------------------------------------------------------------------

SDL_Color ColorRGB(int r, int g, int b)
{
   SDL_Color color;
   color.r = r;
   color.b = b;
   color.g = g;

   return color;
}