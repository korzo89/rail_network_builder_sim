#ifndef GUI_IMAGE_H
#define GUI_IMAGE_H

//--------------------------------------------------------------------------------

#include "GUI_Widget.h"
#include "GFX_SpriteManager.h"

//--------------------------------------------------------------------------------

class GUI_Image : public GUI_Widget
{
protected:

   int sprite;
   GFX_SpriteManager *mng;

public:

   GUI_Image(int _x, int _y, GFX_SpriteManager *_mng, int _sprite);
   virtual ~GUI_Image();

   virtual void Render(SDL_Surface *dest);

   void SetSprite(int _sprite);
};

//--------------------------------------------------------------------------------

#endif