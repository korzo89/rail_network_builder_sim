#include "GUI_Button.h"

//--------------------------------------------------------------------------------

GUI_Button::GUI_Button(int _x, int _y, int _width, int _height, SDL_Surface *_theme)
   : GUI_Widget(_x, _y, _width, _height)
{
   callback = NULL;
   param = NULL;
   clicked = false;
   data = 0;

   container2 = SDL_CreateRGBSurface(SDL_SWSURFACE, width, height, 32, 0, 0, 0, 0);

   int i, j;
   GUI_WindowRects rects;
   SDL_Rect offset;

   offset.x = 0;
   offset.y = 0;
   SDL_BlitSurface(_theme, rects.GetRect(WND_TL), container, &offset);
   SDL_BlitSurface(_theme, rects.GetRect(WND_TL2), container2, &offset);

   offset.x = width-10;
   offset.y = 0;
   SDL_BlitSurface(_theme, rects.GetRect(WND_TR), container, &offset);
   SDL_BlitSurface(_theme, rects.GetRect(WND_TR2), container2, &offset);

   offset.x = 0;
   offset.y = height-10;
   SDL_BlitSurface(_theme, rects.GetRect(WND_BL), container, &offset);
   SDL_BlitSurface(_theme, rects.GetRect(WND_BL2), container2, &offset);

   offset.x = width-10;
   offset.y = height-10;
   SDL_BlitSurface(_theme, rects.GetRect(WND_BR), container, &offset);
   SDL_BlitSurface(_theme, rects.GetRect(WND_BR2), container2, &offset);

   for(i = 10; i < width-10; i++)
   {
      offset.x = i;
      offset.y = 0;
      SDL_BlitSurface(_theme, rects.GetRect(WND_TC), container, &offset);
      SDL_BlitSurface(_theme, rects.GetRect(WND_TC2), container2, &offset);
      offset.y = height-10;
      SDL_BlitSurface(_theme, rects.GetRect(WND_BC), container, &offset);
      SDL_BlitSurface(_theme, rects.GetRect(WND_BC2), container2, &offset);
   }

   for(i = 10; i < height-10; i++)
   {
      offset.y = i;
      offset.x = 0;
      SDL_BlitSurface(_theme, rects.GetRect(WND_CL), container, &offset);
      SDL_BlitSurface(_theme, rects.GetRect(WND_CL2), container2, &offset);
      offset.x = width-10;
      SDL_BlitSurface(_theme, rects.GetRect(WND_CR), container, &offset);
      SDL_BlitSurface(_theme, rects.GetRect(WND_CR2), container2, &offset);
   }

   for(i = 10; i < width-10; i++)
      for(j = 10; j < height-10; j++)
      {
         offset.x = i;
         offset.y = j;
         SDL_BlitSurface(_theme, rects.GetRect(WND_CC), container, &offset);
         SDL_BlitSurface(_theme, rects.GetRect(WND_CC2), container2, &offset);
      }
}

//--------------------------------------------------------------------------------

GUI_Button::~GUI_Button(void)
{
   SDL_FreeSurface(container2);
}

//--------------------------------------------------------------------------------

void GUI_Button::ProcessEvent(SDL_Event *event)
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
            if(clicked && (NULL != callback))
               callback(this, param);
            break;
      }

   if(event->type == SDL_MOUSEBUTTONUP)
      clicked = false;
}

//--------------------------------------------------------------------------------

void GUI_Button::Render(SDL_Surface *dest)
{
   SDL_Rect offset;

   offset.x = x;
   offset.y = y;
   SDL_BlitSurface(clicked ? container2 : container, &(container->clip_rect), dest, &offset);
}

//--------------------------------------------------------------------------------

void GUI_Button::AddCallback(GUI_ButtonCallback _callback, void *_param)
{
   if(NULL == _callback)
      return;

   callback = _callback;
   param = _param;
}
