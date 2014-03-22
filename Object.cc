#include "Object.h"

Object::~Object()
{
  SDL_FreeSurface(img);                 
}

void Object::Show(SDL_Surface* screen, float cameraX, float cameraY)
{

  if(Animations == 0 || Frames == 0)
    {
      CurrentFrame = 0;
    }
  else
    {
      CurrentFrame++;
      if(CurrentFrame > Frames * Animations || CurrentFrame < Frames * (Animations - 1) + 1)
	{
	  CurrentFrame = (  Frames * (Animations - 1) ) + 1;  
	}
    }

  apply_surface(x + cameraX, y + cameraY, screen, &clips[CurrentFrame]);
}



void Object::apply_surface(float x, float y, SDL_Surface* screen, SDL_Rect *clip = NULL)
{
  SDL_Rect offset;

      int x_ = int (x + 0.5);
      int y_ = int (y + 0.5);
    
      offset.x = x_;
      offset.y = y_;
    

    SDL_BlitSurface(img, clip, screen, &offset);
}


SDL_Surface *Object::load_image(std::string filename)
{
  SDL_Surface* loaded_image = NULL;

  SDL_Surface* optimized_image = NULL;

  loaded_image = IMG_Load(filename.c_str());

  if(loaded_image != NULL)
    {
      optimized_image = SDL_DisplayFormat(loaded_image);

      SDL_FreeSurface(loaded_image);
    }


  return optimized_image;
}

void Object::set_clips()
{
     
  clips[0].x = 0;
  clips[0].y = 0;
  clips[0].w = int(Width + 0.5);
  clips[0].h = int(Height + 0.5);

  int X = 1;

for(int j = 0; j < Animations; j++)
 {
      for (int i = 1; i <= Frames; i++)
	{
	  clips[X].x = (i - 1) * int(Width + 0.5);
	  clips[X].y = (j + 1) * int(Height + 0.5);
	  clips[X].w = int(Width + 0.5);
	  clips[X].h = int(Height + 0.5);
	  X++;
	}

 }

}
