#include "GFX_Tweener.h"

//--------------------------------------------------------------------------------

float Linear::easeOut(float t, float b, float c, float d)
{
   return c*t/d + b;
}

float Linear::easeIn(float t, float b, float c, float d)
{
   return c*t/d + b;
}

float Linear::easeInOut(float t, float b, float c, float d)
{
   return c*t/d + b;
}

//--------------------------------------------------------------------------------

float Quad::easeOut(float t, float b, float c, float d)
{
   return -c *(t/=d)*(t-2) + b;
}

float Quad::easeIn(float t, float b, float c, float d)
{
   return c*(t/=d)*t + b;
}

float Quad::easeInOut(float t, float b, float c, float d)
{
   if ((t/=d/2) < 1) return ((c/2)*(t*t)) + b;
   return -c/2 * (((t-2)*(--t)) - 1) + b;
}

//--------------------------------------------------------------------------------

float Elastic::easeOut(float t, float b, float c, float d)
{
   if (t==0) return b;  if ((t/=d)==1) return b+c;
   float p=d*.3f;
   float a=c;
   float s=p/4;
   return (a*pow(2,-10*t) * sin( (t*d-s)*(2*PI)/p ) + c + b);
}

float Elastic::easeIn(float t, float b, float c, float d)
{
   if (t==0) return b;  if ((t/=d)==1) return b+c;
   float p=d*.3f;
   float a=c;
   float s=p/4;
   float postFix =a*pow(2,10*(t-=1));
   return -(postFix * sin((t*d-s)*(2*PI)/p )) + b;
}

float Elastic::easeInOut(float t, float b, float c, float d)
{
   if (t==0) return b;  if ((t/=d/2)==2) return b+c;
   float p=d*(.3f*1.5f);
   float a=c;
   float s=p/4;

   if (t < 1) {
      float postFix =a*pow(2,10*(t-=1));
      return -.5f*(postFix* sin( (t*d-s)*(2*PI)/p )) + b;
   }
   float postFix =  a*pow(2,-10*(t-=1));
   return postFix * sin( (t*d-s)*(2*PI)/p )*.5f + c + b;
}

//--------------------------------------------------------------------------------

float Bounce::easeOut(float t, float b, float c, float d)
{
   if ((t/=d) < (1/2.75f)) {
      return c*(7.5625f*t*t) + b;
   } else if (t < (2/2.75f)) {
      float postFix = t-=(1.5f/2.75f);
      return c*(7.5625f*(postFix)*t + .75f) + b;
   } else if (t < (2.5/2.75)) {
      float postFix = t-=(2.25f/2.75f);
      return c*(7.5625f*(postFix)*t + .9375f) + b;
   } else {
      float postFix = t-=(2.625f/2.75f);
      return c*(7.5625f*(postFix)*t + .984375f) + b;
   }
}

float Bounce::easeIn(float t, float b, float c, float d)
{
   return c - easeOut (d-t, 0, c, d) + b;
}

float Bounce::easeInOut(float t, float b, float c, float d)
{
   if (t < d/2) return easeIn (t*2, 0, c, d) * .5f + b;
   else return easeOut (t*2-d, 0, c, d) * .5f + c*.5f + b;
}

//--------------------------------------------------------------------------------

float Back::easeOut(float t, float b, float c, float d)
{
   float s = 1.70158f;
   return c*((t=t/d-1)*t*((s+1)*t + s) + 1) + b;
}

float Back::easeIn(float t, float b, float c, float d)
{
   float s = 1.70158f;
   float postFix = t/=d;
   return c*(postFix)*t*((s+1)*t - s) + b;
}

float Back::easeInOut(float t, float b, float c, float d)
{
   float s = 1.70158f;
   if ((t/=d/2) < 1) return c/2*(t*t*(((s*=(1.525f))+1)*t - s)) + b;
   float postFix = t-=2;
   return c/2*((postFix)*t*(((s*=(1.525f))+1)*t + s) + 2) + b;
}

//--------------------------------------------------------------------------------

GFX_Tween::GFX_Tween(float *_prop, float _begin, float _end, long _duration, EasingFunction _funct, EasingType _type, long _delay /* = 0 */)
{
   prop = _prop;
   begin = _begin;
   end = _end;
   duration = _duration;
   funct = _funct;
   type = _type;
   delay = _delay;
   time = 0;
}

void GFX_Tween::AddListener(GFX_TweenListener *listener)
{
   listeners.push_back(listener);
}

void GFX_Tween::RemoveListener(GFX_TweenListener *listener)
{
   for(iter = listeners.begin(); iter != listeners.end(); ++iter)
      if(listener == *iter)
      {
         listeners.erase(iter);
         return;
      }
}

void GFX_Tween::MotionStart()
{
   for(iter = listeners.begin(); iter != listeners.end(); ++iter)
      (*iter)->OnMotionStart(this);
}

void GFX_Tween::MotionFinish()
{
   for(iter = listeners.begin(); iter != listeners.end(); ++iter)
      (*iter)->OnMotionFinish(this);
}

void GFX_Tween::MotionStep()
{
   for(iter = listeners.begin(); iter != listeners.end(); ++iter)
      (*iter)->OnMotionStep(this);
}

//--------------------------------------------------------------------------------

GFX_Tweener::GFX_Tweener()
{
   funct[LINEAR] = new Linear();
   funct[QUAD] = new Quad();
   funct[ELASTIC] = new Elastic();
   funct[BOUNCE] = new Bounce();
   funct[BACK] = new Back();

   prevTime = 0;
}

GFX_Tweener::~GFX_Tweener()
{
   for(int i = 0; i < 5; i++)
   {
      delete funct[i];
      funct[i] = NULL;
   }
}

void GFX_Tweener::Init(long time)
{
   prevTime = time;
}

void GFX_Tweener::AddTween(GFX_Tween *tween)
{
   if(NULL == tween)
      return;

   tweens.push_back(tween);
}

void GFX_Tweener::RemoveTween(GFX_Tween *tween)
{
   if(NULL == tween)
      return;

   for(iter = tweens.begin(); iter != tweens.end(); ++iter)
      if(tween == *iter)
      {
         tweens.erase(iter);
         return;
      }
}

void GFX_Tweener::Step(long time)
{
   long diff = time-prevTime;

   GFX_Tween *tw;
   iter = tweens.begin();
   while(iter != tweens.end())
   {
      tw = *iter;

      if(NULL == tw)
      {
         iter = tweens.erase(iter);
         continue;
      }

      if(tw->time < tw->duration+tw->delay)
      {
         if(tw->time == 0)
            tw->MotionStart();

         if(tw->time >= tw->delay)
         {
            switch(tw->type)
            {
            case EASE_OUT:
               *(tw->prop) = funct[tw->funct]->easeOut(tw->time-tw->delay, tw->begin, tw->end-tw->begin, tw->duration);
               break;

            case EASE_IN:
               *(tw->prop) = funct[tw->funct]->easeIn(tw->time-tw->delay, tw->begin, tw->end-tw->begin, tw->duration);
               break;

            case EASE_IN_OUT:
               *(tw->prop) = funct[tw->funct]->easeInOut(tw->time-tw->delay, tw->begin, tw->end-tw->begin, tw->duration);
               break;
            }

            tw->MotionStep();
         }

         tw->time += diff;

         ++iter;
      }
      else
      {
         iter = tweens.erase(iter);
         *(tw->prop) = tw->end;
         tw->MotionFinish();
      }
   }

   prevTime = time;
}