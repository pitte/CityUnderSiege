#include "MovingPlatform.h"

void MovingPlatform::Elevate()
{
  if (x < From - 1)
    {
      MoveSpeed = MoveSpeed *-1;      
    }
  else if( x > To)
    {
      MoveSpeed = MoveSpeed *-1;
    }
  
  x += MoveSpeed;
}
