#ifndef OBJECT_H
#define OBJECT_H
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_mixer.h"
#include <string>
#include <vector>

/*
Base class. Contains functions every subclass uses: how to draw the object 
on screen.
 */

class Object
{
 public:
 Object(float x_, float y_, float Height_, float Width_, std::string Picture_, int Frames_ = 0, int Animations_ = 0)
   : x(x_), y(y_), Width(Width_), Height(Height_), Frames(Frames_), Animations(Animations_), Picture(Picture_)
  {
    set_clips();
    img = IMG_Load(Picture_.c_str());
    CurrentFrame = 0;
    Animations = 0;
  }
  //Virtual in order to be polymorph.
  virtual ~Object();


  void Show(SDL_Surface* screen, float cameraX, float cameraY);

  void apply_surface(float x, float y, SDL_Surface* screen, SDL_Rect *clip);
    
  SDL_Surface *load_image(std::string filename);

  void set_clips();
  
  float x, y;
  float Height;
  float Width;
  SDL_Surface *img;
  SDL_Rect clips[30];
  
  int Frames;
  int CurrentFrame;
  int Animations;
  std::string Picture;

};

#endif
