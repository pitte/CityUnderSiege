#ifndef ENEMY_H
#define ENEMY_H
#include "Moving_Object.h"

class Enemy : public Moving_Object
{
 public:
 Enemy(float x_, float y_, float width_, float height_, float moveSpeed_, std::string picture_, float health_, float to_, int frames_ = 0, int animations_ = 0)
   : Moving_Object(x_, y_, width_, height_, moveSpeed_, picture_, health_, frames_, animations_), to(to_) {}
  
  void enemyMove(std::vector<Object*> Platforms);
  float to;
};

#endif
