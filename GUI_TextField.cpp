#include "GUI_TextField.h"

//--------------------------------------------------------------------------------

GUI_TextField::GUI_TextField(int _x, int _y, int _width, int _height, TTF_Font *_font, SDL_Color _color, std::string _str) : GUI_Widget(_x, _y, _width, _height)
{
   font = _font;
   color = _color;
   txtSurface = NULL;

   SetText(_str);
}

//--------------------------------------------------------------------------------

GUI_TextField::~GUI_TextField(void)
{
   SDL_FreeSurface(txtSurface);
}

//--------------------------------------------------------------------------------

void GUI_TextField::SetText(std::string str)
{
   text = str;

   if(NULL != txtSurface)
      SDL_FreeSurface(txtSurface);
   txtSurface = TTF_RenderText_Solid(font, text.c_str(), color);
}

//--------------------------------------------------------------------------------

void GUI_TextField::SetColor(SDL_Color _color)
{
   color = _color;

   if(NULL != txtSurface)
      SDL_FreeSurface(txtSurface);
   txtSurface = TTF_RenderText_Solid(font, text.c_str(), color);
}

//--------------------------------------------------------------------------------

void GUI_TextField::Render(SDL_Surface *dest)
{
   SDL_Rect offset;
   offset.x = x;
   offset.y = y;

   SDL_BlitSurface(txtSurface, &(container->clip_rect), dest, &offset);
}
