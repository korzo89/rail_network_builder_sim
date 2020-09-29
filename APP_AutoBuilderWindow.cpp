#include "APP_AutoBuilderWindow.h"

//--------------------------------------------------------------------------------

APP_AutoBuilderWindow::APP_AutoBuilderWindow(int x, int y, SDL_Surface *_theme, TTF_Font *_font)
   : GUI_Window(x, y, 206, 258, "Auto-builder", _theme, _font)
{
   SDL_Color cBlack = ColorRGB(0x00, 0x00, 0x00);
   SDL_Color cGrey = ColorRGB(0xcf, 0xcf, 0xcf);
   SDL_Color cWhite = ColorRGB(0xff, 0xff, 0xff);

   tSearch = new GUI_ShadowedTextField(16, 24, 100, 10, _font, cBlack, cGrey, "Search for:");
   AddChild(tSearch);

   tCost = new GUI_TextField(40, 44, 100, 10, _font, cBlack, "lowest cost");
   AddChild(tCost);

   tDist = new GUI_TextField(40, 64, 150, 10, _font, cBlack, "shortest distance");
   AddChild(tDist);

   searchList = new GUI_ToggleList(16, 40, _theme, _font, 2);
   AddChild(searchList);

   tOmit = new GUI_TextField(40, 94, 152, 10, _font, cBlack, "Avoid existing rail");
   AddChild(tOmit);

   omitBtn = new GUI_ToggleButton(16, 90, 18, 18, _theme);
   AddChild(omitBtn);

   tInfo = new GUI_ShadowedTextField(16, 127, 100, 10, _font, cBlack, cGrey, "Path info:");
   AddChild(tInfo);

   tDist2 = new GUI_TextField(16, 150, 80, 10, _font, cBlack, "Distance:");
   AddChild(tDist2);

   tCost2 = new GUI_TextField(48, 170, 50, 10, _font, cBlack, "Cost:");
   AddChild(tCost2);

   distanceInfo = new GUI_ShadowedTextField(96, 150, 100, 10, _font, cWhite, cBlack, "0 km");
   AddChild(distanceInfo);

   costInfo = new GUI_ShadowedTextField(96, 170, 100, 10, _font, cWhite, cBlack, "0 $");
   AddChild(costInfo);

   placeBtn = new GUI_TextButton(51, 195, 105, 25, _theme, _font, cBlack, "Place marker");
   AddChild(placeBtn);

   buildBtn = new GUI_TextButton(58, 224, 91, 25, _theme, _font, cBlack, "Build path");
   AddChild(buildBtn);
}

//--------------------------------------------------------------------------------

APP_AutoBuilderWindow::~APP_AutoBuilderWindow()
{
   delete tSearch;
   tSearch = NULL;

   delete tCost;
   tCost = NULL;

   delete tDist;
   tDist = NULL;

   delete searchList;
   searchList = NULL;

   delete tOmit;
   tOmit = NULL;

   delete omitBtn;
   omitBtn = NULL;

   delete tInfo;
   tInfo = NULL;

   delete tDist2;
   tDist2 = NULL;

   delete tCost2;
   tCost2 = NULL;

   delete distanceInfo;
   distanceInfo = NULL;

   delete costInfo;
   costInfo = NULL;

   delete placeBtn;
   placeBtn = NULL;

   delete buildBtn;
   buildBtn = NULL;
}