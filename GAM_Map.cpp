#include "GAM_Map.h"

//--------------------------------------------------------------------------------

int sign(int num, bool zero)
{
   if(zero)
      return (num > 0) ? 1 : ((num < 0) ? -1 : 0);
   else
      return (num >= 0) ? 1 : -1;
}

//--------------------------------------------------------------------------------

int xiso(int x, int y)
{
   return (-x+y);
}

//--------------------------------------------------------------------------------

int yiso(int x, int y)
{
   return -(-x-y)/2;
}

//--------------------------------------------------------------------------------

void generate_spot (GAM_Map & map, int mapsize, int spotpos_x, int spotpos_y, int spotdiam, int spottype, bool isobject, int cost, int randomize)
{
   int spotcenter_x = spotpos_x + spotdiam/2;
   int spotcenter_y = spotpos_y + spotdiam/2;

   for (int current_y = spotpos_y; current_y < spotpos_y+spotdiam; current_y++)
   {
      if ((current_y == 0) || (current_y >= mapsize-1)) break;
      for (int current_x = spotpos_x; current_x < spotpos_x+spotdiam; current_x++)
      {
         if ((current_x == 0) || (current_x >= mapsize-1)) break;
         double center_dist = sqrt( pow ((spotcenter_x-current_x)*1.0, 2) + pow ((spotcenter_y-current_y)*1.0, 2) );
         double gennum = (0.8*rand()/RAND_MAX) + 2.0; //2.0 .. 2.8
         if (center_dist < spotdiam/gennum) 
         {
            int type = spottype;
            if(randomize > 0)
               type += rand()%randomize;

            if (isobject)
            {
               if (!map[current_x][current_y].hasObject && (map[current_x][current_y].landType == SPR_GRASS))
               {
                  map.AddStaticObject(type, current_x, current_y);
                  map[current_x][current_y].hasObject = true;
                  map[current_x][current_y].cost = cost; //da sie jakos powiazac ze spottype?
               }
            }
            else
            {
               int lnd = map[current_x][current_y].landType;
               if((lnd != SPR_ROADC) && (lnd != SPR_ROADL) && (lnd != SPR_ROADR) && (lnd != SPR_GRASS2) && (lnd != SPR_GRASS3))
               {
                  map[current_x][current_y].landType = type;
                  map[current_x][current_y].cost = cost; //da sie jakos powiazac ze spottype?
               }
            }
         }
      }
   }
}

//--------------------------------------------------------------------------------

void autofill (GAM_Map & map, int mapsize, int spotnumber, int minspotdiam, int maxspotdiam, int spottype, bool isobject, int cost, int randomize)
{
   for (int i=0; i<spotnumber; i++)
   {
      int randomdiam = rand()%(abs(maxspotdiam-minspotdiam)+1)+minspotdiam;
      int randompos_x = rand()%mapsize;
      int randompos_y = rand()%mapsize;
      generate_spot (map, mapsize, randompos_x, randompos_y, randomdiam, spottype, isobject, cost, randomize);
   }
}

//--------------------------------------------------------------------------------

void GenerateCities(GAM_Map &map, int mapSize, int numCities)
{
   int pozycjaX;
   int pozycjaY;
   int wielkosc;
   int kierunek;

   short ax[4] = {1, -1, 1, -1};
   short ay[4] = {1, -1, -1, 1};

   for(int i=0; i< numCities; i++) {

      pozycjaX = ((rand()%(mapSize-5) + 3)/3)*3;
      pozycjaY = ((rand()%(mapSize-5) + 3)/3)*3;
      wielkosc = rand()%20 + 5;

      for(int j=0, iter = 0; iter < 10000 && j<wielkosc; j++, iter++) {

         if(map[pozycjaX][pozycjaY].landType != SPR_ROADC) {
            map[pozycjaX][pozycjaY].landType = SPR_ROADC;
            map[pozycjaX][pozycjaY].cost = COST_LOCKED;
            map[pozycjaX-1][pozycjaY].landType = SPR_ROADL;
            map[pozycjaX-1][pozycjaY].cost = COST_LOCKED;
            map[pozycjaX+1][pozycjaY].landType = SPR_ROADL;
            map[pozycjaX+1][pozycjaY].cost = COST_LOCKED;
            map[pozycjaX][pozycjaY-1].landType = SPR_ROADR;
            map[pozycjaX][pozycjaY-1].cost = COST_LOCKED;
            map[pozycjaX][pozycjaY+1].landType = SPR_ROADR;
            map[pozycjaX][pozycjaY+1].cost = COST_LOCKED;

            for(int k = 0; k < 4; k++)
            {
               short sx = ax[k], sy = ay[k];

               if(map[pozycjaX+sx][pozycjaY+sy].hasObject)
                  continue;

               int obj = (rand()%10 > 5) ? SPR_BLOCK : SPR_HOUSE;
               int lnd = (obj == SPR_BLOCK) ? SPR_GRASS2 : SPR_GRASS3;
               map.AddStaticObject(obj, pozycjaX+sx, pozycjaY+sy, false, true);
               map[pozycjaX+sx][pozycjaY+sy].landType = lnd;
               map[pozycjaX+sx][pozycjaY+sy].cost = COST_LOCKED;
               map[pozycjaX+sx][pozycjaY+sy].hasObject = true;
            }
         }
         else j--;

         kierunek = rand()%4;
         if(kierunek == 0) pozycjaX -= 3;
         else if(kierunek == 1) pozycjaY += 3;
         else if(kierunek == 2) pozycjaX += 3;
         else if(kierunek == 3) pozycjaY -= 3;

         if(pozycjaX < 3) pozycjaX += 6;
         else if(pozycjaX > mapSize-3) pozycjaX -= 6;
         else if(pozycjaY < 3) pozycjaY += 6;
         else if(pozycjaY > mapSize-3) pozycjaY -= 6;
      }
   }
}

//--------------------------------------------------------------------------------

GAM_MapTile::GAM_MapTile(GAM_Map *_map, int _x, int _y, int _land, int _rail, int _cost)
{
   map = _map;
   x = _x;
   y = _y;
   landType = _land;
   railType = _rail;
   cost = _cost;
   highlight = -1;
   hasObject = false;
   hasStation = false;
}

//--------------------------------------------------------------------------------

void GAM_MapTile::AddRail(int _num, bool _station /* = false */)
{
   if(hasStation)
      return;
   if(railType & _num)
      return;
   if(cost < 0)
      return;

   if(landType == SPR_WATER)
      if(((_num != 1) && (_num != 2)) || ((_num == 1) && (railType == 2)) || ((_num == 2) && (railType == 1)))
         return;
      else
         if(_num == 1)
         {
            map->AddStaticObject(SPR_GIRDERL, x, y, true, false, 17, 0);
            map->AddStaticObject(SPR_GIRDERL, x, y, true, false,  17, 24);
         }
         else
         {
            map->AddStaticObject(SPR_GIRDERR, x, y, true, false,  1, 17);
            map->AddStaticObject(SPR_GIRDERR, x, y, true, false,  24, 17);
         }

   if(_station && (railType == 0) && (landType == SPR_GRASS))
      if(_num == 1)
      {
         map->AddStaticObject(SPR_PLATFORML2, x, y, true, false, 0, 0);
         map->AddStaticObject(SPR_PLATFORML1, x, y, true, false, 0, 23);
         hasStation = true;
      }
      else if(_num == 2)
      {
         map->AddStaticObject(SPR_PLATFORMR2, x, y, true, false, 0, 11);
         map->AddStaticObject(SPR_PLATFORMR1, x, y, true, false, 16, 9);
         hasStation = true;
      }

   railType |= _num;
}

//--------------------------------------------------------------------------------

GAM_Object::GAM_Object(int _sprite, int _x, int _y, int _tSize, bool _dynamic /* = true */, bool _deletable /* = true */)
{
   sprite = _sprite;
   dynamic = _dynamic;
   deletable = _deletable;
   tSize = _tSize;
   marked = false;
   visible = true;
   SetPosition((float)_x, (float)_y);
}

//--------------------------------------------------------------------------------

void GAM_Object::SetPosition(float _x, float _y)
{
   x = _x;
   y = _y;
   rx = xiso((int)x, (int)y);
   ry = yiso((int)x, (int)y);
   i = x/tSize;
   j = y/tSize;
}

//--------------------------------------------------------------------------------

bool CompareObj(GAM_Object *a, GAM_Object *b)
{
   if((NULL == a) || (NULL == b))
      return false;

   //return ((a->x+a->y*10) <= (b->x+b->y*10));
   return ((a->rx + a->ry*a->tSize) <= (b->rx + b->ry*b->tSize));
}

//--------------------------------------------------------------------------------

bool RemoveObjCondition(GAM_Object *obj)
{
   return (obj == NULL) || obj->marked;
}

//--------------------------------------------------------------------------------

GAM_Map::GAM_Map(int _size, int _sw, int _sh, int _tw, int _th, GFX_SpriteManager *_spr)
{
   mapSize = _size;
   tWidth = _tw;
   tHeight = _th;
   sWidth = _sw;
   sHeight = _sh;
   sprMng = _spr;
   curVisible = false;

   cx = (sWidth-tWidth)/2;
   cy = (sHeight-(mapSize+1)*tHeight)/2;

   int i, j;

   for(i = 0; i < mapSize; i++)
   {
      map.push_back(std::vector<GAM_MapTile>());

      for(j = 0; j < mapSize; j++)
         map[i].push_back(GAM_MapTile(this, i, j, ((i == 0) || (i == mapSize-1) || (j == 0) || (j == mapSize-1)) ? SPR_WATER : SPR_GRASS));
   }
}

//--------------------------------------------------------------------------------

GAM_Map::~GAM_Map(void)
{
   for(iter = staticOb.begin(); iter != staticOb.end(); ++iter)
      delete *iter;
}

//--------------------------------------------------------------------------------

void GAM_Map::MoveMap(int dx, int dy)
{
   cx += dx;
   cy += dy;
}

//--------------------------------------------------------------------------------

void GAM_Map::Render(SDL_Surface *dest)
{
   int i, j, xx, yy;

   for(j = 0; j < mapSize; j++)
      for(i = 0; i < mapSize; i++)
      {
         xx = cx+(j-i)*tWidth/2;
         yy = cy+(i+j)*tHeight/2;
         if((xx < -tWidth) || (xx > sWidth) || (yy < -2*tHeight) || (yy > sHeight+2*tHeight))
            continue;

         GAM_MapTile &tile = map[i][j];

         if(tile.landType != SPR_WATER)
            if(((i == mapSize-1) || (j == mapSize-1)) || (((i+1 < mapSize) && (map[i+1][j].landType == SPR_WATER)) || ((j+1 < mapSize) && (map[i][j+1].landType == SPR_WATER))))
               sprMng->DrawSprite(SPR_GROUND, xx, yy, dest);
         sprMng->DrawSprite(tile.landType, xx, yy, dest);
         if((tile.landType == SPR_WATER) && (tile.railType != 0))
            sprMng->DrawSprite((tile.railType == 1) ? SPR_BRIDGEL : SPR_BRIDGER, xx, yy, dest);
         if(tile.railType != 0)
            sprMng->DrawSprite(tile.railType, xx, yy, dest);
         if(tile.highlight >= 0)
            sprMng->DrawSprite(tile.highlight, xx, yy, dest);
      }

   int ws = sign(cursor.w);
   int hs = sign(cursor.h);
   int aw = abs(cursor.w);
   int ah = abs(cursor.h);
   for(i = 0; i <= aw; i++)
   {
      xx = cursor.x-i*ws;
      if((xx < 0) || (xx > mapSize-1))
         continue;

      for(j = 0; j <= ah; j++)
      {
         yy = cursor.y-j*hs;
         if((yy < 0) || (yy > mapSize-1))
            continue;

         sprMng->DrawSprite(SPR_CURSOR, cx+(yy-xx)*tWidth/2, cy+(xx+yy)*tHeight/2, dest);
      }
   }

   GAM_Object *obj;
   std::vector<GAM_Object*> sorted;
   for(iter = objects.begin(); iter != objects.end(); ++iter)
   {
      obj = *iter;
      if((NULL == obj) || !CheckBounds(obj->i, obj->j) || (!obj->visible))
         continue;

      sorted.push_back(obj);
   }

   std::sort(sorted.begin(), sorted.end(), CompareObj);

   for(iter = sorted.begin(); iter != sorted.end(); ++iter)
   {
      obj = *iter;
      if(NULL == obj)
         continue;

      sprMng->DrawSprite(obj->sprite, cx+obj->rx, cy+obj->ry, dest);
   }
}

//--------------------------------------------------------------------------------

void GAM_Map::SetCursor(bool visible, int x, int y, int w, int h)
{
   curVisible = visible;
   if(!curVisible)
      return;

   cursor.x = x;
   cursor.y = y;
   cursor.w = w;
   cursor.h = h;
}

//--------------------------------------------------------------------------------

void GAM_Map::AddRailArea(int type, int x, int y, int w /* = 0 */, int h /* = 0 */, bool station /* = false */)
{
   ClearArea(x, y, w, h, false);

   int ws = sign(w);
   int hs = sign(h);
   int aw = abs(w);
   int ah = abs(h);
   int xx, yy;

   for(int i = 0; i <= aw; i++)
   {
      xx = x-i*ws;
      if((xx < 0) || (xx > mapSize-1))
         continue;

      for(int j = 0; j <= ah; j++)
      {
         yy = y-j*hs;
         if((yy < 0) || (yy > mapSize-1))
            continue;

         map[xx][yy].AddRail(type, station);
      }
   }
}

//--------------------------------------------------------------------------------

void GAM_Map::AddLandArea(int type, int x, int y, int w, int h, int cost)
{
   int ws = sign(w);
   int hs = sign(h);
   int aw = abs(w);
   int ah = abs(h);
   int xx, yy;

   for(int i = 0; i <= aw; i++)
   {
      xx = x-i*ws;
      if((xx < 0) || (xx > mapSize-1))
         continue;

      for(int j = 0; j <= ah; j++)
      {
         yy = y-j*hs;
         if((yy < 0) || (yy > mapSize-1))
            continue;

         map[xx][yy].landType = type;
         map[xx][yy].cost = cost;
      }
   }
}

//--------------------------------------------------------------------------------

void GAM_Map::ClearArea(int x, int y, int w, int h, bool clearRail /* = true */)
{
   int ws = sign(w);
   int hs = sign(h);
   int aw = abs(w);
   int ah = abs(h);
   int xx, yy;

   GAM_Object *p;
   for(iter = objects.begin(); iter != objects.end(); ++iter)
   {
      p = *iter;
      if(NULL == p)
         continue;
      if(p->dynamic || !p->deletable)
         continue;

      if((ws < 0) && ((p->i < x) || (p->i > x+aw)))
         continue;
      else if((ws >= 0) && ((p->i > x) || (p->i < x-aw)))
         continue;

      if((hs < 0) && ((p->j < y) || (p->j > y+ah)))
         continue;
      else if((hs >= 0) && ((p->j > y) || (p->j < y-ah)))
         continue;

      if(!clearRail && ((p->sprite == SPR_GIRDERL) || (p->sprite == SPR_GIRDERR) || (p->sprite == SPR_PLATFORML1)
          || (p->sprite == SPR_PLATFORML2) || (p->sprite == SPR_PLATFORMR1) || (p->sprite == SPR_PLATFORMR2)))
         continue;

      p->marked = true;
   }

   iter = objects.begin();
   while(iter != objects.end())
   {
      if((NULL == *iter) || (*iter)->marked)
         iter = objects.erase(iter);
      else
         ++iter;
   }

   iter = staticOb.begin();
   while(iter != staticOb.end())
   {
      if((NULL == *iter) || (*iter)->marked)
      {
         delete *iter;
         *iter = NULL;
         iter = staticOb.erase(iter);
      }
      else
         ++iter;
   }

   if(!clearRail)
      return;

   for(int i = 0; i <= aw; i++)
   {
      xx = x-i*ws;
      if((xx < 0) || (xx > mapSize-1))
         continue;

      for(int j = 0; j <= ah; j++)
      {
         yy = y-j*hs;
         if((yy < 0) || (yy > mapSize-1))
            continue;

         map[xx][yy].railType = 0;
         map[xx][yy].hasStation = false;
      }
   }
}

//--------------------------------------------------------------------------------

GAM_MapTile& GAM_Map::Get(int i, int j)
{
   return map[i][j];
}

//--------------------------------------------------------------------------------

GAM_MapTile& GAM_Map::operator()(int i, int j)
{
   return map[i][j];
}

//--------------------------------------------------------------------------------

std::vector<GAM_MapTile>& GAM_Map::operator[](int i)
{
   return map[i];
}

//--------------------------------------------------------------------------------

void GAM_Map::AddDynamicObject(GAM_Object *obj)
{
   if(NULL != obj)
      objects.push_back(obj);
}

//--------------------------------------------------------------------------------

void GAM_Map::AddStaticObject(int sprite, int x, int y, bool deletable /* = true */, bool center /* = true */, int ox /* = 0 */, int oy /* = 0 */)
{
   int ofx = center ? tHeight/2 : ox;
   int ofy = center ? ofx : oy;
   GAM_Object *ob = new GAM_Object(sprite, x*tHeight+ofx, y*tHeight+ofy, tHeight, false, deletable);
   objects.push_back(ob);
   staticOb.push_back(ob);
}

//--------------------------------------------------------------------------------

void GAM_Map::RemoveObject(GAM_Object *obj)
{
   if(NULL == obj)
      return;

   std::vector<GAM_Object*>::iterator it2;
   for(iter = objects.begin(); iter != objects.end(); ++iter)
      if(obj == *iter)
      {
         if((NULL != *iter) && !(*iter)->dynamic)
         {
            for(it2 = staticOb.begin(); it2 != staticOb.end(); ++it2)
               if(obj == *it2)
               {
                  staticOb.erase(it2);
                  break;
               }

            delete *iter;
            *iter = NULL;
         }
         objects.erase(iter);
         return;
      }
}

//--------------------------------------------------------------------------------

bool GAM_Map::CheckBounds(int i, int j)
{
   return ((i >= 0) && (i < mapSize) && (j >= 0) && (j < mapSize));
}