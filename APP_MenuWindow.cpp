#include "APP_MenuWindow.h"

//--------------------------------------------------------------------------------

APP_MenuWindow::APP_MenuWindow(int x, int y, SDL_Surface *_theme, TTF_Font *_font, GFX_SpriteManager *_mng)
   : GUI_Window(x, y, 225, 60, "Menu", _theme, _font, false, false, false)
{
   SDL_Color cBlack = ColorRGB(0x00, 0x00, 0x00);

   buildBtn = new GUI_ImageButton(10, 24, 25, 25, _theme, _mng, ICO_BUILD);
   buildBtn->data = MENU_BUILD;
   AddChild(buildBtn);

   autoBtn = new GUI_ImageButton(40, 24, 25, 25, _theme, _mng, ICO_AUTO);
   autoBtn->data = MENU_AUTO;
   AddChild(autoBtn);

   stationBtn = new GUI_ImageButton(80, 24, 25, 25, _theme, _mng, ICO_STATION);
   stationBtn->data = MENU_STATION;
   AddChild(stationBtn);

   trainBtn = new GUI_ImageButton(110, 24, 25, 25, _theme, _mng, ICO_TRAIN);
   trainBtn->data = MENU_TRAIN;
   AddChild(trainBtn);

   infoBtn = new GUI_ImageButton(150, 24, 25, 25, _theme, _mng, ICO_INFO);
   infoBtn->data = MENU_INFO;
   AddChild(infoBtn);

   exitBtn = new GUI_ImageButton(190, 24, 25, 25, _theme, _mng, ICO_EXIT);
   exitBtn->data = MENU_EXIT;
   AddChild(exitBtn);
}

//--------------------------------------------------------------------------------

APP_MenuWindow::~APP_MenuWindow()
{
   delete buildBtn;
   buildBtn = NULL;

   delete autoBtn;
   autoBtn = NULL;

   delete stationBtn;
   stationBtn = NULL;

   delete trainBtn;
   trainBtn = NULL;

   delete infoBtn;
   infoBtn = NULL;

   delete exitBtn;
   exitBtn = NULL;
}

//--------------------------------------------------------------------------------

void APP_MenuWindow::AddMenuCallbacks(GUI_ButtonCallback funct, void *param)
{
   buildBtn->AddCallback(funct, param);
   autoBtn->AddCallback(funct, param);
   stationBtn->AddCallback(funct, param);
   trainBtn->AddCallback(funct, param);
   infoBtn->AddCallback(funct, param);
   exitBtn->AddCallback(funct, param);
}