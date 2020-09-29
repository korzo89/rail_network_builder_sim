#ifndef APP_BUILDWINDOW_H
#define APP_BUILDWINDOW_H

//--------------------------------------------------------------------------------

#include "GUI.h"
#include "GFX_SpriteManager.h"
#include "GFX_SpriteNames.h"

//--------------------------------------------------------------------------------

class APP_BuildWindow : public GUI_Window
{
protected:

   GUI_ImageButton *tbtns[9];

public:

   APP_BuildWindow(int x, int y, SDL_Surface *_theme, TTF_Font *_font, GFX_SpriteManager *_mng);
   virtual ~APP_BuildWindow();

   void AddButtonCallbacks(GUI_ButtonCallback _callback, void *_param);
};

//--------------------------------------------------------------------------------

#endif