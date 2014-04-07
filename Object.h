#ifndef OBJECT_H
#define OBJECT_H
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_mixer.h"
#include <string>
#include <vector>

/*
  Base class. Contains functions every subclass uses i.e. how to draw the object
  on screen.
 */
class Object
{
 public:
 Object(float x_, float y_, float height_, float width_, std::string picture_, int frames_ = 0, int animations_ = 0)
   : x(x_), y(y_), width(width_), height(height_), frames(frames_), animations(animations_), picture(picture_)
  {
    setClips();
    img = IMG_Load(picture_.c_str());
    currentFrame = 0;
    animations = 0;
  }
  //Virtual destructor in order to be polymorph.
  virtual ~Object();

  void show(SDL_Surface* screen, float cameraX, float cameraY);
  void applySurface(float x, float y, SDL_Surface* screen, SDL_Rect *clip);
  SDL_Surface *loadImage(std::string filename);
  void setClips();
  
  float x, y;
  float height;
  float width;
  SDL_Surface *img;
  SDL_Rect clips[30];
  int frames;
  int currentFrame;
  int animations;
  std::string picture;
};

#endif
