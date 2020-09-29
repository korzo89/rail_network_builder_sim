#include "APP_TrainWindow.h"

//--------------------------------------------------------------------------------

//--------------------------------------------------------------------------------

APP_TrainWindow::APP_TrainWindow(int x, int y, SDL_Surface *_theme, TTF_Font *_font)
   : GUI_Window(x, y, 213, 166, "Build trains", _theme, _font)
{
   SDL_Color cBlack = ColorRGB(0x00, 0x00, 0x00);
   SDL_Color cGrey = ColorRGB(0xcf, 0xcf, 0xcf);
   SDL_Color cWhite = ColorRGB(0xff, 0xff, 0xff);

   tLength = new GUI_ShadowedTextField(16, 24, 110, 10, _font, cBlack, cGrey, "Train length:");
   AddChild(tLength);

   lengthNum = new GUI_Numeric(128, 22, 70, 18, _theme, _font, 2, 30, 10);
   AddChild(lengthNum);

   tInfo = new GUI_ShadowedTextField(16, 52, 100, 10, _font, cBlack, cGrey, "Path info:");
   AddChild(tInfo);

   tDist = new GUI_TextField(16, 75, 80, 10, _font, cBlack, "Distance:");
   AddChild(tDist);

   distanceInfo = new GUI_ShadowedTextField(96, 75, 100, 10, _font, cWhite, cBlack, "0 km");
   AddChild(distanceInfo);

   placeBtn = new GUI_TextButton(53, 102, 105, 25, _theme, _font, cBlack, "Place marker");
   AddChild(placeBtn);

   buildBtn = new GUI_TextButton(56, 131, 99, 25, _theme, _font, cBlack, "Build train");
   AddChild(buildBtn);
}

//--------------------------------------------------------------------------------

APP_TrainWindow::~APP_TrainWindow()
{
   delete tLength;
   tLength = NULL;

   delete lengthNum;
   lengthNum = NULL;

   delete tDist;
   tDist = NULL;

   delete tInfo;
   tInfo = NULL;

   delete distanceInfo;
   distanceInfo = NULL;

   delete placeBtn;
   placeBtn = NULL;

   delete buildBtn;
   buildBtn = NULL;
}