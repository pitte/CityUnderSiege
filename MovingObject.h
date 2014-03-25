#ifndef MOVINGOBJECT_H
#define MOVINGOBJECT_H
#include "Object.h"
#include <string>
#include <vector>

/*
This object moves and needs to check collision with the world. 
It also has hitpoints and other variables handling movement.
 */

class MovingObject : public Object
{
 public:
 MovingObject(float x_, float y_, float Width_, float Height_, float MoveSpeed_, std::string Picture_, float Health_ = '1', int Frames_ = 0, int Animations_ = 0) 
   : Object(x_, y_, Height_, Width_, Picture_, Frames_, Animations_), xVel(0), yVel(0), MoveSpeed(MoveSpeed_), Health(Health_)
  {
    inAir = true;
  }

  void Gravity();
  void BulletMovement();
  bool Collision(Object* o);

  float Health;
  float xVel, yVel;
  float MoveSpeed;
  bool inAir;
  std::string Picture;
 
};

#endif
