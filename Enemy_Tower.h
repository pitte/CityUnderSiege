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
 Enemy_Tower(float x_, float y_, float width_, float height_, float moveSpeed_, std::string picture_, float health_, 
	     float to_, int range_, int shootDelay_, int frames_ = 0, int animations_ = 0)
   : Enemy(x_, y_, width_, height_, moveSpeed_, picture_, health_, to_, 
	   frames_, animations_), range(range_), shootDelay(shootDelay_)
  {
    from = y_;
    shootCount = 0;
  }
  
  void aiTower();
  void towerShoot(float targetX, float targetY, float& xVel, float& yVel);

  bool towerFire;
  int shootCount;
  int range;
  int shootDelay;
  float from;
};

#endif
