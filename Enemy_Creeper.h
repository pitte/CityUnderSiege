#ifndef ENEMYCREEPER_H
#define ENEMYCREEPER_H
#include "Enemy.h"

class Enemy_Creeper : public Enemy
{
 public:
 Enemy_Creeper(float x_, float y_, float Width_, float Height_, float MoveSpeed_, std::string Picture_, float Health_, 
	       int Range_, int Frames_ = 0, int Animations_ = 0)
   : Enemy(x_, y_, Width_, Height_, MoveSpeed_, Picture_, Health_, Frames_, Animations_), Range(Range_) {}
  
  void AI_Creeper(float playerx);
  
  float playerx;
  int Range;
};

#endif
