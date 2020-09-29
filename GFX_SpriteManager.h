#ifndef GFX_SPRITEMANAGER_H
#define GFX_SPRITEMANAGER_H

//--------------------------------------------------------------------------------

#include <string>
#include <vector>
#include <fstream>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_tools.h"

//--------------------------------------------------------------------------------

// klasa sprite'a
class GFX_Sprite
{
public:

   SDL_Rect clipRect; // obszar grafiki
   int ox; // offset x
   int oy; // offset y
};

//--------------------------------------------------------------------------------

// manager sprite'ow
class GFX_SpriteManager
{
private:

   std::vector<GFX_Sprite> sprites; // wektor sprite'ow

   SDL_Surface *gfx; // powierzchnia z grafika

public:

   GFX_SpriteManager(void);
   ~GFX_SpriteManager(void);

   // zaladowanie grafiki z pliku
   bool Load(std::string src);

   // rysowanie sprite'a na powierzchni na okreslonej pozycji
   bool DrawSprite(int id, int x, int y, SDL_Surface *dest);

   // ilosc sprite'ow managera
   int NumSprites(void) const;
};

//--------------------------------------------------------------------------------

#endif