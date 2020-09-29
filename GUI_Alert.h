#ifndef GUI_ALERT_H
#define GUI_ALERT_H

//--------------------------------------------------------------------------------

#include "GUI_Window.h"
#include "GUI_TextButton.h"
#include <vector>

//--------------------------------------------------------------------------------

// rodzaj wyrownania tekstu alertu
enum GUI_TextAlign { AL_LEFT = 0, AL_CENTER = 1, AL_RIGHT = 2 };

//--------------------------------------------------------------------------------

// alert
class GUI_Alert : public GUI_Window
{
private:

   GUI_Button *okBtn; // przycisk OK

public:

   bool marked; // flaga oznaczenia alertu do usuniecia

   GUI_Alert(int _x, int _y, std::string _title, std::string _message, SDL_Surface *_theme, TTF_Font *_font, GUI_TextAlign _align = AL_LEFT);
   ~GUI_Alert(void);

   // ustawienie callbacku zamkniecia alertu
   void AddCallback(GUI_ButtonCallback _callback, void *_param);

};

//--------------------------------------------------------------------------------

#endif