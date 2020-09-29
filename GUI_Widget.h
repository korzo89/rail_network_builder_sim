#ifndef GUI_WIDGET_H
#define GUI_WIDGET_H

//--------------------------------------------------------------------------------

//#include "GUI_Window.h"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_tools.h"

//--------------------------------------------------------------------------------

class GUI_Window;

//--------------------------------------------------------------------------------

// klasa abstrakcyjna widgetu okna
class GUI_Widget
{
protected:

   SDL_Surface *container; // kontener widgetu

   int width; // szerokosc widgetu
   int height; // wysokosc widgetu

public:

   int x;
   int y;

   GUI_Window *parent; // okno bedace rodzicem widgetu

   GUI_Widget(int _x, int _y, int _width, int _height);
   virtual ~GUI_Widget(void);

   // przetworzenie zdarzenia
   virtual void ProcessEvent(SDL_Event *event);

   // ustawienie pozycji widgetu
   void SetPosition(int dx, int dy);

   // przypisanie rodzica
   virtual void SetParent(GUI_Window *par);

   // renderowanie widgetu
   virtual void Render(SDL_Surface *dest) = 0;
};

//--------------------------------------------------------------------------------

#endif 
