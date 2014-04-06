#ifndef MOVINGOBJECT_H
#define MOVINGOBJECT_H
#include "Object.h"
#include <string>
#include <vector>

/*
  This object moves and needs to check collision with the world. 
  It also has hitpoints and other variables handling movement.
 */
class Moving_Object : public Object
{
 public:
 Moving_Object(float x_, float y_, float width_, float height_, float moveSpeed_, std::string picture_, float health_ = '1', int frames_ = 0, int animations_ = 0) 
   : Object(x_, y_, height_, width_, picture_, frames_, animations_), xVel(0), yVel(0), moveSpeed(moveSpeed_), health(health_)
  {
    inAir = true;
  }

  void gravity();
  void bulletMovement();
  bool collision(Object* o);

  float health;
  float xVel, yVel;
  float moveSpeed;
  bool inAir;
  std::string picture;
};

#endif
