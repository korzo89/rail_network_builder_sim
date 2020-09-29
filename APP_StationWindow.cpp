#include "APP_StationWindow.h"

//--------------------------------------------------------------------------------

APP_StationWindow::APP_StationWindow(int _x, int _y, SDL_Surface *_theme, TTF_Font *_font, GFX_SpriteManager *_mng)
   : GUI_Window(x, y, 236, 203, "Build stations", _theme, _font)
{
   SDL_Color cBlack = ColorRGB(0x00, 0x00, 0x00);
   SDL_Color cGrey = ColorRGB(0xcf, 0xcf, 0xcf);

   tOrient = new GUI_ShadowedTextField(16, 24, 180, 10, _font, cBlack, cGrey, "Platform orientation:");
   AddChild(tOrient);

   tLeft = new GUI_TextField(64, 109, 40, 10, _font, cBlack, "Left");
   AddChild(tLeft);

   tRight = new GUI_TextField(163, 109, 40, 10, _font, cBlack, "Right");
   AddChild(tRight);

   iLeft = new GUI_Image(28, 44, _mng, IMG_OLEFT);
   AddChild(iLeft);

   iRight = new GUI_Image(131, 44, _mng, IMG_ORIGHT);
   AddChild(iRight);

   orientationList = new GUI_ToggleList(40, 106, _theme, _font, 2, 0, true, 81);
   AddChild(orientationList);

   tLength = new GUI_ShadowedTextField(16, 143, 130, 10, _font, cBlack, cGrey, "Platform length:");
   AddChild(tLength);

   lengthNum = new GUI_Numeric(151, 139, 70, 18, _theme, _font, 3, 10, 6);
   AddChild(lengthNum);

   placeBtn = new GUI_TextButton(60, 169, 117, 25, _theme, _font, cBlack, "Place station");
   AddChild(placeBtn);
}

//--------------------------------------------------------------------------------

APP_StationWindow::~APP_StationWindow()
{
   delete tOrient;
   tOrient = NULL;

   delete tLeft;
   tLeft = NULL;

   delete tRight;
   tRight = NULL;

   delete iLeft;
   iLeft = NULL;

   delete iRight;
   iRight = NULL;

   delete tLength;
   tLength = NULL;

   delete orientationList;
   orientationList = NULL;

   delete lengthNum;
   lengthNum = NULL;

   delete placeBtn;
   placeBtn = NULL;
}