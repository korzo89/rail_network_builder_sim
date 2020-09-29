#ifndef GAM_TRAIN_H
#define GAM_TRAIN_H

//--------------------------------------------------------------------------------

#include "GAM_Map.h"
#include "GAM_TrainCar.h"
#include <math.h>

//--------------------------------------------------------------------------------

enum GAM_TrainState { TRAIN_STOPPED = 0, TRAIN_TRAVEL = 1, TRAIN_ON_STATION = 2, TRAIN_WAITING = 3 };

//--------------------------------------------------------------------------------

// klasa pociagu
class GAM_Train
{
private:

   std::vector<GAM_TrainCar*> cars; // lista wagonow
   std::vector<GAM_TrainCar*>::iterator iter;

   std::vector<GAM_MapTile*> path; // sciezka pociagu
   unsigned currStep; // aktualny krok na sciezce

   GAM_TrainState state;
   int waitCount;
   
   int maxSpeed; // maksymalna predkosc pociagu
   int speed; // aktualna predkosc pociagu
   int length; // ilosc wagonow
   int dist; // odleglosc miedzy wagonami
   bool horiz; // poczatkowe ulozenie pociagu
   bool firstPass;

   int tSize; // rozmiar pola mapy

   int sprite; // sprite lokomotywy

   GAM_Map *map; // mapa

   // ustawienie nowego kierunku zgodnie ze sciezka
   int NewDir(int px, int py, int xx, int yy, int nx, int ny);

public:

   GAM_Train(int _sprite, int _x, int _y, int _length, int _speed, GAM_Map *_map, int _tSize, bool _horiz, int _dist = 24);
   ~GAM_Train();

   // ustawienie sciezki
   void SetPath(std::vector<GAM_MapTile*> _path);

   // aktualizacja pozycji pociagu
   void Update();
};

//--------------------------------------------------------------------------------

#endif