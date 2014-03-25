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
  float narl, mots, hyp, grader;
  float arctan;

  narl = TargetX - x; //Adjacent side.
  mots = TargetY - x; //Opposite side.
  
  arctan = atan(narl/mots); //Degrees.
  
  xVel = sin(arctan);
  yVel = cos(arctan);
  
  if(narl > 0 && mots > 0) {
      xVel = sin(arctan)*3;
      yVel = cos(arctan)*3;
    }
  else if(narl > 0 && mots < 0) {
      xVel = (-sin(arctan))*3;
      yVel = (-cos(arctan))*3;
    }
  else if(narl < 0 && mots > 0) {
      xVel = sin(arctan)*3;
      yVel = cos(arctan)*3;
    }
  else if(narl < 0 && mots < 0) {
      xVel = (-sin(arctan))*3;
      yVel = (-cos(arctan))*3;
    }
}
