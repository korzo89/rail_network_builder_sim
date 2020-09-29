#ifndef GUI_IMAGEBUTTON_H
#define GUI_IMAGEBUTTON_H

//--------------------------------------------------------------------------------

#include "GUI_Button.h"
#include "GFX_SpriteManager.h"

//--------------------------------------------------------------------------------

// przycisk z obrazkiem
class GUI_ImageButton : public GUI_Button
{
protected:

   int icon; // id sprite na przycisku
   GFX_SpriteManager *sprMng; // manager sprite'ow

public:

   GUI_ImageButton(int _x, int _y, int _width, int _height, SDL_Surface *_theme, GFX_SpriteManager *_mng, int _icon);
   virtual ~GUI_ImageButton(void);

   // renderowanie widgetu
   virtual void Render(SDL_Surface *dest);
};

//--------------------------------------------------------------------------------

#endif