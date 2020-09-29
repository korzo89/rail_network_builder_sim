#ifndef GAM_ASTAR
#define GAM_ASTAR

//--------------------------------------------------------------------------------

#include "GAM_Map.h"

//--------------------------------------------------------------------------------

// punkt sciezki
class GAM_Waypoint
{
public:

   GAM_Waypoint *prev; // poprzedni punkt sciezki
   GAM_MapTile *tile; // pole mapy

   int h; // koszty wyszukiwania
   int g;
   int f;

   GAM_Waypoint(GAM_MapTile *_tile, GAM_Waypoint *_prev = NULL);
};

//--------------------------------------------------------------------------------

// rodzaj algorytmu wyszukiwania
enum GAM_SearchAlgorithm { FND_SHORTEST = 0, FND_CHEAPEST = 1, FND_RAIL = 2 };

//--------------------------------------------------------------------------------

// narzedzie wyszukiwania sciezek
class GAM_AStar
{
private:

   GAM_Map *map; // mapa
   GAM_SearchAlgorithm algorithm; // rodzaj algorytmu wyszukiwania
   bool crossing; // flaga umozliwiajaca przechodzenie przez pola z wybudowanymi torami

   std::vector<GAM_Waypoint*> open; // lista otwartych pol
   std::vector<GAM_Waypoint*> closed; // lista zamknietych pol
   std::vector<GAM_Waypoint*>::iterator it;

   // dodanie pola do otwartych
   void AddToOpen(int x, int y, GAM_Waypoint *prev, int dx, int dy);

   // wyszyszczenie list
   void ClearLists(void);

   // sprawdzenie czy dany ruch jest mozliwy
   bool CanGo(int xp, int yp, int x, int y, int xn, int yn);

   // spradzenie mozliwosci ruchu bez podania poprzedniego pola
   bool CanGoNoPrev(int x, int y, int xn, int yn);

public:

   GAM_AStar(GAM_Map *_map);
   ~GAM_AStar(void);

   // znalezienie sciezki
   std::vector<GAM_MapTile*> FindPath(int x1, int y1, int x2, int y2, GAM_SearchAlgorithm alg, bool cross = true);
};

//--------------------------------------------------------------------------------

#endif