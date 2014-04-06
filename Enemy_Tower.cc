#include "Enemy_Tower.h"

void Enemy_Tower::aiTower()
{
  //Movement in y-axis.
  if(y > from)
    moveSpeed = moveSpeed*-1;
  if(y < to)
    moveSpeed = moveSpeed*-1;

  y -= moveSpeed;
}

void Enemy_Tower::towerShoot(float targetX, float targetY, float& xVel, 
			      float& yVel)
{
  float adjacent, opposite, hyp;
  float arctan;

  adjacent = targetX - x; //Adjacent side.
  opposite = targetY - x; //Opposite side.
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
