#ifndef APP_AUTOBUILDERWINDOW_H
#define APP_AUTOBUILDERWINDOW_H

//--------------------------------------------------------------------------------

#include "GUI.h"

//--------------------------------------------------------------------------------

class APP_AutoBuilderWindow : public GUI_Window
{
protected:

   GUI_ShadowedTextField *tSearch;
   GUI_TextField *tCost;
   GUI_TextField *tDist;
   GUI_TextField *tOmit;
   GUI_ShadowedTextField *tInfo;
   GUI_TextField *tDist2;
   GUI_TextField *tCost2;

public:

   GUI_ToggleList *searchList;
   GUI_ToggleButton *omitBtn;
   GUI_ShadowedTextField *distanceInfo;
   GUI_ShadowedTextField *costInfo;
   GUI_TextButton *placeBtn;
   GUI_TextButton *buildBtn;

   APP_AutoBuilderWindow(int x, int y, SDL_Surface *_theme, TTF_Font *_font);
   virtual ~APP_AutoBuilderWindow();
};

//--------------------------------------------------------------------------------

#endif