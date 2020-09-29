#ifndef GUI_SHADOWEDTEXTFIELD_H
#define GUI_SHADOWEDTEXTFIELD_H

//--------------------------------------------------------------------------------

#include "GUI_TextField.h"

//--------------------------------------------------------------------------------

class GUI_ShadowedTextField : public GUI_TextField
{
protected:

   SDL_Color sColor;
   SDL_Surface *shadow;

public:

   GUI_ShadowedTextField(int _x, int _y, int _width, int _height, TTF_Font *_font, SDL_Color _color, SDL_Color _sColor, std::string _str = "");
   virtual ~GUI_ShadowedTextField(void);

   // ustawienie tekstu
   virtual void SetText(std::string str);

   // ustawienie koloru tekstu
   void SetColor(SDL_Color _color, SDL_Color _sColor);

   // renderowanie widgetu
   virtual void Render(SDL_Surface *dest);
};

//--------------------------------------------------------------------------------

#endif