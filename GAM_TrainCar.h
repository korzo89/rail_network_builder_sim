#ifndef GAM_TRAINCAR_H
#define GAM_TRAINCAR_H

//--------------------------------------------------------------------------------

#include "GAM_Map.h"

//--------------------------------------------------------------------------------

// klasa informacji o ruchu wagonu
class GAM_MoveInfo
{
public:

   int nextDir; // nastepny kierunek
   int x; // pozycja pola
   int y;

   GAM_MoveInfo(int _nd, int _x, int _y);
};

//--------------------------------------------------------------------------------

// klasa wagonu pociagu
class GAM_TrainCar : public GAM_Object
{
private:

   std::list<GAM_MoveInfo> moves; // lista ruchow wagonu

public:

   float speedX; // predkosci wagonu
   float speedY;
   int prevX; // poprzednia znormalizowana pozycja wagonu
   int prevY;
   int dir; // kierunek wagonu

   int baseSprite; // podstawowy sprite grafiki wagonu

   bool locomotive; // flaga okreslajaca czy wagon jest lokomotywa

   GAM_TrainCar(int _sprite, int _x, int _y, bool _loc, int _tSize);

   // ustawienie kierunku ruchu wagonu
   void SetDir(int _dir);

   // dodanie ruchu
   void AddMove(GAM_MoveInfo mv);

   // wyczyszczenie listy ruchow
   void ClearMoves();

   // wykonanie kolejnego ruchu
   void NextMove(int _x, int _y);
};

//--------------------------------------------------------------------------------

#endif