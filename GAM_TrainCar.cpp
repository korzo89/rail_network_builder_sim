#include "GAM_TrainCar.h"

//--------------------------------------------------------------------------------

GAM_MoveInfo::GAM_MoveInfo(int _nd, int _x, int _y)
{
   nextDir = _nd;
   x = _x;
   y = _y;
}

//--------------------------------------------------------------------------------

GAM_TrainCar::GAM_TrainCar(int _sprite, int _x, int _y, bool _loc, int _tSize) : GAM_Object(_sprite, _x, _y, _tSize)
{
   baseSprite = _sprite;
   x = _x;
   y = _y;
   SetPosition(x, y);
   prevX = i;
   prevY = j;
   locomotive = _loc;
   dir = 0;
}

//--------------------------------------------------------------------------------

void GAM_TrainCar::SetDir(int _dir)
{
   dir = _dir;
   switch(dir)
   {
   case 0:
      speedX = 0;
      speedY = 0;
      //sprite = baseSprite;
      //rotation = 0;
      break;
   case 1:
      speedX = -1;
      speedY = 0;
      sprite = baseSprite;
      //rotation = 90;
      break;
   case 2:
      speedX = -0.707f;
      speedY = 0.707f;
      sprite = baseSprite+3;
      //rotation = 45;
      break;
   case 3:
      speedX = 0;
      speedY = 1;
      sprite = baseSprite+1;
      //rotation = 0;
      break;
   case 4:
      speedX = 0.707f;
      speedY = 0.707f;
      sprite = baseSprite+2;
      //rotation = 45;
      break;
   case 5:
      speedX = 1;
      speedY = 0;
      sprite = baseSprite;
      //rotation = 90;
      break;
   case 6:
      speedX = 0.707f;
      speedY = -0.707f;
      sprite = baseSprite+3;
      //rotation = 45;
      break;
   case 7:
      speedX = 0;
      speedY = -1;
      sprite = baseSprite+1;
      //rotation = 0;
      break;
   case 8:
      speedX = -0.707f;
      speedY = -0.707f;
      sprite = baseSprite+2;
      //rotation = -45;
      break;
   }
}

//--------------------------------------------------------------------------------

void GAM_TrainCar::AddMove(GAM_MoveInfo mv)
{
   moves.push_back(mv);
}

//--------------------------------------------------------------------------------

void GAM_TrainCar::ClearMoves()
{
   moves.clear();
}

//--------------------------------------------------------------------------------

void GAM_TrainCar::NextMove(int _x, int _y)
{
   for(std::list<GAM_MoveInfo>::iterator it = moves.begin(); it != moves.end(); ++it)
      if(((*it).x == _x) && ((*it).y == _y))
      {
         SetDir((*it).nextDir);
         moves.erase(it);
         return;
      }
}