#include "GUI_ToggleButton.h"

//--------------------------------------------------------------------------------

GUI_ToggleButton::GUI_ToggleButton(int _x, int _y, int _width, int _height, SDL_Surface *_theme, bool _man /* = false */) : GUI_Button(_x, _y, _width, _height, _theme)
{
   checked = false;
   manual = _man;
}

//--------------------------------------------------------------------------------

void GUI_ToggleButton::ProcessEvent(SDL_Event *event)
{
   if(((event->type != SDL_MOUSEBUTTONDOWN) && (event->type != SDL_MOUSEBUTTONUP)) || (event->button.button != SDL_BUTTON_LEFT))
      return;

   int xx = (NULL != parent) ? event->button.x-parent->x : event->button.x;
   int yy = (NULL != parent) ? event->button.y-parent->y : event->button.y;

   if((xx > x) && (xx < x+width) && (yy > y) && (yy < y+height))
      switch(event->type)
      {
      case SDL_MOUSEBUTTONDOWN:
         if((NULL == parent) || (parent->GetFocus()))
            clicked = true;
         break;

      case SDL_MOUSEBUTTONUP:
         if(clicked)
         {
            if(!manual)
               checked = !checked;

            if(NULL != callback)
               callback(this, param);
         }
         break;
      }

   if(event->type == SDL_MOUSEBUTTONUP)
      clicked = false;
}

//--------------------------------------------------------------------------------

void GUI_ToggleButton::Render(SDL_Surface *dest)
{
   SDL_Rect offset;

   offset.x = x;
   offset.y = y;
   SDL_BlitSurface((clicked || checked) ? container2 : container, &(container->clip_rect), dest, &offset);
}

//--------------------------------------------------------------------------------

bool GUI_ToggleButton::IsChecked(void)
{
   return checked;
}

//--------------------------------------------------------------------------------

void GUI_ToggleButton::SetChecked(bool chk)
{
   checked = chk;
}
