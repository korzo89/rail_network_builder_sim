#include "GUI_Notifier.h"

//--------------------------------------------------------------------------------

GUI_NotifierItem::GUI_NotifierItem(std::string _text, int _x, int _y, bool _red, int _timeout, GFX_Tweener *_tweener, SDL_Surface *_theme, TTF_Font *_font)
{
   x = _x;
   y = _y;
   ox = _x;
   oy = _y;
   tweener = _tweener;
   marked = false;
   time = 0;
   timeout = 1000+_timeout;
   pos = 0;
   hidden = false;

   SDL_Color color;
   color.r = _red ? 0x00 : 0xfb;
   color.g = _red ? 0x00 : 0xea;
   color.b = _red ? 0x00 : 0x78;
   SDL_Surface *text = TTF_RenderText_Solid(_font, _text.c_str(), color);

   int hh;
   TTF_SizeText(_font, _text.c_str(), &width, &hh);
   width += 10;

   tweenX = new GFX_Tween(&x, x, x-width-20, 1000, ELASTIC, EASE_OUT);
   tweener->AddTween(tweenX);
   tweenY = NULL;

   container = SDL_CreateRGBSurface(SDL_SWSURFACE, width+1, 19, 32, 0, 0, 0, 0);

   SDL_Rect rect;
   rect.x = 1;
   rect.y = 1;
   rect.w = width;
   rect.h = 18;
   SDL_FillRect(container, &rect, SDL_MapRGB(container->format, 0x00, 0x00, 0x00));

   GUI_WindowRects rects;
   SDL_Rect offset;

   offset.x = 0;
   offset.y = 0;
   SDL_BlitSurface(_theme, rects.GetRect(_red ? NOT_L2 : NOT_L), container, &offset);

   offset.x = width-2;
   SDL_BlitSurface(_theme, rects.GetRect(_red ? NOT_R2 : NOT_R), container, &offset);

   offset.y = 0;
   for(int i = 2; i < width-2; i++)
   {
      offset.x = i;
      SDL_BlitSurface(_theme, rects.GetRect(_red ? NOT_C2 : NOT_C), container, &offset);
   }

   ApplySurface(text, container, 6, 4);
   SDL_FreeSurface(text);

   color.r = color.g = color.b = _red ? 0xff : 0x00;
   text = TTF_RenderText_Solid(_font, _text.c_str(), color);
   ApplySurface(text, container, 5, 3);
   SDL_FreeSurface(text);
}

//--------------------------------------------------------------------------------

GUI_NotifierItem::~GUI_NotifierItem()
{
   tweener->RemoveTween(tweenX);
   delete tweenX;
   tweenX = NULL;

   tweener->RemoveTween(tweenY);
   delete tweenY;
   tweenY = NULL;

   SDL_FreeSurface(container);
}

//--------------------------------------------------------------------------------

void GUI_NotifierItem::Render(SDL_Surface *dest, int diff)
{
   time += diff;

   ApplySurface(container, dest, x, y);
}

//--------------------------------------------------------------------------------

void GUI_NotifierItem::MoveUp()
{
   pos++;
   tweener->RemoveTween(tweenY);
   delete tweenY;
   tweenY = new GFX_Tween(&y, y, oy+pos*28, 100, LINEAR, EASE_OUT);
   tweener->AddTween(tweenY);
}

//--------------------------------------------------------------------------------

void GUI_NotifierItem::Hide()
{
   if(hidden)
      return;

   hidden = true;
   tweener->RemoveTween(tweenX);
   delete tweenX;
   tweenX = new GFX_Tween(&x, x, ox, 500, BACK, EASE_IN);
   tweenX->AddListener(this);
   tweener->AddTween(tweenX);
}

//--------------------------------------------------------------------------------

bool GUI_NotifierItem::IsTimeout()
{
   return time >= timeout;
}

//--------------------------------------------------------------------------------

void GUI_NotifierItem::OnMotionStart(GFX_Tween *tween)
{
}

//--------------------------------------------------------------------------------

void GUI_NotifierItem::OnMotionFinish(GFX_Tween *tween)
{
   marked = true;
}

//--------------------------------------------------------------------------------

void GUI_NotifierItem::OnMotionStep(GFX_Tween *tween)
{
}

//--------------------------------------------------------------------------------

GUI_Notifier::GUI_Notifier(int _x, int _y, GFX_Tweener *_tweener, SDL_Surface *_theme, TTF_Font *_font)
{
   x = _x;
   y = _y;
   tweener = _tweener;
   theme = _theme;
   font = _font;
}

//--------------------------------------------------------------------------------

GUI_Notifier::~GUI_Notifier()
{
   for(iter = items.begin(); iter != items.end(); ++iter)
   {
      delete (*iter);
      *iter = NULL;
   }
}

//--------------------------------------------------------------------------------

void GUI_Notifier::Init(long time)
{
   prevTime = time;
}

//--------------------------------------------------------------------------------

void GUI_Notifier::Notify(std::string text, bool red /* = false */)
{
   int i = items.size();
   for(iter = items.begin(); iter != items.end(); ++iter)
   {
      (*iter)->MoveUp();
      if((*iter)->pos > 4)
         (*iter)->Hide();
   }

   GUI_NotifierItem *it = new GUI_NotifierItem(text, x+10, y, red, 10000, tweener, theme, font);
   items.push_back(it);
}

//--------------------------------------------------------------------------------

void GUI_Notifier::Render(SDL_Surface *dest, long time)
{
   int diff = time-prevTime;
   prevTime = time;

   GUI_NotifierItem *p;
   iter = items.begin();
   while(iter != items.end())
   {
      p = *iter;
      if(NULL == p)
      {
         ++iter;
         continue;
      }

      p->Render(dest, diff);

      if(p->IsTimeout())
         p->Hide();

      if(p->marked)
      {
         delete *iter;
         *iter = NULL;
         iter = items.erase(iter);
      }
      else
         ++iter;
   }        
}