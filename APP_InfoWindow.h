#ifndef APP_INFOWINDOW_H
#define APP_INFOWINDOW_H

//--------------------------------------------------------------------------------

#include "GUI.h"

//--------------------------------------------------------------------------------

class APP_InfoWindow : public GUI_Window
{
public:

   GUI_TextField *txt1;
   GUI_TextField *txt2;

   APP_InfoWindow(int x, int y, SDL_Surface *_theme, TTF_Font *_font);
   virtual ~APP_InfoWindow();
};

//--------------------------------------------------------------------------------

#endif