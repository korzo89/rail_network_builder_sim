#include "GUI_ShadowedTextField.h"

//--------------------------------------------------------------------------------

GUI_ShadowedTextField::GUI_ShadowedTextField(int _x, int _y, int _width, int _height, TTF_Font *_font, SDL_Color _color, SDL_Color _sColor, std::string _str /* = */ )
   : GUI_TextField(_x, _y, _width, _height, _font, _color, _str)
{
   font = _font;
   color = _color;
   sColor = _sColor;
   txtSurface = NULL;
   shadow = NULL;

   SetText(_str);
}

//--------------------------------------------------------------------------------

GUI_ShadowedTextField::~GUI_ShadowedTextField(void)
{
   SDL_FreeSurface(shadow);
}

//--------------------------------------------------------------------------------

void GUI_ShadowedTextField::SetText(std::string str)
{
   text = str;

   if(NULL != txtSurface)
      SDL_FreeSurface(txtSurface);
   txtSurface = TTF_RenderText_Solid(font, text.c_str(), color);

   if(NULL != shadow)
      SDL_FreeSurface(shadow);
   shadow = TTF_RenderText_Solid(font, text.c_str(), sColor);
}

//--------------------------------------------------------------------------------

void GUI_ShadowedTextField::SetColor(SDL_Color _color, SDL_Color _sColor)
{
   color = _color;
   sColor = _sColor;

   if(NULL != txtSurface)
      SDL_FreeSurface(txtSurface);
   txtSurface = TTF_RenderText_Solid(font, text.c_str(), color);

   if(NULL != shadow)
      SDL_FreeSurface(shadow);
   shadow = TTF_RenderText_Solid(font, text.c_str(), sColor);
}

//--------------------------------------------------------------------------------

void GUI_ShadowedTextField::Render(SDL_Surface *dest)
{
   SDL_Rect offset;
   offset.x = x+1;
   offset.y = y+1;
   
   SDL_BlitSurface(shadow, &(container->clip_rect), dest, &offset);

   offset.x = x;
   offset.y = y;

   SDL_BlitSurface(txtSurface, &(container->clip_rect), dest, &offset);
}
