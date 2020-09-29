#include "GUI_Image.h"

//--------------------------------------------------------------------------------

GUI_Image::GUI_Image(int _x, int _y, GFX_SpriteManager *_mng, int _sprite)
   : GUI_Widget(_x, _y, 0, 0)
{
   mng = _mng;
   sprite = _sprite;
}

//--------------------------------------------------------------------------------

GUI_Image::~GUI_Image()
{

}

//--------------------------------------------------------------------------------

void GUI_Image::Render(SDL_Surface *dest)
{
   mng->DrawSprite(sprite, x, y, dest);
}

//--------------------------------------------------------------------------------

void GUI_Image::SetSprite(int _sprite)
{
   sprite = _sprite;
}