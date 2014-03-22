#include "MovingObject.h"

class MovingPlatform : public MovingObject
{
 public:
 MovingPlatform(float x_, float y_, float Width_, float Height_, float MoveSpeed_, std::string Picture_, float To_):
  MovingObject(x_, y_, Width_, Height_, MoveSpeed_, Picture_), To(To_) 
  {
    From = x_;
  }
  
  float From;
  float To;
  
  
  void Elevate();
 
};
