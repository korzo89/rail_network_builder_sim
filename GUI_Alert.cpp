#include "GUI_Alert.h"

//--------------------------------------------------------------------------------

GUI_Alert::GUI_Alert(int _x, int _y, std::string _title, std::string _message, SDL_Surface *_theme, TTF_Font *_font, GUI_TextAlign _align /* = AL_LEFT */)
   : GUI_Window(_x, _y, _title, _theme, _font, true, false)
{
   marked = false;

   SDL_Color color = {0x00, 0x00, 0x00};

   int lineSkip = TTF_FontLineSkip(font);
   int ww = 0, hh = 0;
   std::vector<std::string> lines;

   int n = 0;
   while(n != -1)
   {
      std::string sub;
      n = _message.find('\n', 0);
      sub = _message.substr(0, n);
      if(n != -1)
         _message = _message.substr(n+1, -1);
      lines.push_back(sub);

      int w = 0;
      TTF_SizeText(font, sub.c_str(), &w, &hh);
      if(w > ww)
         ww = w;
   }

   hh += (lines.size()-1)*lineSkip;

   width = ww+20;
   height = hh+65;

   MakeBackground(_theme);

   okBtn = new GUI_TextButton(width/2-20, height-30, 40, 20, _theme, _font, color, "OK");
   AddChild(okBtn);

   SDL_Surface *temp;
   for(int i = 0; i < lines.size(); i++)
   {
      temp = TTF_RenderText_Solid(font, lines[i].c_str(), color);

      if(NULL == temp)
         continue;

      switch(_align)
      {
      case AL_LEFT:
         ww = 10;
         break;
      case AL_CENTER:
         ww = width/2-temp->clip_rect.w/2;
         break;
      case AL_RIGHT:
         ww = width-10-temp->clip_rect.w;
         break;
      }

      ApplySurface(temp, background, ww, 25+i*lineSkip);
      SDL_FreeSurface(temp);
   }
}

//--------------------------------------------------------------------------------

GUI_Alert::~GUI_Alert(void)
{
   delete okBtn;
   okBtn = NULL;
}

//--------------------------------------------------------------------------------

void GUI_Alert::AddCallback(GUI_ButtonCallback _callback, void *_param)
{
   okBtn->AddCallback(_callback, _param);
}