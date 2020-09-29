#ifndef GUI_VIEWPORT_H
#define GUI_VIEWPORT_H

//--------------------------------------------------------------------------------

#include "GUI_IDrawable.h"
#include "GUI_Window.h"

//--------------------------------------------------------------------------------

class GUI_Viewport : public GUI_IDrawable
{
protected:

   SDL_Surface *view;

public:

   GUI_Viewport(int _x, int _y, int _width, int _height, SDL_Surface *_theme);

   ~GUI_Viewport(void);

   void DrawSurface(SDL_Surface *src, SDL_Rect *rect, int ox = 0, int oy = 0);

   virtual void Render(SDL_Surface *dest);
};

//--------------------------------------------------------------------------------

#endif