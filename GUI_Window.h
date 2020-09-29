#ifndef GUI_WINDOW_H
#define GUI_WINDOW_H

//--------------------------------------------------------------------------------

#include <string>
#include <list>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_tools.h"
#include "GUI_Widget.h"

//--------------------------------------------------------------------------------

// typ pozycji elementow w grafice motywu
enum GUI_WindowRectID { WND_TL = 0, WND_TC = 1, WND_TR = 2, WND_CL = 3, WND_CC = 4, WND_CR = 5, WND_BL = 6, WND_BC = 7, WND_BR = 8, WND_CLOSEBTN = 9,
   WND_LBAR = 10, WND_CBAR = 11, WND_RBAR = 12, WND_TL2 = 13, WND_TC2 = 14, WND_TR2 = 15, WND_CL2 = 16, WND_CC2 = 17, WND_CR2 = 18, WND_BL2 = 19, WND_BC2 = 20, WND_BR2 = 21,
   WND_CLOSEBTN2 = 22, WND_LBAR2 = 23, WND_CBAR2 = 24, WND_RBAR2 = 25, NOT_L = 26, NOT_C = 27, NOT_R = 28, NOT_L2 = 29, NOT_C2 = 30, NOT_R2 = 31 };

// rodzaj klikniecia okna
enum GUI_WindowBound { BND_NONE = 0, BND_TITLEBAR = 1, BND_ALL = 2, BND_CLOSE = 3 };

//--------------------------------------------------------------------------------

// klasa obszarow elementow okna
class GUI_WindowRects
{
private:

   SDL_Rect rects[32]; // obszary na grafice motywu

public:

   GUI_WindowRects(void);

   // pobranie danego obszaru
   SDL_Rect* GetRect(GUI_WindowRectID id);
};

//--------------------------------------------------------------------------------

// typ wskaznika na callback okna
typedef void (*GUI_WindowCallback)(GUI_Window *target, void *param);

//--------------------------------------------------------------------------------

// klasa okna
class GUI_Window
{
protected:

   SDL_Surface *container; // kontener grafiki okna
   SDL_Surface *background; // tlo okna
   SDL_Surface *text; // powierzchnia z tekstem tytulu
   SDL_Surface *closeBtn; // przycisk zamkniecia okna

   TTF_Font *font; // czczionka tekstow okna

   bool showBar; // flaga pokazania paska tytulowego
   bool showClose; // flaga pokazywania przycisku zamkniecia
   bool draggable; // flaga przesuwalnosci okna

   bool focus; // flaga aktywnosci okna
   bool closeClicked; // flaga przycisniecia przycisku zamkniecia

   GUI_WindowCallback callback;
   void *param;

   std::string title; // tytul okna

   std::list<GUI_Widget*> displayList; // lista dzieci okna
   std::list<GUI_Widget*>::iterator it;

   // utworzenie tla okna
   void MakeBackground(SDL_Surface *_theme);

public:

   int x;
   int y;
   int width;
   int height;
   bool visible; // flaga aktywnosci okna

   GUI_Window(int _x, int _y, int _width, int _height, std::string _title, SDL_Surface *_theme, TTF_Font *_font, bool _showBar = true, bool _showClose = true, bool _draggable = true);
   GUI_Window(int _x, int _y, std::string _title, SDL_Surface *_theme, TTF_Font *_font, bool _showBar = true, bool _showClose = true, bool _draggable = true);
   virtual ~GUI_Window(void);

   // renderowanie okna
   void Render(SDL_Surface *dest);

   // sprawdzenie czy dana pozycja znajduje sie o obszarze okna
   GUI_WindowBound CheckBounds(int cx, int cy);

   // przetworzenie zdarzenia
   void ProcessEvent(SDL_Event *event);

   // ustawienie pozycji okna
   void SetPosition(int dx, int dy);

   // dodanie elementu do okna
   void AddChild(GUI_Widget *child);

   // sprawdzenie aktywnosci okna
   bool GetFocus(void) const;

   // ustawienie aktywnosci okna
   void SetFocus(bool _focus);

   void AddCloseCallback(GUI_WindowCallback _callback, void *_param);
};

//--------------------------------------------------------------------------------

#endif