#include "GAM_AStar.h"

//--------------------------------------------------------------------------------

GAM_Waypoint::GAM_Waypoint(GAM_MapTile *_tile, GAM_Waypoint *_prev /* = NULL */)
{
   prev = _prev;
   tile = _tile;
   h = 0;
   g = 0;
   f = 0;
}

//--------------------------------------------------------------------------------

GAM_AStar::GAM_AStar(GAM_Map *_map)
{
   map = _map;
}

//--------------------------------------------------------------------------------

GAM_AStar::~GAM_AStar(void)
{
   ClearLists();
}

//--------------------------------------------------------------------------------

std::vector<GAM_MapTile*> GAM_AStar::FindPath(int x1, int y1, int x2, int y2, GAM_SearchAlgorithm alg, bool cross /* = true */)
{
   algorithm = alg;
   crossing = cross;

   if(!map->CheckBounds(x1, x2) || !map->CheckBounds(x2, y2) || (map->Get(x1, y1).cost < 0) || (map->Get(x2, y2).cost < 0))
      return std::vector<GAM_MapTile*>();
   if((algorithm == FND_RAIL) && ((map->Get(x1, y1).railType == 0) || (map->Get(x2, y2).railType == 0)))
      return std::vector<GAM_MapTile*>();

   GAM_Waypoint *curr = new GAM_Waypoint(&(map->Get(x1, y1)));
   open.push_back(curr);

   const long MAX = 10000;
   long k = 0;

   while(!open.empty())
   {
      curr = open[0];
      for(int i = 1; i < open.size(); i++)
         if(open[i]->f < curr->f)
            curr = open[i];

      closed.push_back(curr);
      
      for(it = open.begin(); it != open.end(); ++it)
         if(curr == *it)
         {
            open.erase(it);
            break;
         }

      if((curr->tile->x == x2) && (curr->tile->y == y2))
         break;

      AddToOpen(curr->tile->x-1, curr->tile->y, curr, x2, y2);
      AddToOpen(curr->tile->x, curr->tile->y-1, curr, x2, y2);
      AddToOpen(curr->tile->x+1, curr->tile->y, curr, x2, y2);
      AddToOpen(curr->tile->x, curr->tile->y+1, curr, x2, y2);

      k++;
      if(k >= MAX)
      {
         ClearLists();
         return std::vector<GAM_MapTile*>();
      }
   }

   if((curr->tile->x != x2) || (curr->tile->y != y2))
   {
      ClearLists();
      return std::vector<GAM_MapTile*>();
   }

   std::vector<GAM_MapTile*> output;
   for(GAM_Waypoint *p = curr; p != NULL; p = p->prev)
      output.push_back(p->tile);
   std::reverse(output.begin(), output.end());

   ClearLists();

   return output;
}

//--------------------------------------------------------------------------------

void GAM_AStar::AddToOpen(int x, int y, GAM_Waypoint *prev, int dx, int dy)
{
   if(!map->CheckBounds(x, y))
      return;
   if(map->Get(x, y).cost < 0)
      return;

   if(algorithm == FND_RAIL)
   {
      if(map->Get(x, y).railType == 0)
         return;
      if((NULL != prev->prev) && !CanGo(prev->prev->tile->x, prev->prev->tile->y, prev->tile->x, prev->tile->y, x, y))
         return;
      else if((NULL == prev->prev) && !CanGoNoPrev(prev->tile->x, prev->tile->y, x, y))
         return;
   }
   else
   {
      if(!crossing && map->Get(x, y).railType != 0)
         return;
      if(map->Get(x, y).hasStation)
         return;
      if(prev->tile->landType == SPR_WATER)
         if(NULL != prev->prev)
            if((prev->tile->x == prev->prev->tile->x) && (x != prev->tile->x))
               return;
            else if((prev->tile->y == prev->prev->tile->y) && (y != prev->tile->y))
               return;
   }

   int i;
   GAM_Waypoint *p;

   for(i = 0; i < open.size(); i++)
   {
      p = open[i];
      if((p->tile->x == x) && (p->tile->y == y))
         if((algorithm != FND_RAIL) && (prev->tile->landType != SPR_WATER))
            return;
         else
         {
            if(NULL != p->prev)
            {
               if((p->prev->tile->x == prev->tile->x) && (p->prev->tile->y == prev->tile->y))
                  return;
            }
            else if((NULL == p->prev) && (NULL == prev))
               return;
         }
   }
            
   for(i = 0; i < closed.size(); i++)
   {
      p = closed[i];
      if((p->tile->x == x) && (p->tile->y == y))
         if((algorithm != FND_RAIL) && !((prev->tile->landType == SPR_WATER) && (map->Get(x, y).landType == SPR_WATER)))
            return;
         else
         {
            if(NULL != p->prev)
            {
               if((p->prev->tile->x == prev->tile->x) && (p->prev->tile->y == prev->tile->y))
                  return;
            }
            else if((NULL == p->prev) && (NULL == prev))
               return;
         }
   }

   GAM_Waypoint *wp = new GAM_Waypoint(&(map->Get(x, y)), prev);
   wp->g = prev->g+((algorithm == FND_CHEAPEST) ? wp->tile->cost : 1);
   float param = 2.0;
   wp->h = (abs(x-dx)+abs(y-dy))*((algorithm == FND_CHEAPEST) ? param*COST_GRASS : param);
   wp->f = wp->g+wp->h;

   open.push_back(wp);
}

//--------------------------------------------------------------------------------

void GAM_AStar::ClearLists(void)
{
   int i;

   for(i = 0; i < open.size(); i++)
   {
      delete open[i];
      open[i] = NULL;
   }
   for(i = 0; i < closed.size(); i++)
   {
      delete closed[i];
      closed[i] = NULL;
   }

   open.clear();
   closed.clear();
}

//--------------------------------------------------------------------------------

bool GAM_AStar::CanGo(int xp, int yp, int x, int y, int xn, int yn)
{
   bool ret_val=0;
   bool left;
   bool right;
   bool up;
   bool down;
   int curr=map->Get(x, y).railType;
   int next=map->Get(xn, yn).railType;
   bool bit_curr[6], bit_next[6];
   //przeliczanie numeru pola na wartosc bitowa
   for(int i=5;i>=0;i--){
      bit_curr[i]=curr%2;
      curr=curr/2;
   }
   for(int i=5;i>=0;i--){
      bit_next[i]=next%2;
      next=next/2;
   }
  
   //zdefiniowanie wejsc do kolejnego pola (cel przejscia)
   left=bit_next[0]||bit_next[3]||bit_next[4];
   right=bit_next[1]||bit_next[2]||bit_next[4];
   up=bit_next[2]||bit_next[3]||bit_next[5];
   down=bit_next[0]||bit_next[1]||bit_next[5];

   //wlasciwe sprawdzenie mozliwosci przejscia z (x,y), na (xn,yn), (xp,yp)-pol. poprzednie
   if(yp+1==y)//1
   {
      if(xp==x)//4
      {
         if(yn-1==y&&xn==x)//8
         {
            ret_val=bit_curr[4]&&left;
         }//pl
         else if(yn==y)//9
         {
            if(xn-1==x)
            {
               ret_val=bit_curr[0]&&up;
            }//dp
            else if(xn+1==x)
            {
               ret_val=bit_curr[3]&&down;
            }//gp
         }
      }
   }
   else if(yp==y)//2
   {
      if(xp+1==x)//5
      {
         if(yn==y&&xn-1==x)//10
         {
            ret_val=bit_curr[5]&&up;
         }//gd
         else if(yn-1==y&&xn==x)//11
         {
            ret_val=bit_curr[2]&&left;
         }//gp
         else if(yn+1==y&&xn==x)//12
         {
            ret_val=bit_curr[3]&&right;
         }//gl
      }
      else if(xp-1==x)//6
      {
         if(yn==y&&xn+1==x)//13
         {
            ret_val=bit_curr[5]&&down;
         }//gd
         else if(yn-1==y&&xn==x)//14
         {
            ret_val=bit_curr[1]&&left;
         }//dp
         else if(yn+1==y&&xn==x)//15
         {
            ret_val=bit_curr[0]&&right;
         }//dl
      }
   }
   else if(yp-1==y)//3
   {
      if(xp==x)//7
      {
         if(yn+1==y&&xn==x)//16
         {
            ret_val=bit_curr[4]&&right;
         }//pl
         else if(yn==y)//17
         {
            if(xn+1==x)
            {
               ret_val=bit_curr[2]&&down;
            }//gp
            else if(xn-1==x)
            {
               ret_val=bit_curr[1]&&up;
            }//dp
         }
      }
   }

   return ret_val;
}

//--------------------------------------------------------------------------------

bool GAM_AStar::CanGoNoPrev(int x, int y, int xn, int yn)
{
   bool ret_val=0;
   //enables-wartosci zezwolen wejsc do pola-celu i wyjsc z obecnego pola
   //kolejnosc: n_l, n_r, n_u, n_d, c_l, c_r, c_u, c_d
   bool enables[8];
   int curr=map->Get(x, y).railType;
   int next=map->Get(xn, yn).railType;
   bool bit_curr[6], bit_next[6];
   //przeliczanie numeru pola na wartosc binarna
   for(int i=5;i>=0;i--){
      bit_curr[i]=curr%2;
      curr=curr/2;
      bit_next[i]=next%2;
      next=next/2;
   }

   //zdefiniowanie wejsc do kolejnego pola/wyjsc z obecnego
   enables[0]=bit_next[0]||bit_next[3]||bit_next[4];
   enables[1]=bit_next[1]||bit_next[2]||bit_next[4];
   enables[2]=bit_next[2]||bit_next[3]||bit_next[5];
   enables[3]=bit_next[0]||bit_next[1]||bit_next[5];
   enables[4]=bit_curr[0]||bit_curr[3]||bit_curr[4];
   enables[5]=bit_curr[1]||bit_curr[2]||bit_curr[4];
   enables[6]=bit_curr[2]||bit_curr[3]||bit_curr[5];
   enables[7]=bit_curr[0]||bit_curr[1]||bit_curr[5];

   //wlasciwe sprawdzenie mozliwosci przejscia z (x,y), na (xn,yn)
   if(xn==x)
   {
      if(yn+1==y)
         ret_val=enables[4]&&enables[1];//left
      else if(yn-1==y)
         ret_val=enables[5]&&enables[0];//right
   }
   else if(yn==y)
   {
      if(xn+1==x)
         ret_val=enables[6]&&enables[3];//up
      else if(xn-1==x)
         ret_val=enables[7]&&enables[2];//down
   }

   return ret_val;
}