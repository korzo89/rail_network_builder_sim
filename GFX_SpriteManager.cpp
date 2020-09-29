#include "GFX_SpriteManager.h"

//--------------------------------------------------------------------------------

GFX_SpriteManager::GFX_SpriteManager(void)
{
   gfx = NULL;
}

//--------------------------------------------------------------------------------

GFX_SpriteManager::~GFX_SpriteManager(void)
{
   SDL_FreeSurface(gfx);
}

//--------------------------------------------------------------------------------

bool GFX_SpriteManager::Load(std::string src)
{
   std::ifstream file;
   file.open(src.c_str());

   if(!file.is_open())
      return false;

   char c;
   bool filename = false, comment = false;
   int ni = 0, nj = 0, xx = 0, yy = 0, ww = 0, hh = 0, ox = 0, oy = 0;
   std::string name;

   while(file.good())
   {
      c = file.peek();

      if(comment && (c != ';'))
         file.ignore();
      else if(filename && (c != ';'))
      {
         c = file.get();
         name += c;
      }
      else
      {
         switch(c)
         {
         case ';':
            filename = false;
            comment = false;
            file.ignore();
            break;

         case '@':
            filename = true;
            file.ignore();
            break;

         case '#':
            comment = true;
            file.ignore();
            break;

         case '$':
            file.ignore();

            file >> ni >> nj >> xx >> yy >> ww >> hh >> ox >> oy;

            for(int i = 0; i < ni; i++)
               for(int j = 0; j < nj; j++)
               {
                  GFX_Sprite spr;
                  spr.clipRect.x = xx+j*ww;
                  spr.clipRect.y = yy+i*hh;
                  spr.clipRect.w = ww;
                  spr.clipRect.h = hh;
                  spr.ox = ox;
                  spr.oy = oy;

                  sprites.push_back(spr);
               }        
            break;

         case '&':
            file.ignore();

            GFX_Sprite spr;
            file >> spr.clipRect.x >> spr.clipRect.y >> spr.clipRect.w >> spr.clipRect.h >> spr.ox >> spr.oy;
            sprites.push_back(spr);

            break;

         default:
            file.ignore();
            break;
         }
      }
   }

   file.close();

   gfx = LoadImage(name);
   if(NULL == gfx)
      return false;

   return true;
}

//--------------------------------------------------------------------------------

bool GFX_SpriteManager::DrawSprite(int id, int x, int y, SDL_Surface *dest)
{
   if((id < 0) || (id >= sprites.size()))
      return false;

   SDL_Rect offset;
   offset.x = x+sprites[id].ox;
   offset.y = y+sprites[id].oy;

   SDL_BlitSurface(gfx, &(sprites[id].clipRect), dest, &offset);

   return true;
}

//--------------------------------------------------------------------------------

int GFX_SpriteManager::NumSprites(void) const
{
   return sprites.size();
}