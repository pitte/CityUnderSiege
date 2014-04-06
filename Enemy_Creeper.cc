#include "Enemy_Creeper.h"

void Enemy_Creeper::aiCreeper(float playerX)
{
  if(x < playerX)
      x += moveSpeed;
  
  else if(x > playerX)
      x -= moveSpeed;
}
