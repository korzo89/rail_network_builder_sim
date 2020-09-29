#ifndef GUI_TOGGLELIST_H
#define GUI_TOGGLELIST_H

//--------------------------------------------------------------------------------

#include "GUI_ToggleButton.h"
#include <vector>

//--------------------------------------------------------------------------------

void ToggleButtonCallback(GUI_Button *target, void *param);

//--------------------------------------------------------------------------------

class GUI_ToggleList : public GUI_Widget
{
protected:

   std::vector<GUI_ToggleButton*> btns;

   unsigned int selected;

public:

   GUI_ToggleList(int _x, int _y, SDL_Surface *_theme, TTF_Font *_font, unsigned int _num, unsigned int _sel = 0, bool _horiz = false, int _space = 2);
   ~GUI_ToggleList();

   virtual void ProcessEvent(SDL_Event *event);

   virtual void Render(SDL_Surface *dest);

   virtual void SetParent(GUI_Window *par);

   unsigned int GetSelection();

   void SetSelection(unsigned int num);
};

//--------------------------------------------------------------------------------

#endif