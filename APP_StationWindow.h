#ifndef APP_STATIONWINDOW_H
#define APP_STATIONWINDOW_H

//--------------------------------------------------------------------------------

#include "GUI.h"
#include "GFX_SpriteManager.h"
#include "GFX_SpriteNames.h"

//--------------------------------------------------------------------------------

class APP_StationWindow : public GUI_Window
{
protected:

   GUI_ShadowedTextField *tOrient;
   GUI_TextField *tLeft;
   GUI_TextField *tRight;
   GUI_Image *iLeft;
   GUI_Image *iRight;
   GUI_ShadowedTextField *tLength;

public:

   GUI_ToggleList *orientationList;
   GUI_Numeric *lengthNum;
   GUI_TextButton *placeBtn;

   APP_StationWindow(int _x, int _y, SDL_Surface *_theme, TTF_Font *_font, GFX_SpriteManager *_mng);
   virtual ~APP_StationWindow();
};

//--------------------------------------------------------------------------------

#endif