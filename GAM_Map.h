#ifndef GAM_MAP_H
#define GAM_MAP_H

//--------------------------------------------------------------------------------

#include "GFX_SpriteNames.h"
#include "GFX_SpriteManager.h"
#include "GAM_Rect.h"
#include "GAM_Costs.h"
#include "SDL.h"
#include <vector>
#include <list>
#include <algorithm>

//--------------------------------------------------------------------------------

class GAM_Map;

// znak zmiennej (jesli parametr zero jest true, zwraca 0, gdy zmienna jest zerem)
int sign(int num, bool zero = false);

// wyliczenie wspolrzednej x w izometrii
int xiso(int x, int y);

// wyliczenie y w izometrii
int yiso(int x, int y);

// tworzenie losowej plamy terenu typu spottype
void generate_spot(GAM_Map & map, int mapsize, int spotpos_x, int spotpos_y, int spotdiam, int spottype, bool isobject = false, int cost = 0, int randomize = 0);

// automatyczne zapelnianie mapy plamami terenu typu spottype
void autofill(GAM_Map & map, int mapsize, int spotnumber, int minspotdiam, int maxspotdiam, int spottype, bool isobject = false, int cost = 0, int randomize = 0);

void GenerateCities(GAM_Map &map, int mapSize, int numCities);

//--------------------------------------------------------------------------------

// klasa pola mapy
class GAM_MapTile
{
private:

   GAM_Map *map;

public:

   int landType; // typ podloza
   int railType; // typ szyn
   int cost; // koszt pola
   bool hasStation;

   int x; // wspolrzedne pola
   int y;

   bool hasObject; // pole zawiera obiekt
   int highlight; // podswietlenie

   GAM_MapTile(GAM_Map *_map, int _x, int _y, int _land = SPR_GRASS, int _rail = 0, int _cost = COST_GRASS);

   // dodanie szyn do pola
   void AddRail(int _num, bool _station = false);
};

//--------------------------------------------------------------------------------

// klasa obiektu
class GAM_Object
{
protected:

   int tSize; // rozmiar pola

public:

   int sprite; // id sprite'a obiektu
   bool dynamic; // flaga dynamicznosci obiektu (obiekt statyczny jest usuwany aktomatycznie przez mape)
   bool deletable; // flaga mozliwosci usuniecia obiektu wraz z wyczyszczeniem pola
   float x;
   float y;
   int i; // znormalizowane wspolrzedne
   int j;
   int rx; // rzeczywiste wspolrzedne ekranowe
   int ry;

   bool visible;

   bool marked; // flaga oznaczenia do usuniecia

   GAM_Object(int _sprite, int _x, int _y, int _tSize, bool _dynamic = true, bool _deletable = true);

   // ustawienie pozycji obiektu
   void SetPosition(float _x, float _y);

   // deklaracja przyjazni z funkcja porownujaca obiekty
   friend bool CompareObj(GAM_Object *a, GAM_Object *b);
};

// funkcja porownujaca pozycje obiektow przy sortowaniu
bool CompareObj(GAM_Object *a, GAM_Object *b);

// warunek usuniecia obiektu
bool RemoveObjCondition(GAM_Object *obj);

//--------------------------------------------------------------------------------

// klasa mapy
class GAM_Map
{
private:

   int mapSize; // rozmiar mapy
   int sWidth; // szerokosc ekranu
   int sHeight; // wysokosc ekranu
   int cx; // akualna pozycja x mapy
   int cy; // akualna pozycja y mapy

   std::vector<GAM_Object*> objects; // lista obiektow na mapie
   std::vector<GAM_Object*> staticOb; // lista statycznych obiektow
   std::vector<GAM_Object*>::iterator iter;

   GAM_Rect cursor; // obszar kursora
   bool curVisible; // flaga widocznosci kursora

   std::vector<std::vector<GAM_MapTile>> map; // lista pol mapy

   GFX_SpriteManager *sprMng; // manager sprite'ow

public:

   int tWidth; // szerokosc grafiki pola
   int tHeight; // wysokosc grafiki pola

   GAM_Map(int _size, int _sw, int _sh, int _tw, int _th, GFX_SpriteManager *_spr);
   ~GAM_Map(void);

   // przesuniecie mapy
   void MoveMap(int dx, int dy);
    
   // renderowanie mapy do powierzchni dest
   void Render(SDL_Surface *dest);

   // ustawienie powierzchni kursora
   void SetCursor(bool visible, int x, int y, int w = 0, int h = 0);

   // dodanie obszaru z szynami
   void AddRailArea(int type, int x, int y, int w = 0, int h = 0, bool station = false);

   // dodanie obszaru terenu
   void AddLandArea(int type, int x, int y, int w, int h, int cost = 0);

   // wyczyszczenie obszaru
   void ClearArea(int x, int y, int w, int h, bool clearRail = true);

   // pobranie referencji do pojedynczego pola
   GAM_MapTile& Get(int i, int j);

   // pobranie referencji do pojedynczego pola
   GAM_MapTile& operator()(int i, int j);

   // pobranie referencji do rzedu pol
   std::vector<GAM_MapTile>& operator[](int i);

   // dodanie dynamicznego obiektu do mapy
   void AddDynamicObject(GAM_Object *obj);

   // dodanie statycznego obiektu
   void AddStaticObject(int sprite, int x, int y, bool deletable = true, bool center = true, int ox = 0, int oy = 0);

   // usuniecie obiektu z mapy
   void RemoveObject(GAM_Object *obj);

   // sprawdzenie czy znormalizowane wspolrzedne (i,j) znajduja sie w granicach mapy
   bool CheckBounds(int i, int j);
};

//--------------------------------------------------------------------------------

#endif