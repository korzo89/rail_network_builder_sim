#ifndef GUI_FULLBUTTON_H
#define GUI_FULLBUTTON_H

//--------------------------------------------------------------------------------

#include <string>
#include "GUI_Button.h"
#include "GFX_SpriteManager.h"
#include "SDL_ttf.h"

//--------------------------------------------------------------------------------

// przycisk z obrazkiem
class GUI_FullButton : public GUI_Button
{
protected:

   int icon; // id sprite na przycisku
   int iconSize;
   GFX_SpriteManager *sprMng; // manager sprite'ow

   TTF_Font *font; // czcionka
   SDL_Color color; // kolor tekstu
   SDL_Surface *txtSurface; // powierzchnia tekstu
   std::string text; // tekst

public:

   GUI_FullButton(int _x, int _y, int _width, int _height, SDL_Surface *_theme, TTF_Font *_font, SDL_Color _color, std::string _str, GFX_SpriteManager *_mng, int _icon, int _iconSize);
   virtual ~GUI_FullButton(void);

   // renderowanie widgetu
   virtual void Render(SDL_Surface *dest);

   // ustawienie tekstu
   void SetText(std::string str);

   // ustawienie koloru tekstu
   void SetColor(SDL_Color _color);
};

//--------------------------------------------------------------------------------

#endif