#ifndef ENEMY_H
#define ENEMY_H
#include "MovingObject.h"


class Enemy : public MovingObject
{
 public:
 Enemy(float x_, float y_, float Width_, float Height_, float MoveSpeed_, std::string Picture_, float Health_, float To_, 
       int Frames_ = 0, int Animations_ = 0)
   : MovingObject(x_, y_, Width_, Height_, MoveSpeed_, Picture_, Health_, Frames_, Animations_), To(To_) {}
  
  void EnemyMove(std::vector<Object*> Platforms);
  float To;
};

#endif
