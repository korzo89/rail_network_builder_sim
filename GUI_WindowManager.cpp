#include "GUI_WindowManager.h"

//--------------------------------------------------------------------------------

void AlertCallback(GUI_Button *target, void *param)
{
   dynamic_cast<GUI_Alert*>(target->parent)->marked = true;
}

//--------------------------------------------------------------------------------

GUI_WindowManager::GUI_WindowManager(void)
{
   theme = NULL;
   font = NULL;
   width = 0;
   height = 0;
   drag = NULL;
   isFocus = false;
}

//--------------------------------------------------------------------------------

GUI_WindowManager::~GUI_WindowManager(void)
{
   for(int i = 0; i < alerts.size(); i++)
   {
      delete alerts[i];
      alerts[i] = NULL;
   }
}

//--------------------------------------------------------------------------------

void GUI_WindowManager::SetDefaults(SDL_Surface *_theme, TTF_Font *_font, int _width, int _height)
{
   theme = _theme;
   font = _font;
   width = _width;
   height = _height;
}

//--------------------------------------------------------------------------------

void GUI_WindowManager::AddWindow(GUI_Window *wnd)
{
   if(NULL != wnd)
   {
      if(displayList.size() > 0)
         displayList.back()->SetFocus(false);

      displayList.push_back(wnd);

      wnd->SetFocus(true);
   }
}

//--------------------------------------------------------------------------------

void GUI_WindowManager::RemoveWindow(GUI_Window *wnd)
{
   for(it = displayList.begin(); it != displayList.end(); ++it)
      if(wnd == *it)
      {
         displayList.erase(it);
         return;
      }
}

//--------------------------------------------------------------------------------

GUI_Alert* GUI_WindowManager::ShowAlert(std::string _title, std::string _message, GUI_TextAlign _align /* = AL_CENTER */, bool _center /* = true */, int _x /* = 0 */, int _y /* = 0 */)
{
   if((NULL == theme) || (NULL == font))
      return NULL;

   GUI_Alert *al = new GUI_Alert(_x, _y, _title, _message, theme, font, _align);
   if(_center)
      al->SetPosition((width-al->width)/2, (height-al->height)/2);
   al->AddCallback(AlertCallback, this);

   AddWindow(al);
   alerts.push_back(al);

   return al;
}

//--------------------------------------------------------------------------------

void GUI_WindowManager::RemoveAlerts(void)
{
   if(alerts.size() == 0)
      return;

   std::vector<GUI_Alert*> als;
   std::vector<GUI_Alert*> mrk;

   int i;

   for(i = 0; i < alerts.size(); i++)
      if(alerts[i]->marked)
         mrk.push_back(alerts[i]);
      else
         als.push_back(alerts[i]);
   alerts = als;

   for(i = 0; i < mrk.size(); i++)
   {
      RemoveWindow(mrk[i]);
      delete mrk[i];
      mrk[i] = NULL;
   }

   if(displayList.size() > 0)
      displayList.back()->SetFocus(true);
}

//--------------------------------------------------------------------------------

void GUI_WindowManager::RenderAll(SDL_Surface *dest)
{
   for(it = displayList.begin(); it != displayList.end(); ++it)
      if(NULL != *it)
         (*it)->Render(dest);
}

//--------------------------------------------------------------------------------

void GUI_WindowManager::ProcessEvent(SDL_Event *event)
{
   switch(event->type)
   {
   case SDL_MOUSEBUTTONDOWN:
      HandleMouseDown(event);
      break;

   case SDL_MOUSEBUTTONUP:
      HandleMouseUp(event);
      break;

   case SDL_MOUSEMOTION:
      HandleMouseMotion(event);
      break;
   }

   for(it = displayList.begin(); it != displayList.end(); ++it)
      if(NULL != *it)
         (*it)->ProcessEvent(event);

   if((event->type == SDL_MOUSEBUTTONUP) && (event->button.button == SDL_BUTTON_LEFT))
      RemoveAlerts();
}

//--------------------------------------------------------------------------------

void GUI_WindowManager::HandleMouseDown(SDL_Event *event)
{
   if(event->button.button != SDL_BUTTON_LEFT)
      return;

   int x = event->button.x;
   int y = event->button.y;

   GUI_Window *focus = NULL;

   for(it = displayList.begin(); it != displayList.end(); ++it)
   {
      if(NULL == *it)
         continue;

      GUI_WindowBound bounds = (*it)->CheckBounds(x, y);
      if((bounds != BND_NONE) && (bounds != BND_CLOSE))
         focus = *it;
   }

   if(NULL != focus)
   {
      FocusWindow(focus);

      isFocus = true;

      if(focus->CheckBounds(x, y) == BND_TITLEBAR)
      {
         drag = focus;
         dragOffset.x = x-focus->x;
         dragOffset.y = y-focus->y;
      }
   }
   else
      isFocus = false;
}

//--------------------------------------------------------------------------------

void GUI_WindowManager::HandleMouseUp(SDL_Event *event)
{
   if(event->button.button == SDL_BUTTON_LEFT)
      drag = NULL;
}

//--------------------------------------------------------------------------------

void GUI_WindowManager::HandleMouseMotion(SDL_Event *event)
{
   if(NULL != drag)
   {
      int xx = event->motion.x-dragOffset.x;
      int yy = event->motion.y-dragOffset.y;

      if(abs(xx) < WND_SNAP)
         xx = 0;
      if(abs(xx+drag->width - width) < WND_SNAP)
         xx = width-drag->width;
      if(abs(yy) < WND_SNAP)
         yy = 0;
      if(abs(yy+drag->height - height) < WND_SNAP)
         yy = height-drag->height;

      drag->SetPosition(xx, yy);
   }
}

//--------------------------------------------------------------------------------

void GUI_WindowManager::FocusWindow(GUI_Window *wnd, bool center /* = false */)
{
   if(NULL == wnd)
      return;
   if(wnd == displayList.back())
      return;

   bool found = false;

   for(it = displayList.begin(); it != displayList.end(); ++it)
      if(wnd == *it)
      {
         found = true;
         break;
      }

   if(!found)
      return;

   if(displayList.size() > 0)
      displayList.back()->SetFocus(false);
   wnd->SetFocus(true);

   displayList.erase(it);
   displayList.push_back(wnd);

   if(center)
      CenterWindow(wnd);
}

//--------------------------------------------------------------------------------

bool GUI_WindowManager::GetFocus(void) const
{
   return isFocus;
}

//--------------------------------------------------------------------------------

void GUI_WindowManager::CenterWindow(GUI_Window *wnd)
{
   if(NULL == wnd)
      return;

   wnd->SetPosition((width - wnd->width)/2, (height - wnd->height)/2);
}