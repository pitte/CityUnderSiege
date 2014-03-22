#include "Enemy_Creeper.h"


void Enemy_Creeper::AI_Creeper(float playerx)
{
  if(x < playerx)
    {
      x += MoveSpeed;
    }
  
  else if(x > playerx)
    {
      x -= MoveSpeed;
    }
}
