#ifndef ENEMYTOWER_H
#define ENEMYTOWER_H
#include "Enemy.h"
#include <complex>
#include <valarray>
#include <stdio.h>
#include <math.h>

class Enemy_Tower : public Enemy
{
 public:
 Enemy_Tower(float x_, float y_, float Width_, float Height_, float MoveSpeed_, std::string Picture_, float Health_, float To_, int Range_, int ShootDelay_, int Frames_ = 0, int Animations_ = 0)
   : Enemy(x_, y_, Width_, Height_, MoveSpeed_, Picture_, Health_, To_, Frames_, Animations_), Range(Range_), ShootDelay(ShootDelay_)
    {
      From = y_;
      ShootCount = 0;
    }
  
  void AI_Tower();
  void Tower_Shoot(float TargetX, float TargetY, float& xVel, float& yVel);

  bool TowerFire;
  int ShootCount;
  int Range;
  int ShootDelay;
  float From;

};

#endif
