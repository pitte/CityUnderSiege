#include "Enemy.h"
#include "Moving_Object.h"
#include "Moving_Platform.h"
#include "Object.h"
#include "Player.h"

void Moving_Object::gravity()
{
  if (yVel < 20)
    {
      yVel++;
      
      if(yVel > 1)
      inAir = true;
    } 
}

bool Moving_Object::collision(Object* o)
{
  if ( x + width +xVel      > o->x              //Left
       && x + xVel          < o->x + o->width   //Right
       && y + yVel + height > o->y              //Top
       && y + yVel          < o->y + o->height) //Bottom
     {  
         return true;
     }
     else
         return false;         
}

void Moving_Object::bulletMovement()
{
  x += moveSpeed;
  x += xVel;
  y += yVel;
}
