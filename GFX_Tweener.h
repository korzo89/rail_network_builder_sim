#ifndef GFX_TWEENER_H
#define GFX_TWEENER_H

//--------------------------------------------------------------------------------

#include <list>

//--------------------------------------------------------------------------------

#ifndef PI
   #define PI 3.14159265
#endif

//--------------------------------------------------------------------------------

// klasa animacji
class Easing
{
public:
   virtual float easeOut(float t, float b, float c, float d) = 0;
   virtual float easeIn(float t, float b, float c, float d) = 0;
   virtual float easeInOut(float t, float b, float c, float d) = 0;
};

// pochodne klasy animacji
class Linear : public Easing
{
public:
   virtual float easeOut(float t, float b, float c, float d);
   virtual float easeIn(float t, float b, float c, float d);
   virtual float easeInOut(float t, float b, float c, float d);
};

class Quad : public Easing
{
public:
   virtual float easeOut(float t, float b, float c, float d);
   virtual float easeIn(float t, float b, float c, float d);
   virtual float easeInOut(float t, float b, float c, float d);
};

class Elastic : public Easing
{
public:
   virtual float easeOut(float t, float b, float c, float d);
   virtual float easeIn(float t, float b, float c, float d);
   virtual float easeInOut(float t, float b, float c, float d);
};

class Bounce : public Easing
{
public:
   virtual float easeOut(float t, float b, float c, float d);
   virtual float easeIn(float t, float b, float c, float d);
   virtual float easeInOut(float t, float b, float c, float d);
};

class Back : public Easing
{
public:
   virtual float easeOut(float t, float b, float c, float d);
   virtual float easeIn(float t, float b, float c, float d);
   virtual float easeInOut(float t, float b, float c, float d);
};

//--------------------------------------------------------------------------------

// rodzaj spowalniania animacji
enum EasingType { EASE_OUT, EASE_IN, EASE_IN_OUT };

// rodzaj animacji
enum EasingFunction { LINEAR, QUAD, ELASTIC, BOUNCE, BACK };

//--------------------------------------------------------------------------------

class GFX_TweenListener;

// tween (animacja parametru)
class GFX_Tween
{
private:
   std::list<GFX_TweenListener*> listeners; // lista listenerow zdarzen
   std::list<GFX_TweenListener*>::iterator iter;

public:
   float begin; // poczatkowa wartosc animacji
   float end; // koncowa wartosc

   long duration; // czas trwania animacji
   long time; // aktualny czas animacji
   long delay; // opoznienie animacji
   
   EasingFunction funct; // rodzaj animacji
   EasingType type; // rodzaj spowalniania

   float *prop; // wskaznik do animowanej zmiennej

   GFX_Tween(float *_prop, float _begin, float _end, long _duration, EasingFunction _funct, EasingType _type, long _delay = 0);
   
   // dodanie listenera zdarzenia
   void AddListener(GFX_TweenListener *listener);

   // usuniecie listenera
   void RemoveListener(GFX_TweenListener *listener);

   // animacja rozpoczeta
   void MotionStart();

   // animacja zakonczona
   void MotionFinish();

   // wykonany krok animacji
   void MotionStep();
};

//--------------------------------------------------------------------------------

// listener zdarzen tweenow
class GFX_TweenListener
{
public:

   // animacja rozpoczeta
   virtual void OnMotionStart(GFX_Tween *tween) = 0;

   // animacja zakonczona
   virtual void OnMotionFinish(GFX_Tween *tween) = 0;

   // wykonany krok animacji
   virtual void OnMotionStep(GFX_Tween *tween) = 0;
};

//--------------------------------------------------------------------------------

// tweener (manager animacji)
class GFX_Tweener
{
private:

   std::list<GFX_Tween*> tweens; // lista tweenow
   std::list<GFX_Tween*>::iterator iter;

   Easing *funct[5]; // rodzaje animacji

   long prevTime; // czas poprzedniego kroku

public:

   GFX_Tweener();
   ~GFX_Tweener();

   // inicjalizacja tweenera
   void Init(long time);

   // dodanie tweenu
   void AddTween(GFX_Tween *tween);

   // usuniecie tweenu
   void RemoveTween(GFX_Tween *tween);

   // wykonanie kroku animacji
   void Step(long time);
};

//--------------------------------------------------------------------------------

#endif