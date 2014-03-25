#ifndef ENEMYSIMPLE_H
#define ENEMYSIMPLE_H
#include "Enemy.h"


class Enemy_Simple : public Enemy
{
 public:
 Enemy_Simple(float x_, float y_, float Width_, float Height_, float MoveSpeed_, std::string Picture_, float Health_, 
	      float To_, int Frames_ = 0, int Animations_ = 0, int GroundLevel_ = 566)
   : Enemy(x_, y_, Width_, Height_, MoveSpeed_, Picture_, Health_, To_, Frames_, Animations_), GroundLevel(GroundLevel_) 
  {
    From = x_;
  }
  
  void AI_Simple();
  
  float From;
  int GroundLevel;
};

#endif
