#include "APP_BuildWindow.h"

//--------------------------------------------------------------------------------

APP_BuildWindow::APP_BuildWindow(int x, int y, SDL_Surface *_theme, TTF_Font *_font, GFX_SpriteManager *_mng)
   : GUI_Window(x, y, 290, 60, "Build", _theme, _font)
{
   int img[9] = {ICO_CURSOR, ICO_TRACKL, ICO_TRACKR, ICO_TRACKH, ICO_TRACKV, ICO_BOMB, ICO_GRASS, ICO_ROCK, ICO_WATER}; // ikony
   for(int i = 0; i < 9; i++) // utworzenie przyciskow
   {
      tbtns[i] = new GUI_ImageButton(10+i*30+(i > 5 ? 5 : 0), 24, 25, 25, _theme, _mng, img[i]);
      tbtns[i]->data = i-1;
      AddChild(tbtns[i]);
   }
}

//--------------------------------------------------------------------------------

APP_BuildWindow::~APP_BuildWindow()
{
   for(int i = 0; i < 9; i++) // zwolnienie wskaznikow przyciskow
   {
      delete tbtns[i];
      tbtns[i] = NULL;
   }
}

//--------------------------------------------------------------------------------

void APP_BuildWindow::AddButtonCallbacks(GUI_ButtonCallback _callback, void *_param)
{
   for(int i = 0; i < 9; i++)
      tbtns[i]->AddCallback(_callback, _param);
}