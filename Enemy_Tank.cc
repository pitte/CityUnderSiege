#include "Enemy_Tank.h"


void Enemy_Tank::AI_Tank(float playerx)
{
  if(x  < playerx - 127)
    x += MoveSpeed;

  if(x  > playerx - 127)
    x -= MoveSpeed;
}
