#include "GAM_Train.h"

//--------------------------------------------------------------------------------

GAM_Train::GAM_Train(int _sprite, int _x, int _y, int _length, int _speed, GAM_Map *_map, int _tSize, bool _horiz, int _dist)
{
   sprite = _sprite;
   speed = 0;
   maxSpeed = _speed;
   length = _length;
   map = _map;
   tSize = _tSize;
   dist = _dist;
   horiz = _horiz;
   firstPass = true;
   state = TRAIN_STOPPED;

   for(int i = 0; i < length; i++)
   {
      GAM_TrainCar *car = new GAM_TrainCar((i == 0) ? sprite : SPR_CAR1, _x*tSize+tSize/2+(_horiz ? 0 : 1)*i*_dist, _y*tSize+tSize/2+(_horiz ? 1 : 0)*i*_dist, (i == 0), tSize);
      car->visible = false;
      cars.push_back(car);
      map->AddDynamicObject(car);
      car->SetDir(_horiz ? 7 : 1);
   }
}

//--------------------------------------------------------------------------------

GAM_Train::~GAM_Train()
{
   for(int i = 0; i < cars.size(); i++)
   {
      if(NULL != map)
         map->RemoveObject(cars[i]);
      delete cars[i];
      cars[i] = NULL;
   }
}

//--------------------------------------------------------------------------------

void GAM_Train::SetPath(std::vector<GAM_MapTile*> _path)
{
   currStep = 0;
   path = _path;
   firstPass = true;

   if(path.size() < 2)
      return;

   GAM_MapTile *first = path[0], *second = path[1];
   GAM_TrainCar *car;

   int dir = 0, hx = 0, hy = 0;
   if(first->y == second->y)
   {
      if(first->x > second->x)
      {
         dir = 1;
         hx = 1;
         hy = 0;
      }
      else
      {
         dir = 5;
         hx = -1;
         hy = 0;
      }
   }
   else if(first->x == second->x)
   {
      if(first->y > second->y)
      {
         dir = 7;
         hx = 0;
         hy = 1;
      }
      else
      {
         dir = 3;
         hx = 0;
         hy = -1;
      }
   }

   int i = 0;
   for(iter = cars.begin(); iter != cars.end(); ++iter)
   {
      car = *iter;
      car->visible = (i == 0);
      car->x = first->x*tSize + tSize/2 + hx*i*dist;
      car->y = first->y*tSize + tSize/2 + hy*i*dist;
      car->SetPosition(car->x, car->y);
      car->prevX = car->i;
      car->prevY = car->j;
      car->SetDir(dir);
      car->ClearMoves();
      i++;
   }

   speed = maxSpeed;
   state = TRAIN_TRAVEL;
}

//--------------------------------------------------------------------------------

void GAM_Train::Update()
{
   if((path.size() == 0) || (state == TRAIN_STOPPED))
      return;

   if(state == TRAIN_WAITING)
   {
      waitCount++;
      if(waitCount > 50)
      {
         state = TRAIN_TRAVEL;
         speed = maxSpeed;
      }
   }

   int xx, yy;
   bool stop = false;
   GAM_TrainCar *car;
   for(iter = cars.begin(); iter != cars.end(); ++iter)
   {
      car = *iter;

      xx = (car->x + speed*car->speedX)/tSize;
      yy = (car->y + speed*car->speedY)/tSize;

      if((car->prevX != xx) || (car->prevY != yy))
      {
         car->x += speed*car->speedX;
         car->y += speed*car->speedY;

         int sx = sign(car->prevX-xx, true);
         int sy = sign(car->prevY-yy, true);
         float ox = xx*tSize + (1+sx)*tSize/2.0;
         float oy = yy*tSize + (1+sy)*tSize/2.0;
         float dx = car->x-ox;
         float dy = car->y-oy;
         float dist = sqrt((float)(dx*dx + dy*dy));

         if(car->locomotive)
         {
            currStep++;
            if(currStep >= path.size()-1)
               currStep = 0;

            GAM_MapTile *next = path[currStep+1], *prev;

            if(next->railType == 0)
            {
               state = TRAIN_STOPPED;
               stop = true;
            }

            switch(state)
            {
            case TRAIN_TRAVEL:
               if(path[currStep]->hasStation)
                  state = TRAIN_ON_STATION;
               break;

            case TRAIN_ON_STATION:
               if(!next->hasStation)
               {
                  state = TRAIN_WAITING;
                  stop = true;
                  waitCount = 0;
               }
               break;
            }

            if(firstPass)
            {
               if(currStep > 0)
               {
                  prev = path[currStep-1];
                  car->SetDir(NewDir(prev->x, prev->y, xx, yy, next->x, next->y));
               }
               else
                  car->SetDir(NewDir(xx, yy, xx, yy, next->x, next->y));

               firstPass = false;
            }
            else
            {
               int prevStep = currStep-1;
               if(prevStep < 0)
                  prevStep = path.size()-2;

               prev = path[prevStep];
               car->SetDir(NewDir(prev->x, prev->y, xx, yy, next->x, next->y));
            }               
         }
         else
         {
            car->NextMove(xx, yy);
            
            if((car->i == path[0]->x) && (car->j == path[0]->y))
               car->visible = true;
         }

         if(iter+1 != cars.end())
            (*(iter+1))->AddMove(GAM_MoveInfo(car->dir, xx, yy));

         car->prevX = xx;
         car->prevY = yy;

         car->x = ox + dist*car->speedX;
         car->y = oy + dist*car->speedY;

         //car->SetDir(0);
      }
      else
      {
         car->x += speed*car->speedX;
         car->y += speed*car->speedY;
      }

      car->SetPosition(car->x, car->y);
   }

   if(stop)
   {
      speed = 0;
      stop = false;
   }
}

//--------------------------------------------------------------------------------

int GAM_Train::NewDir(int px, int py, int xx, int yy, int nx, int ny)
{
   if((nx < xx) && (ny == yy))
      if((px == xx) && (py == yy))
         return 1;
      else if((py == yy))
         return 1;
      else if((py < yy))
         return 2;
      else if((py > yy) && (px == xx))
         return 8;

   if((nx > xx) && (ny == yy))
      if((px == xx) && (py == yy))
         return 5;
      else if((py == yy))
         return 5;
      else if((py < yy))
         return 4;
      else if((py > yy) && (px == xx))
         return 6;

   if((nx == xx) && (ny < yy))
      if((px == xx) && (py == yy))
         return 7;
      else if((px == xx))
         return 7;
      else if((px < xx))
         return 6;
      else if((py == yy) && (px > xx))
         return 8;

   if((nx == xx) && (ny > yy))
      if((px == xx) && (py == yy))
         return 3;
      else if((px == xx))
         return 3;
      else if((px < xx))
         return 4;
      else if((py == yy) && (px > xx))
         return 2;

      /*if((nx < xx) && (ny == yy))
         if((px == xx) && (py == yy))
            return 1;
         else if((py == yy) && (px > xx))
            return 1;
         else if((py < yy) && (px == xx))
            return 2;
         else if((py > yy) && (px == xx))
            return 8;

         if((nx > xx) && (ny == yy))
            if((px == xx) && (py == yy))
               return 5;
            else if((py == yy) && (px < xx))
               return 5;
            else if((py < yy) && (px == xx))
               return 4;
            else if((py > yy) && (px == xx))
               return 6;

            if((nx == xx) && (ny < yy))
               if((px == xx) && (py == yy))
                  return 7;
               else if((py > yy) && (px == xx))
                  return 7;
               else if((py == yy) && (px < xx))
                  return 6;
               else if((py == yy) && (px > xx))
                  return 8;

               if((nx == xx) && (ny > yy))
                  if((px == xx) && (py == yy))
                     return 3;
                  else if((py < yy) && (px == xx))
                     return 3;
                  else if((py == yy) && (px < xx))
                     return 4;
                  else if((py == yy) && (px > xx))
                     return 2;*/

   return 0;
}

