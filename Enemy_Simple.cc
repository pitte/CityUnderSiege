#include "Enemy_Simple.h"

void Enemy_Simple::aiSimple()
{
  //Walk From to To.
  if (x < from)
      moveSpeed = moveSpeed *-1;
  if(x > to)
      moveSpeed = moveSpeed *-1;
  
  animations = 1;
  x += moveSpeed;
  
  //Jump.
  if(!inAir) {
      yVel -= 18;
      inAir = true;
    }
  y += yVel;
}
