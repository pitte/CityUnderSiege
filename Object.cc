#include "Object.h"

Object::~Object()
{
  SDL_FreeSurface(img);                 
}

void Object::show(SDL_Surface* screen, float cameraX, float cameraY)
{
  if(animations == 0 || frames == 0)
    {
      currentFrame = 0;
    }
  else
    {
      currentFrame++;
      if(currentFrame > frames * animations || currentFrame < frames * (animations - 1) + 1)
	{
	  currentFrame = (  frames * (animations - 1) ) + 1;  
	}
    }
  applySurface(x + cameraX, y + cameraY, screen, &clips[currentFrame]);
}



void Object::applySurface(float x, float y, SDL_Surface* screen, SDL_Rect *clip = NULL)
{
  SDL_Rect offset;
  int x_ = int (x + 0.5);
  int y_ = int (y + 0.5);
  
  offset.x = x_;
  offset.y = y_; 
  
  SDL_BlitSurface(img, clip, screen, &offset);
}


SDL_Surface *Object::loadImage(std::string filename)
{
  SDL_Surface* loadedImage = NULL;
  SDL_Surface* optimizedImage = NULL;
  loadedImage = IMG_Load(filename.c_str());

  if(loadedImage != NULL)
    {
      optimizedImage = SDL_DisplayFormat(loadedImage);
      SDL_FreeSurface(loadedImage);
    }
  return optimizedImage;
}

void Object::setClips()
{
  clips[0].x = 0;
  clips[0].y = 0;
  clips[0].w = int(width + 0.5);
  clips[0].h = int(height + 0.5);
  
  int x = 1;
  
  for(int j = 0; j < animations; j++)
    {
      for (int i = 1; i <= frames; i++)
	{
	  clips[x].x = (i - 1) * int(width + 0.5);
	  clips[x].y = (j + 1) * int(height + 0.5);
	  clips[x].w = int(width + 0.5);
	  clips[x].h = int(height + 0.5);
	  x++;
	}      
    }
}
