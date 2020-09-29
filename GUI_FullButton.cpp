#include "GUI_FullButton.h"

//--------------------------------------------------------------------------------

GUI_FullButton::GUI_FullButton(int _x, int _y, int _width, int _height, SDL_Surface *_theme, TTF_Font *_font, SDL_Color _color, std::string _str, GFX_SpriteManager *_mng, int _icon, int _iconSize)
   : GUI_Button(_x, _y, _width, _height, _theme)
{
   sprMng = _mng;
   icon = _icon;
   iconSize = _iconSize;

   font = _font;
   color = _color;
   txtSurface = NULL;

   SetText(_str);
}

//--------------------------------------------------------------------------------

GUI_FullButton::~GUI_FullButton(void)
{
   SDL_FreeSurface(txtSurface);
}

//--------------------------------------------------------------------------------

void GUI_FullButton::Render(SDL_Surface *dest)
{
   SDL_Rect offset;

   offset.x = x;
   offset.y = y;
   SDL_BlitSurface(clicked ? container2 : container, &(container->clip_rect), dest, &offset);

   int ww = (txtSurface->clip_rect.w + iconSize)/2;
   int hh = txtSurface->clip_rect.h/2;
   offset.x = x+width/2-ww+iconSize+(clicked ? 1 : 0);
   offset.y = y+height/2-hh+(clicked ? 1 : 0);
   SDL_BlitSurface(txtSurface, &(txtSurface->clip_rect), dest, &offset);

   sprMng->DrawSprite(icon, offset.x-iconSize, y+4+(clicked ? 1 : 0), dest);
}

//--------------------------------------------------------------------------------

void GUI_FullButton::SetText(std::string str)
{
   text = str;

   if(NULL != txtSurface)
      SDL_FreeSurface(txtSurface);
   txtSurface = TTF_RenderText_Solid(font, text.c_str(), color);
}

//--------------------------------------------------------------------------------

void GUI_FullButton::SetColor(SDL_Color _color)
{
   color = _color;

   if(NULL != txtSurface)
      SDL_FreeSurface(txtSurface);
   txtSurface = TTF_RenderText_Solid(font, text.c_str(), color);
}
