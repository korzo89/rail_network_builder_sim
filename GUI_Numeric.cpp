#include "GUI_Numeric.h"

//--------------------------------------------------------------------------------

GUI_Numeric::GUI_Numeric(int _x, int _y, int _width, int _height, SDL_Surface *_theme, TTF_Font *_font, int _min /* = 0 */, int _max /* = 100 */, int _default /* = 50 */, int _step /* = 1 */)
   : GUI_Widget(_x, _y, _width, _height)
{
   value = _default;
   defaultValue = _default;
   minValue = _min;
   maxValue = _max;
   step = _step;

   btnPlus = new GUI_TextButton(_x+_width-18, _y, 18, 18, _theme, _font, ColorRGB(0, 0, 0), "+");
   btnPlus->AddCallback(NumericPlusBtnCallback, this);

   btnMinus = new GUI_TextButton(_x, _y, 18, 18, _theme, _font, ColorRGB(0, 0, 0), "-");
   btnMinus->AddCallback(NumericMinusBtnCallback, this);

   str << value;
   btnValue = new GUI_TextButton(_x+17, _y, _width-34, 18, _theme, _font, ColorRGB(0, 0, 0), str.str());
   btnValue->AddCallback(NumericValueBtnCallback, this);
}

//--------------------------------------------------------------------------------

GUI_Numeric::~GUI_Numeric()
{
   delete btnPlus;
   btnPlus = NULL;

   delete btnMinus;
   btnMinus = NULL;

   delete btnValue;
   btnValue = NULL;
}

//--------------------------------------------------------------------------------

void GUI_Numeric::ProcessEvent(SDL_Event *event)
{
   btnPlus->ProcessEvent(event);
   btnMinus->ProcessEvent(event);
   btnValue->ProcessEvent(event);
}

//--------------------------------------------------------------------------------

void GUI_Numeric::Render(SDL_Surface *dest)
{
   btnValue->Render(dest);
   btnPlus->Render(dest);
   btnMinus->Render(dest);
}

//--------------------------------------------------------------------------------

void GUI_Numeric::SetParent(GUI_Window *par)
{
   parent = par;

   btnPlus->SetParent(par);
   btnMinus->SetParent(par);
   btnValue->SetParent(par);
}

//--------------------------------------------------------------------------------

void GUI_Numeric::SetValue(int val)
{
   value = val;
   if(value > maxValue)
      value = maxValue;
   if(value < minValue)
      value = minValue;

   str.str("");
   str << value;
   btnValue->SetText(str.str());
}

//--------------------------------------------------------------------------------

int GUI_Numeric::GetValue()
{
   return value;
}

//--------------------------------------------------------------------------------

void GUI_Numeric::StepUp()
{
   SetValue(value+step);
}

//--------------------------------------------------------------------------------

void GUI_Numeric::StepDown()
{
   SetValue(value-step);
}

//--------------------------------------------------------------------------------

void GUI_Numeric::Reset()
{
   SetValue(defaultValue);
}


//--------------------------------------------------------------------------------

void NumericPlusBtnCallback(GUI_Button *target, void *param)
{
   GUI_Numeric *num = (GUI_Numeric*)param;
   if(NULL != num)
      num->StepUp();
}

void NumericMinusBtnCallback(GUI_Button *target, void *param)
{
   GUI_Numeric *num = (GUI_Numeric*)param;
   if(NULL != num)
      num->StepDown();
}

void NumericValueBtnCallback(GUI_Button *target, void *param)
{
   GUI_Numeric *num = (GUI_Numeric*)param;
   if(NULL != num)
      num->Reset();
}