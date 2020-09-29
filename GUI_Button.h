#ifndef GUI_BUTTON_H
#define GUI_BUTTON_H

//--------------------------------------------------------------------------------

#include "GUI_Window.h"
#include "SDL_ttf.h"

//--------------------------------------------------------------------------------

class GUI_Button;

// typ wskaznika na callback przycisku
typedef void (*GUI_ButtonCallback)(GUI_Button *target, void *param);

//--------------------------------------------------------------------------------

// przycisk
class GUI_Button : public GUI_Widget
{
protected:

   SDL_Surface *container2; // powierzchnia z grafika wcisnietego przycisku

   GUI_ButtonCallback callback; // callback przycisku
   void *param; // parametr callbacku

   bool clicked; // flaga wcisniecia przycisku

public:

   int data; // dane przycisku

   GUI_Button(int _x, int _y, int _width, int _height, SDL_Surface *_theme);
   virtual ~GUI_Button(void);

   // przetworzenie zdarzenia
   virtual void ProcessEvent(SDL_Event *event);

   // renderowanie widgetu
   virtual void Render(SDL_Surface *dest);

   // ustawienie callbacku przycisku
   void AddCallback(GUI_ButtonCallback _callback, void *_param);
};

//--------------------------------------------------------------------------------

#endif