#include "GUI_Window.h"

//--------------------------------------------------------------------------------

GUI_WindowRects::GUI_WindowRects(void)
{
   int i, j, k = 0;
   for(i = 0; i < 3; i++)
      for(j = 0; j < 3; j++)
      {
         rects[k].x = j*10;
         rects[k].y = i*10;
         rects[k].w = (j == 1) ? 1 : 10;
         rects[k].h = (i == 1) ? 1 : 10;

         rects[k+13].x = j*10;
         rects[k+13].y = i*10+31;
         rects[k+13].w = (j == 1) ? 1 : 10;
         rects[k+13].h = (i == 1) ? 1 : 10;

         k++;
      }

   rects[9].x = 31;
   rects[9].y = 0;
   rects[9].w = 15;
   rects[9].h = 15;

   rects[10].x = 31;
   rects[10].y = 0;
   rects[10].w = 2;
   rects[10].h = 15;

   rects[11].x = 33;
   rects[11].y = 0;
   rects[11].w = 2;
   rects[11].h = 15;

   rects[12].x = 44;
   rects[12].y = 0;
   rects[12].w = 2;
   rects[12].h = 15;

   rects[22].x = 31;
   rects[22].y = 16;
   rects[22].w = 15;
   rects[22].h = 15;

   rects[23].x = 31;
   rects[23].y = 16;
   rects[23].w = 2;
   rects[23].h = 15;

   rects[24].x = 33;
   rects[24].y = 16;
   rects[24].w = 2;
   rects[24].h = 15;

   rects[25].x = 44;
   rects[25].y = 16;
   rects[25].w = 2;
   rects[25].h = 15;

   rects[26].x = 31;
   rects[26].y = 32;
   rects[26].w = 2;
   rects[26].h = 18;

   rects[27].x = 33;
   rects[27].y = 32;
   rects[27].w = 2;
   rects[27].h = 18;

   rects[28].x = 44;
   rects[28].y = 32;
   rects[28].w = 2;
   rects[28].h = 18;

   rects[29].x = 31;
   rects[29].y = 51;
   rects[29].w = 2;
   rects[29].h = 18;

   rects[30].x = 33;
   rects[30].y = 51;
   rects[30].w = 2;
   rects[30].h = 18;

   rects[31].x = 44;
   rects[31].y = 51;
   rects[31].w = 2;
   rects[31].h = 18;
}

//--------------------------------------------------------------------------------

SDL_Rect* GUI_WindowRects::GetRect(GUI_WindowRectID id)
{
   return &rects[id];
}

//--------------------------------------------------------------------------------

GUI_Window::GUI_Window(int _x, int _y, int _width, int _height, std::string _title, SDL_Surface *_theme, TTF_Font *_font, bool _showBar /* = true */, bool _showClose /* = true */, bool _draggable /* = true */)
{
   x = _x;
   y = _y;
   width = _width;
   height = _height;
   title = _title;
   font = _font;
   focus = false;
   showBar = _showBar;
   showClose = _showClose;
   draggable = _draggable;
   visible = true;
   closeBtn = NULL;
   closeClicked = false;

   MakeBackground(_theme);
}

//--------------------------------------------------------------------------------

GUI_Window::GUI_Window(int _x, int _y, std::string _title, SDL_Surface *_theme, TTF_Font *_font, bool _showBar /* = true */, bool _showClose /* = true */, bool _draggable /* = true */)
{
   x = _x;
   y = _y;
   title = _title;
   font = _font;
   focus = false;
   showBar = _showBar;
   showClose = _showClose;
   draggable = _draggable;
   closeBtn = NULL;
   closeClicked = false;
}

//--------------------------------------------------------------------------------

GUI_Window::~GUI_Window(void)
{
   SDL_FreeSurface(container);
   SDL_FreeSurface(background);
}

//--------------------------------------------------------------------------------

void GUI_Window::MakeBackground(SDL_Surface *_theme)
{
   int i, j;

   background = SDL_CreateRGBSurface(SDL_SWSURFACE, width, height, 32, 0, 0, 0, 0);
   container = SDL_CreateRGBSurface(SDL_SWSURFACE, width, height, 32, 0, 0, 0, 0);

   SDL_Color color = {0x00, 0x00, 0x00};
   text = TTF_RenderText_Solid(font, title.c_str(), color);

   GUI_WindowRects rects;
   SDL_Rect offset;

   offset.x = 0;
   offset.y = 0;
   SDL_BlitSurface(_theme, rects.GetRect(WND_TL), background, &offset);

   offset.x = width-10;
   offset.y = 0;
   SDL_BlitSurface(_theme, rects.GetRect(WND_TR), background, &offset);

   offset.x = 0;
   offset.y = height-10;
   SDL_BlitSurface(_theme, rects.GetRect(WND_BL), background, &offset);

   offset.x = width-10;
   offset.y = height-10;
   SDL_BlitSurface(_theme, rects.GetRect(WND_BR), background, &offset);

   for(i = 10; i < width-10; i++)
   {
      offset.x = i;
      offset.y = 0;
      SDL_BlitSurface(_theme, rects.GetRect(WND_TC), background, &offset);
      offset.y = height-10;
      SDL_BlitSurface(_theme, rects.GetRect(WND_BC), background, &offset);
   }

   for(i = 10; i < height-10; i++)
   {
      offset.y = i;
      offset.x = 0;
      SDL_BlitSurface(_theme, rects.GetRect(WND_CL), background, &offset);
      offset.x = width-10;
      SDL_BlitSurface(_theme, rects.GetRect(WND_CR), background, &offset);
   }

   for(i = 10; i < width-10; i++)
      for(j = 10; j < height-10; j++)
      {
         offset.x = i;
         offset.y = j;
         SDL_BlitSurface(_theme, rects.GetRect(WND_CC), background, &offset);
      }

   offset.y = 0;

   if(showBar)
   {
      offset.x = 0;
      SDL_BlitSurface(_theme, rects.GetRect(WND_LBAR), background, &offset);

      for(i = 2; i < width-2; i++)
      {
         offset.x = i;
         SDL_BlitSurface(_theme, rects.GetRect(WND_CBAR), background, &offset);
      }

      offset.x = width-2;
      SDL_BlitSurface(_theme, rects.GetRect(WND_RBAR), background, &offset);
   }

   if(showClose)
   {
      offset.x = width-15;
      SDL_BlitSurface(_theme, rects.GetRect(WND_CLOSEBTN), background, &offset);

      closeBtn = SDL_CreateRGBSurface(SDL_SWSURFACE, 15, 15, 32, 0, 0, 0, 0);
      SDL_BlitSurface(_theme, rects.GetRect(WND_CLOSEBTN2), closeBtn, NULL);
   }

   offset.x = 4;
   offset.y = 2;
   SDL_BlitSurface(text, NULL, background, &offset);
}

//--------------------------------------------------------------------------------

void GUI_Window::Render(SDL_Surface *dest)
{
   if(!visible)
      return;

   SDL_BlitSurface(background, NULL, container, NULL);

   if(showClose && closeClicked)
      ApplySurface(closeBtn, container, width-15, 0);

   for(it = displayList.begin(); it != displayList.end(); ++it)
      if(NULL != *it)
         (*it)->Render(container);
      
   ApplySurface(container, dest, x, y);
}

//--------------------------------------------------------------------------------

GUI_WindowBound GUI_Window::CheckBounds(int cx, int cy)
{
   if(!visible)
      return BND_NONE;

   if((cx > x) && (cx < x+width) && (cy > y))
      if(showClose && (cx > x+width-15) && (cy < y+15))
         return BND_CLOSE;
      else if(draggable && (cy < y+15))
         return BND_TITLEBAR;
      else if(cy < y+height)
         return BND_ALL;

   return BND_NONE;
}

//--------------------------------------------------------------------------------

void GUI_Window::ProcessEvent(SDL_Event *event)
{
   if(!visible)
      return;

   if(showClose && (event->button.button == SDL_BUTTON_LEFT) && (CheckBounds(event->motion.x, event->motion.y) == BND_CLOSE))
      if(event->type == SDL_MOUSEBUTTONDOWN)
         closeClicked = true;
      else if(event->type == SDL_MOUSEBUTTONUP)
      {
         visible = false;
         callback(this, param);
      }

   if((event->button.button == SDL_BUTTON_LEFT) && (event->type == SDL_MOUSEBUTTONUP))
      closeClicked = false;

   for(it = displayList.begin(); it != displayList.end(); ++it)
      if(NULL != *it)
         (*it)->ProcessEvent(event);
}

//--------------------------------------------------------------------------------

void GUI_Window::SetPosition(int dx, int dy)
{
   x = dx;
   y = dy;
}

//--------------------------------------------------------------------------------

void GUI_Window::AddChild(GUI_Widget *child)
{
   if(NULL != child)
   {
      displayList.push_back(child);
      child->SetParent(this);
   }
}

//--------------------------------------------------------------------------------

bool GUI_Window::GetFocus(void) const
{
   return focus;
}

//--------------------------------------------------------------------------------

void GUI_Window::SetFocus(bool _focus)
{
   focus = _focus;
}

//--------------------------------------------------------------------------------

void GUI_Window::AddCloseCallback(GUI_WindowCallback _callback, void *_param)
{
   if(NULL == _callback)
      return;

   callback = _callback;
   param = _param;
}