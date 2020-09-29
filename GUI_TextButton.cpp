#include "GUI_TextButton.h"

//--------------------------------------------------------------------------------

GUI_TextButton::GUI_TextButton(int _x, int _y, int _width, int _height, SDL_Surface *_theme, TTF_Font *_font, SDL_Color _color, std::string _str)
   : GUI_Button(_x, _y, _width, _height, _theme)
{
   font = _font;
   color = _color;
   txtSurface = NULL;

   SetText(_str);
}

//--------------------------------------------------------------------------------

GUI_TextButton::~GUI_TextButton(void)
{
   SDL_FreeSurface(txtSurface);
}

//--------------------------------------------------------------------------------

void GUI_TextButton::Render(SDL_Surface *dest)
{
   SDL_Rect offset;

   offset.x = x;
   offset.y = y;
   SDL_BlitSurface(clicked ? container2 : container, &(container->clip_rect), dest, &offset);

   offset.x = x+width/2-txtSurface->clip_rect.w/2+(clicked ? 1 : 0);
   offset.y = y+height/2-txtSurface->clip_rect.h/2+(clicked ? 1 : 0);
   SDL_BlitSurface(txtSurface, &(txtSurface->clip_rect), dest, &offset);
}

//--------------------------------------------------------------------------------

void GUI_TextButton::SetText(std::string str)
{
   text = str;

   if(NULL != txtSurface)
      SDL_FreeSurface(txtSurface);
   txtSurface = TTF_RenderText_Solid(font, text.c_str(), color);
}

//--------------------------------------------------------------------------------

void GUI_TextButton::SetColor(SDL_Color _color)
{
   color = _color;

   if(NULL != txtSurface)
      SDL_FreeSurface(txtSurface);
   txtSurface = TTF_RenderText_Solid(font, text.c_str(), color);
}
