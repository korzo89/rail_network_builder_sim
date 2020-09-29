#include "GUI_IDrawable.h"

//--------------------------------------------------------------------------------

GUI_IDrawable::GUI_IDrawable(int _x, int _y, int _width, int _height)
{
   x = _x;
   y = _y;
   width = _width;
   height = _height;
   parent = NULL;

   container = SDL_CreateRGBSurface(SDL_SWSURFACE, width, height, 32, 0, 0, 0, 0);
}

//--------------------------------------------------------------------------------

GUI_IDrawable::~GUI_IDrawable(void)
{
   SDL_FreeSurface(container);
}

//--------------------------------------------------------------------------------

void GUI_IDrawable::ProcessEvent(SDL_Event *event)
{

}

//--------------------------------------------------------------------------------

void GUI_IDrawable::SetPosition(int dx, int dy)
{
   x = dx;
   y = dy;
}