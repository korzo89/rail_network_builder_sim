#ifndef GUI_CANVAS_H
#define GUI_CANVAS_H

//--------------------------------------------------------------------------------

#include "GUI_Widget.h"
#include "GUI_Window.h"

//--------------------------------------------------------------------------------

// wigdet z polem do rysowania
class GUI_Canvas : public GUI_Widget
{
public:

   SDL_Surface *view; // powierchnia do rysowania

   GUI_Canvas(int _x, int _y, int _width, int _height, SDL_Surface *_theme);
   ~GUI_Canvas(void);

   // renderowanie widgetu
   virtual void Render(SDL_Surface *dest);
};

//--------------------------------------------------------------------------------

#endif