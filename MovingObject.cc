#include "MovingPlatform.h"
#include "MovingObject.h"
#include "Object.h"
#include "Enemy.h"
#include "Player.h"

void MovingObject::Gravity()
{
  if (yVel < 20)
    {
      yVel++;
      
      if(yVel > 1)
      inAir = true;
    } 
}

bool MovingObject::Collision(Object* o)
{
  if ( x + Width +xVel      > o->x              //Left
       && x + xVel          < o->x + o->Width   //Right
       && y + yVel + Height > o->y              //Top
       && y + yVel          < o->y + o->Height) //Bottom
     {  
         return true;
     }
     else
         return false;         
}

void MovingObject::BulletMovement()
{
  x += MoveSpeed;
  x += xVel;
  y += yVel;
}
