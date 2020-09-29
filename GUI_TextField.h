#ifndef GUI_TEXTFIELD_H
#define GUI_TEXTFIELD_H

//--------------------------------------------------------------------------------

#include <string>
#include "GUI_Widget.h"
#include "SDL_ttf.h"

//--------------------------------------------------------------------------------

// pole tekstowe
class GUI_TextField : public GUI_Widget
{
protected:

   TTF_Font *font; // czcionka
   SDL_Color color; // kolor tekstu
   SDL_Surface *txtSurface; // powierzchnia tekstu
   std::string text; // tekst

public:

   GUI_TextField(int _x, int _y, int _width, int _height, TTF_Font *_font, SDL_Color _color, std::string _str = "");
   virtual ~GUI_TextField(void);

   // ustawienie tekstu
   virtual void SetText(std::string str);

   // ustawienie koloru tekstu
   void SetColor(SDL_Color _color);

   // renderowanie widgetu
   virtual void Render(SDL_Surface *dest);
};

//--------------------------------------------------------------------------------

#endif