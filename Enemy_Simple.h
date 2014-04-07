#ifndef ENEMYSIMPLE_H
#define ENEMYSIMPLE_H
#include "Enemy.h"

class Enemy_Simple : public Enemy
{
 public:
 Enemy_Simple(float x_, float y_, float width_, float height_, float moveSpeed_, std::string picture_, float health_, float to_, int frames_ = 0, int animations_ = 0, int groundLevel_ = 566)
   : Enemy(x_, y_, width_, height_, moveSpeed_, picture_, health_, to_, frames_, animations_), groundLevel(groundLevel_) 
  {
    from = x_;
  }
  
  void aiSimple();
  
  float from;
  int groundLevel;
};

#endif
