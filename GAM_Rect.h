#ifndef GAM_RECT_H
#define GAM_RECT_H

//--------------------------------------------------------------------------------

// prostokat
class GAM_Rect
{
public:

   int x; // pozycja
   int y;
   int w; // szerokosc
   int h; // wysokosc

   GAM_Rect(int _x = 0, int _y = 0, int _w = 0, int _h = 0)
   {
      Set(_x, _y, _w, _h);
   }

   // ustawienie wlasciwosci
   void Set(int _x = 0, int _y = 0, int _w = 0, int _h = 0)
   {
      x = _x;
      y = _y;
      w = _w;
      h = _h;
   }
};

//--------------------------------------------------------------------------------

#endif