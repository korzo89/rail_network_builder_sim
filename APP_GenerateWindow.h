#ifndef APP_GENERATEWINDOW_H
#define APP_GENERATEWINDOW_H

//--------------------------------------------------------------------------------

#include "GUI.h"

//--------------------------------------------------------------------------------

class APP_GenerateWindow : public GUI_Window
{
protected:

   GUI_ShadowedTextField *sizeLbl;
   GUI_ShadowedTextField *landLbl;
   GUI_TextField *cityLbl;
   GUI_TextField *treeLbl;
   GUI_TextField *waterLbl;
   GUI_TextField *rockLbl;

public:

   GUI_Numeric *sizeNum;
   GUI_Numeric *cityNum;
   GUI_Numeric *treeNum;
   GUI_Numeric *waterNum;
   GUI_Numeric *rockNum;
   GUI_TextButton *genBtn;

   APP_GenerateWindow(int x, int y, SDL_Surface *_theme, TTF_Font *_font);
   virtual ~APP_GenerateWindow();
};

//--------------------------------------------------------------------------------

#endif