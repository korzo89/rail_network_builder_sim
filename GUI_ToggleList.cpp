#include "GUI_ToggleList.h"

//--------------------------------------------------------------------------------

GUI_ToggleList::GUI_ToggleList(int _x, int _y, SDL_Surface *_theme, TTF_Font *_font, unsigned int _num, unsigned int _sel /* = 0 */, bool _horiz /* = false */, int _space /* = 2 */)
   : GUI_Widget(_x, _y, 0, 0)
{
   selected = _sel;

   for(unsigned int i = 0; i < _num; i++)
   {
      GUI_ToggleButton *btn = new GUI_ToggleButton(_horiz ? x+i*(18+_space) : x, _horiz ? y : y+i*(18+_space), 18, 18, _theme, true);
      btn->data = i;
      btn->AddCallback(ToggleButtonCallback, this);
      if(i == selected)
         btn->SetChecked(true);

      btns.push_back(btn);
   }
}

//--------------------------------------------------------------------------------

GUI_ToggleList::~GUI_ToggleList()
{
   for(unsigned int i = 0; i < btns.size(); i++)
   {
      delete btns[i];
      btns[i] = NULL;
   }
}

//--------------------------------------------------------------------------------

void GUI_ToggleList::ProcessEvent(SDL_Event *event)
{
   for(unsigned int i = 0; i < btns.size(); i++)
      btns[i]->ProcessEvent(event);
}

//--------------------------------------------------------------------------------

void GUI_ToggleList::Render(SDL_Surface *dest)
{
   for(unsigned int i = 0; i < btns.size(); i++)
      btns[i]->Render(dest);
}

//--------------------------------------------------------------------------------

void GUI_ToggleList::SetParent(GUI_Window *par)
{
   for(unsigned int i = 0; i < btns.size(); i++)
      btns[i]->SetParent(par);
}

//--------------------------------------------------------------------------------

unsigned int GUI_ToggleList::GetSelection()
{
   return selected;
}

//--------------------------------------------------------------------------------

void GUI_ToggleList::SetSelection(unsigned int num)
{
   selected = num;

   for(unsigned int i = 0; i < btns.size(); i++)
      btns[i]->SetChecked(i == num);   
}

//--------------------------------------------------------------------------------

void ToggleButtonCallback(GUI_Button *target, void *param)
{
   GUI_ToggleList *list = (GUI_ToggleList*)param;
   if(NULL != list)
      list->SetSelection(target->data);
}