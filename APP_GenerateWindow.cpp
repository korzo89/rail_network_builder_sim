#include "APP_GenerateWindow.h"

//--------------------------------------------------------------------------------

APP_GenerateWindow::APP_GenerateWindow(int x, int y, SDL_Surface *_theme, TTF_Font *_font)
   : GUI_Window(x, y, 180, 190, "Map generator", _theme, _font, true, false)
{
   SDL_Color cBlack = ColorRGB(0x00, 0x00, 0x00);
   SDL_Color cGrey = ColorRGB(0xcf, 0xcf, 0xcf);

   sizeLbl = new GUI_ShadowedTextField(16, 24, 63, 10, _font, cBlack, cGrey, "Map size");
   AddChild(sizeLbl);

   sizeNum = new GUI_Numeric(90, 20, 70, 18, _theme, _font, 50, 300, 200, 10);
   AddChild(sizeNum);
   
   landLbl = new GUI_ShadowedTextField(16, 50, 142, 10, _font, cBlack, cGrey, "Landscape density:");
   AddChild(landLbl);

   cityLbl = new GUI_TextField(35, 70, 50, 10, _font, cBlack, "Cities");
   AddChild(cityLbl);

   cityNum = new GUI_Numeric(90, 66, 70, 18, _theme, _font, 0, 100, 10, 10);
   AddChild(cityNum);

   treeLbl = new GUI_TextField(27, 90, 60, 10, _font, cBlack, "Forests");
   AddChild(treeLbl);

   treeNum = new GUI_Numeric(90, 86, 70, 18, _theme, _font, 0, 100, 10, 10);
   AddChild(treeNum);

   waterLbl = new GUI_TextField(43, 110, 50, 10, _font, cBlack, "Water");
   AddChild(waterLbl);

   waterNum = new GUI_Numeric(90, 106, 70, 18, _theme, _font, 0, 100, 10, 10);
   AddChild(waterNum);

   rockLbl = new GUI_TextField(43, 130, 50, 10, _font, cBlack, "Rocks");
   AddChild(rockLbl);

   rockNum = new GUI_Numeric(90, 126, 70, 18, _theme, _font, 0, 100, 10, 10);
   AddChild(rockNum);

   genBtn = new GUI_TextButton(32, 157, 115, 25, _theme, _font, cBlack, "GENERATE MAP");
   AddChild(genBtn);
}

//--------------------------------------------------------------------------------

APP_GenerateWindow::~APP_GenerateWindow()
{
   delete sizeLbl;
   sizeLbl = NULL;

   delete landLbl;
   landLbl = NULL;

   delete cityLbl;
   cityLbl = NULL;

   delete treeLbl;
   treeLbl = NULL;

   delete waterLbl;
   waterLbl = NULL;

   delete rockLbl;
   rockLbl = NULL;

   delete sizeNum;
   sizeNum = NULL;

   delete cityNum;
   cityNum = NULL;

   delete treeNum;
   treeNum = NULL;

   delete waterNum;
   waterNum = NULL;

   delete rockNum;
   rockNum = NULL;

   delete genBtn;
   genBtn = NULL;
}