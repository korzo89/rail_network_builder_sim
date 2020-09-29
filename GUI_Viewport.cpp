#include "GUI_Viewport.h"

//--------------------------------------------------------------------------------

GUI_Viewport::GUI_Viewport(int _x, int _y, int _width, int _height, SDL_Surface *_theme) : GUI_IDrawable(_x, _y, _width, _height)
{
   view = SDL_CreateRGBSurface(SDL_SWSURFACE, width-4, height-4, 32, 0, 0, 0, 0);

   int i, j;
   GUI_WindowRects rects;
   SDL_Rect offset;

   offset.x = 0;
   offset.y = 0;
   SDL_BlitSurface(_theme, rects.GetRect(WND_TL2), container, &offset);

   offset.x = width-10;
   offset.y = 0;
   SDL_BlitSurface(_theme, rects.GetRect(WND_TR2), container, &offset);

   offset.x = 0;
   offset.y = height-10;
   SDL_BlitSurface(_theme, rects.GetRect(WND_BL2), container, &offset);

   offset.x = width-10;
   offset.y = height-10;
   SDL_BlitSurface(_theme, rects.GetRect(WND_BR2), container, &offset);

   for(i = 10; i < width-10; i++)
   {
      offset.x = i;
      offset.y = 0;
      SDL_BlitSurface(_theme, rects.GetRect(WND_TC2), container, &offset);
      offset.y = height-10;
      SDL_BlitSurface(_theme, rects.GetRect(WND_BC2), container, &offset);
   }

   for(i = 10; i < height-10; i++)
   {
      offset.y = i;
      offset.x = 0;
      SDL_BlitSurface(_theme, rects.GetRect(WND_CL2), container, &offset);
      offset.x = width-10;
      SDL_BlitSurface(_theme, rects.GetRect(WND_CR2), container, &offset);
   }

   for(i = 10; i < width-10; i++)
      for(j = 10; j < height-10; j++)
      {
         offset.x = i;
         offset.y = j;
         SDL_BlitSurface(_theme, rects.GetRect(WND_CC2), container, &offset);
      }
}

//--------------------------------------------------------------------------------

GUI_Viewport::~GUI_Viewport(void)
{
   SDL_FreeSurface(view);
}

//--------------------------------------------------------------------------------

void GUI_Viewport::DrawSurface(SDL_Surface *src, SDL_Rect *rect, int ox, int oy)
{
   if(NULL == src)
      return;

   SDL_Rect offset;
   offset.x = ox;
   offset.y = oy;

   SDL_FillRect(view, &(view->clip_rect), SDL_MapRGB(view->format, 0x00, 0x00, 0x00));
   
   SDL_BlitSurface(src, rect, view, &offset);
}

//--------------------------------------------------------------------------------

void GUI_Viewport::Render(SDL_Surface *dest)
{
   SDL_Rect offset;

   offset.x = x;
   offset.y = y;
   SDL_BlitSurface(container, &(container->clip_rect), dest, &offset);

   offset.x = x+2;
   offset.y = y+2;
   SDL_BlitSurface(view, &(view->clip_rect), dest, &offset);
}