#ifndef GUI_TEXTBUTTON_H
#define GUI_TEXTBUTTON_H

//--------------------------------------------------------------------------------

#include <string>
#include "GUI_Button.h"
#include "GUI_Window.h"
#include "SDL_ttf.h"

//--------------------------------------------------------------------------------

// przycisk tekstowy
class GUI_TextButton : public GUI_Button
{
protected:

   TTF_Font *font; // czcionka
   SDL_Color color; // kolor tekstu
   SDL_Surface *txtSurface; // powierzchnia tekstu
   std::string text; // tekst

public:

   GUI_TextButton(int _x, int _y, int _width, int _height, SDL_Surface *_theme, TTF_Font *_font, SDL_Color _color, std::string _str = "");
   virtual ~GUI_TextButton(void);

   // renderowanie widgetu
   virtual void Render(SDL_Surface *dest);

   // ustawienie tekstu
   void SetText(std::string str);

   // ustawienie koloru tekstu
   void SetColor(SDL_Color _color);
};

//--------------------------------------------------------------------------------

#endif