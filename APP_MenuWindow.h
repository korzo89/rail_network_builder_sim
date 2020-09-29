#ifndef APP_MENUWINDOW_H
#define APP_MENUWINDOW_H

//--------------------------------------------------------------------------------

#include "GUI.h"
#include "GFX_SpriteManager.h"
#include "GFX_SpriteNames.h"

//--------------------------------------------------------------------------------

#define MENU_BUILD   0
#define MENU_AUTO    1
#define MENU_STATION 2
#define MENU_TRAIN   3
#define MENU_INFO    4
#define MENU_EXIT    5

//--------------------------------------------------------------------------------

class APP_MenuWindow : public GUI_Window
{
public:

   GUI_ImageButton *buildBtn;
   GUI_ImageButton *autoBtn;
   GUI_ImageButton *stationBtn;
   GUI_ImageButton *trainBtn;
   GUI_ImageButton *infoBtn;
   GUI_ImageButton *exitBtn;

   APP_MenuWindow(int x, int y, SDL_Surface *_theme, TTF_Font *_font, GFX_SpriteManager *_mng);
   virtual ~APP_MenuWindow();

   void AddMenuCallbacks(GUI_ButtonCallback funct, void *param);
};

//--------------------------------------------------------------------------------

#endif