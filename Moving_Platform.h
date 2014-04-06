#include "Moving_Object.h"

class Moving_Platform : public Moving_Object
{
 public:
 Moving_Platform(float x_, float y_, float width_, float height_, float moveSpeed_, std::string picture_, float to_):
  Moving_Object(x_, y_, width_, height_, moveSpeed_, picture_), to(to_) 
  {
    from = x_;
  }
  
  float from;
  float to;
  
  void elevate();
};
