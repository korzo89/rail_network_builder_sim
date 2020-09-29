#ifndef GUI_TOGGLEBUTTON_H
#define GUI_TOGGLEBUTTON_H

//--------------------------------------------------------------------------------

#include "GUI_Button.h"

//--------------------------------------------------------------------------------

// przycisk z przelaczaniem stanu
class GUI_ToggleButton : public GUI_Button
{
protected:

   bool checked; // przycisk zaznaczony

   bool manual;

public:

   GUI_ToggleButton(int _x, int _y, int _width, int _height, SDL_Surface *_theme, bool _man = false);

   // przetworzenie zdarzenia
   virtual void ProcessEvent(SDL_Event *event);

   // renderowanie widgetu
   virtual void Render(SDL_Surface *dest);

   // spradzenie czy przycisk jest zaznaczony
   bool IsChecked(void);

   void SetChecked(bool chk);
};

//--------------------------------------------------------------------------------

#endif