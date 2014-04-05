#include "Enemy_Tower.h"

void Enemy_Tower::AI_Tower()
{
  //Movement in y-axis.
  if(y > From)
    MoveSpeed = MoveSpeed*-1;
  if(y < To)
    MoveSpeed = MoveSpeed*-1;

  y -= MoveSpeed;
}


void Enemy_Tower::Tower_Shoot(float TargetX, float TargetY, float& xVel, 
			      float& yVel)
{
  float adjacent, opposite, hyp;
  float arctan;

  adjacent = TargetX - x; //Adjacent side.
  opposite = TargetY - x; //Opposite side.
  arctan = atan(adjacent/opposite); //Degrees.
  
  xVel = sin(arctan);
  yVel = cos(arctan);
  
  if(adjacent > 0 && opposite > 0) {
      xVel = sin(arctan)*3;
      yVel = cos(arctan)*3;
    }
  else if(adjacent > 0 && opposite < 0) {
      xVel = (-sin(arctan))*3;
      yVel = (-cos(arctan))*3;
    }
  else if(adjacent < 0 && opposite > 0) {
      xVel = sin(arctan)*3;
      yVel = cos(arctan)*3;
    }
  else if(adjacent < 0 && opposite < 0) {
      xVel = (-sin(arctan))*3;
      yVel = (-cos(arctan))*3;
    }
}
