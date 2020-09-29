#include "APP_InfoWindow.h"

//--------------------------------------------------------------------------------

APP_InfoWindow::APP_InfoWindow(int x, int y, SDL_Surface *_theme, TTF_Font *_font)
   : GUI_Window(x, y, 120, 80, "Tile info", _theme, _font)
{
   SDL_Color cBlack = ColorRGB(0x00, 0x00, 0x00);

   txt1 = new GUI_TextField(10, 20, 200, 20, _font, cBlack); // pola tekstowe
   AddChild(txt1);
   
   txt2 = new GUI_TextField(10, 40, 200, 20, _font, cBlack);
   AddChild(txt2);
}

//--------------------------------------------------------------------------------

APP_InfoWindow::~APP_InfoWindow()
{
   delete txt1;
   txt1 = NULL;

   delete txt2;
   txt2 = NULL;
}