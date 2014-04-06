#include "Moving_Platform.h"

void Moving_Platform::elevate()
{
  if (x < from - 1)
    {
      moveSpeed = moveSpeed *-1;      
    }
  else if( x > to)
    {
      moveSpeed = moveSpeed *-1;
    }
  
  x += moveSpeed;
}
