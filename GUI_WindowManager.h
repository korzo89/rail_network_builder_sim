#ifndef GUI_WINDOWMANAGER_H
#define GUI_WINDOWMANAGER_H

//--------------------------------------------------------------------------------

#include <list>
#include <vector>
#include "SDL.h"
#include "GUI_Window.h"
#include "GUI_Alert.h"

//--------------------------------------------------------------------------------

#define WND_SNAP 10 // odleglosc przyciagania okien do brzegow ekranu

//--------------------------------------------------------------------------------

// callback przyciskow OK w alertach
void AlertCallback(GUI_Button *target, void *param);

//--------------------------------------------------------------------------------

// klasa managera systemu okien
class GUI_WindowManager
{
private:

   std::list<GUI_Window*> displayList; // lista okien
   std::list<GUI_Window*>::iterator it;

   std::vector<GUI_Alert*> alerts; // lista alertow
   std::vector<GUI_Alert*>::iterator ia;

   GUI_Window *drag; // aktualnie przesuwane okno
   SDL_Rect dragOffset; // offset klikniecia przy przesuwaniu

   SDL_Surface *theme; // motyw okien
   TTF_Font *font; // czcionka w oknach
   int width; // szerokosc ekranu
   int height; // wysokosc ekranu
   
   bool isFocus; // flaga aktywnosci dowolnego okna

   // przetworzenie przycisniecia mysza
   void HandleMouseDown(SDL_Event *event);

   // przetworzenie zwolnienia myszy
   void HandleMouseUp(SDL_Event *event);

   // przetworzenie ruchu myszy
   void HandleMouseMotion(SDL_Event *event);

   // usuniecie nieaktywnych alertow
   void RemoveAlerts(void);

public:

   GUI_WindowManager(void);
   ~GUI_WindowManager(void);

   // ustawienie wlasciwosci managera
   void SetDefaults(SDL_Surface *_theme, TTF_Font *_font, int _width, int _height);

   // dodanie okna do managera
   void AddWindow(GUI_Window *wnd);

   // usuniecie okna
   void RemoveWindow(GUI_Window *wnd);

   // utworzenie i pokazanie alertu
   GUI_Alert* ShowAlert(std::string _title, std::string _message, GUI_TextAlign _align = AL_CENTER, bool _center = true, int _x = 0, int _y = 0);

   // renderowanie systemu okien
   void RenderAll(SDL_Surface *dest);

   // przetworzenie zdarzenia
   void ProcessEvent(SDL_Event *event);

   // uaktywnienie okna
   void FocusWindow(GUI_Window *wnd, bool center = false);

   // sprawdzenie aktywnosci dowolnego okna
   bool GetFocus(void) const;

   void CenterWindow(GUI_Window *wnd);
};

//--------------------------------------------------------------------------------

#endif