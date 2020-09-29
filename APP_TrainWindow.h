#ifndef APP_TRAINWINDOW_H
#define APP_TRAINWINDOW_H

//--------------------------------------------------------------------------------

#include "GUI.h"

//--------------------------------------------------------------------------------

class APP_TrainWindow : public GUI_Window
{
protected:

   GUI_ShadowedTextField *tLength;
   GUI_ShadowedTextField *tInfo;
   GUI_TextField *tDist;

public:

   GUI_Numeric *lengthNum;
   GUI_ShadowedTextField *distanceInfo;
   GUI_TextButton *placeBtn;
   GUI_TextButton *buildBtn;

   APP_TrainWindow(int x, int y, SDL_Surface *_theme, TTF_Font *_font);
   virtual ~APP_TrainWindow();
};

//--------------------------------------------------------------------------------

#endif