#ifndef GUI_IDRAWABLE_H
#define GUI_IDRAWABLE_H

//--------------------------------------------------------------------------------

//#include "GUI_Window.h"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_tools.h"

//--------------------------------------------------------------------------------

class GUI_Window;

//--------------------------------------------------------------------------------

class GUI_IDrawable
{
protected:

   SDL_Surface *container;

   int width;
   int height;

public:

   int x;
   int y;

   GUI_Window *parent;

   GUI_IDrawable(int _x, int _y, int _width, int _height);

   virtual ~GUI_IDrawable(void);

   virtual void ProcessEvent(SDL_Event *event);

   void SetPosition(int dx, int dy);

   virtual void Render(SDL_Surface *dest) = 0;
};

//--------------------------------------------------------------------------------

#endif 
