#include "GUI_ImageButton.h"

//--------------------------------------------------------------------------------

GUI_ImageButton::GUI_ImageButton(int _x, int _y, int _width, int _height, SDL_Surface *_theme, GFX_SpriteManager *_mng, int _icon)
   : GUI_Button(_x, _y, _width, _height, _theme)
{
   sprMng = _mng;
   icon = _icon;
}

//--------------------------------------------------------------------------------

GUI_ImageButton::~GUI_ImageButton(void)
{
   
}

//--------------------------------------------------------------------------------

void GUI_ImageButton::Render(SDL_Surface *dest)
{
   GUI_Button::Render(dest);

    int offset = 4+(clicked ? 1 : 0);
    sprMng->DrawSprite(icon, x+offset, y+offset, dest);
}
