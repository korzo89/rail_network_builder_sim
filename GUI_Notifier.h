#ifndef GUI_NOTIFIER_H
#define GUI_NOTIFIER_H

//--------------------------------------------------------------------------------

#include "SDL_tools.h"
#include "GUI_Window.h"
#include "GFX_Tweener.h"

//--------------------------------------------------------------------------------

// powiadomienie
class GUI_NotifierItem : public GFX_TweenListener
{
private:

   SDL_Surface *container; // kontener z grafika

   float x; // pozycja powiadomienia
   float y;
   int ox; // pierwotna pozycja
   int oy;
   int width; // szerokosc powiadomienia
   int timeout; // czas wyswietlania powiadomienia
   int time; // aktualny zliczany czas
   bool hidden; // flaga okreslajaca czy powiadomienie jest aktualnie ukrywane

   GFX_Tween *tweenX; // tween animujacy wspolrzedna x
   GFX_Tween *tweenY; // tween animujacy y
   GFX_Tweener *tweener; // wskaznik do tweenera

public:

   int pos; // aktualna pozycja na liscie powiadomien
   bool marked; // flaga oznaczenia do usuniecia

   GUI_NotifierItem(std::string _text, int _x, int _y, bool _red, int _timeout, GFX_Tweener *_twener, SDL_Surface *_theme, TTF_Font *_font);
   ~GUI_NotifierItem();

   // renderowanie powiadomienia
   void Render(SDL_Surface *dest, int diff);

   // przesuniecie powiadomienia w gore
   void MoveUp();
   
   // schowanie powiadomienia
   void Hide();

   // sprawdzenie czy czas wyswietlania powiadomienia sie zakonczyl
   bool IsTimeout();

   // funkcje obslugujace zdarzenia tweenow
   virtual void OnMotionStart(GFX_Tween *tween);
   virtual void OnMotionFinish(GFX_Tween *tween);
   virtual void OnMotionStep(GFX_Tween *tween);
};

//--------------------------------------------------------------------------------

// generator powiadomien
class GUI_Notifier
{
private:

   std::list<GUI_NotifierItem*> items; // lista powiadomien
   std::list<GUI_NotifierItem*>::iterator iter;

   int x; // pozycja generatora
   int y;
   long prevTime; // czas poprzedniego kroku

   GFX_Tweener *tweener; // tweener animacji
   SDL_Surface *theme; // grafika motywu
   TTF_Font *font; // czcionka tekstow

public:

   GUI_Notifier(int _x, int _y, GFX_Tweener *_tweener, SDL_Surface *_theme, TTF_Font *_font);
   ~GUI_Notifier();

   // inicjalizacja generatora
   void Init(long time);

   // wyswietlenie powiadomienia
   void Notify(std::string text, bool red = false);

   // renderowanie powiadomien
   void Render(SDL_Surface *dest, long time);
};

//--------------------------------------------------------------------------------

#endif