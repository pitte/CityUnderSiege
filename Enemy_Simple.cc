#include "Enemy_Simple.h"

void Enemy_Simple::AI_Simple()
{
  //Går från From till To
  if (x < From)
    {
      MoveSpeed = MoveSpeed *-1;
    }
  if(x > To)
    {
      MoveSpeed = MoveSpeed *-1;
    }
  
  Animations = 1;
  
  x += MoveSpeed;
  
  //Hoppar
  if(!inAir)
    {
      yVel -= 18;
      inAir = true;
    }
  y += yVel;
}
