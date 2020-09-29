#ifndef GUI_NUMERIC_H
#define GUI_NUMERIC_H

//--------------------------------------------------------------------------------

#include "GUI_TextButton.h"
#include "SDL_tools.h"
#include <sstream>

//--------------------------------------------------------------------------------

void NumericPlusBtnCallback(GUI_Button *target, void *param);

void NumericMinusBtnCallback(GUI_Button *target, void *param);

void NumericValueBtnCallback(GUI_Button *target, void *param);

//--------------------------------------------------------------------------------

class GUI_Numeric : public GUI_Widget
{
protected:

   int value;
   int defaultValue;
   int maxValue;
   int minValue;
   int step;

   GUI_TextButton *btnPlus;
   GUI_TextButton *btnMinus;
   GUI_TextButton *btnValue;

   std::stringstream str;

public:

   GUI_Numeric(int _x, int _y, int _width, int _height, SDL_Surface *_theme, TTF_Font *_font, int _min = 0, int _max = 100, int _default = 50, int _step = 1);
   virtual ~GUI_Numeric();

   virtual void ProcessEvent(SDL_Event *event);

   virtual void Render(SDL_Surface *dest);

   virtual void SetParent(GUI_Window *par);

   void SetValue(int val);

   int GetValue();

   void StepUp();

   void StepDown();

   void Reset();
};

//--------------------------------------------------------------------------------

#endif