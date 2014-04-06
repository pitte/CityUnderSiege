#ifndef ENEMYCREEPER_H
#define ENEMYCREEPER_H
#include "Enemy.h"

class Enemy_Creeper : public Enemy
{
 public:
 Enemy_Creeper(float x_, float y_, float width_, float height_, float moveSpeed_, std::string picture_, float health_, 
	       int range_, int frames_ = 0, int animations_ = 0)
   : Enemy(x_, y_, width_, height_, moveSpeed_, picture_, health_, frames_, animations_), range(range_) {}
  
  void aiCreeper(float playerX);
  
  float playerX;
  int range;
};

#endif
