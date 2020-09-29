#include "GUI_Widget.h"

//--------------------------------------------------------------------------------

GUI_Widget::GUI_Widget(int _x, int _y, int _width, int _height)
{
   x = _x;
   y = _y;
   width = _width;
   height = _height;
   parent = NULL;

   container = SDL_CreateRGBSurface(SDL_SWSURFACE, width, height, 32, 0, 0, 0, 0);
}

//--------------------------------------------------------------------------------

GUI_Widget::~GUI_Widget(void)
{
   SDL_FreeSurface(container);
}

//--------------------------------------------------------------------------------

void GUI_Widget::ProcessEvent(SDL_Event *event)
{

}

//--------------------------------------------------------------------------------

void GUI_Widget::SetPosition(int dx, int dy)
{
   x = dx;
   y = dy;
}

//--------------------------------------------------------------------------------

void GUI_Widget::SetParent(GUI_Window *par)
{
   parent = par;
}