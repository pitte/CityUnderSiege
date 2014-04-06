#include "Enemy.h"
#include "Enemy_Creeper.h"
#include "Moving_Object.h"
#include "Moving_Platform.h"
#include "Object.h"
#include "Player.h"

void Player::handleInput(SDL_Event event, Mix_Chunk* playerShoot, Mix_Chunk* playerJump)
{
  if(event.type == SDL_KEYDOWN)
    {
      switch(event.key.keysym.sym)
	{
	case SDLK_UP:
	  if(!inAir)
	    {
	      yVel -= 20; inAir = true;
	      Mix_PlayChannel(-1, playerJump, 0);
	    }
	  break;
	case SDLK_LEFT: leftKey = true; prevLeft = true; prevRight = false;
	  break; 
	case SDLK_RIGHT: rightKey = true; prevLeft = false; prevRight = true;
	  break;
	case SDLK_LCTRL: shoot = true;
	  if(ammo != 0)
	    Mix_PlayChannel(-1, playerShoot, 0);
	  break;
	case SDLK_LALT: use = true;
	  break;	  
	default: break;
	}
    }
  else if(event.type == SDL_KEYUP)
    {
      switch(event.key.keysym.sym)
	{	  
	case SDLK_LEFT:
	  leftKey = false;  
          break;       
	case SDLK_RIGHT:
          rightKey = false;
          break;	  
	case SDLK_LCTRL:
	  shoot = false;
	  break;	  
	case SDLK_LALT:
	  use = false;
	  break;	  
	case SDLK_ESCAPE:
	  pausMenu = !pausMenu;
	  break;	  
	default: break;
	}
    }
}

void Player::move(std::vector<Object*>& Platforms, std::vector<Object*>& Bullets, Mix_Chunk* playerHurt,  Mix_Chunk* playerJumpsEnemy, Mix_Chunk* enemyDies, bool& quit, bool& game, bool& startMenu)
{
  Moving_Platform* mp;
  Enemy* enemy;
  Moving_Object* bullet;
  Object* bulletObject;
  bool isMovingPlatform = false;
  bool disappear = false;
  
  for(int b = 0; b < Bullets.size(); b++)
    {
      bulletObject = dynamic_cast<Object*>(Bullets[b]);
      if(collision(Bullets[b]) && bulletObject->picture == "Images/laser.png")
	{
	  if(!noHurt)
	    { 
	      health -= 1;
	      Mix_PlayChannel(-1, playerHurt, 0);
	    }
	  noHurt = true;
	  if( Bullets.at(b) != NULL ) 
	    {
	      delete Bullets.at(b);
	      Bullets.at(b) = NULL;
	      Bullets.erase(Bullets.begin()+b);
	    }
	}
    }

  for (int i = 0; i < Platforms.size(); ++i)
    { 
      mp = dynamic_cast<Moving_Platform*>(Platforms[i]);
      enemy = dynamic_cast<Enemy*>(Platforms[i]);
      
      if( mp != 0)
	{
	  isMovingPlatform = true;
	}
      
      if( collision(Platforms[i]) )
	{
	  float yTemp = yVel;
	  float xTemp = xVel;
	  
	  if(Platforms[i]->picture == "Images/weaponcrate.png")
	    {
	      if( Platforms.at(i) != NULL )
		{
		  delete Platforms.at(i);
		  Platforms.at(i) = NULL;
		  Platforms.erase(Platforms.begin()+i);
		}

	      int ammoNum = 5;
	      while(ammoNum != 0 && ammo != 20)
		{
		  ammo++;
		  ammoNum--;
		}
	      continue; 
	    }
	  else if(Platforms[i]->picture == "Images/healthcrate.png")
	    {
	      if( Platforms.at(i) != NULL )
		{
		  delete Platforms.at(i);
		  Platforms.at(i) = NULL;
		  Platforms.erase(Platforms.begin()+i);
		}
	      if(health != 5)
		health += 1;
	      continue;
	    }	  
	  else if(Platforms[i]->picture == "Images/Exit_Game.jpg")
	    {
	      quit = false;
	      game = false;
	      startMenu = true;
	      Mix_PlayChannel(-1, enemyDies, 0);
	      break;
	    }	  
	  else
	    yVel = 0;
	      
	  //Collision X-axis.
	  if(collision(Platforms[i]))
	    {
	      if(xVel == 0)
		{
		  if(isMovingPlatform)
		    {
		      if(mp->moveSpeed > 0)
			x = Platforms[i]->x + Platforms[i]->width;
		      else
			x = Platforms[i]->x - width;
		    }		  
		  else if(enemy != 0)
		    {
		      if(!noHurt)
			{ 
			  health -= 1;
			  Mix_PlayChannel(-1, playerHurt, 0);
			}
		      noHurt = true;
		      if(enemy->x < x)
			{
			  x = enemy->x + enemy->width;
			  xVel = (moveSpeed+5);
			}		      
		      else
			{
			  x = enemy->x - width;
			  xVel = (moveSpeed+5) * -1;
			}
		      yTemp = -7;
		      inAir = true;
		    }
		}
	      else if(xVel > 0)
		{
		  x = Platforms[i]->x - width - xVel;
		  if(enemy != 0)
		    {
		      if(!noHurt)
			{ 
			  health -= 1;
			  Mix_PlayChannel(-1, playerHurt, 0);
			}
		      noHurt = true;
		      xVel = (moveSpeed+5)*-1;
		      yTemp = -7;
		      inAir = true;
		    }
		}
	      else
		{
		  x = Platforms[i]->x + Platforms[i]->width - xVel;
		  if(enemy != 0)
		    { 
		      if(!noHurt)
			{ 
			  health -= 1;
			  Mix_PlayChannel(-1, playerHurt, 0);
			}
		      noHurt = true;
		      xVel = (moveSpeed+5);
		      yTemp = -7;
		      inAir = true;
		    }
		}
	      if(Platforms[i]->picture == "Images/Blocks/flyblockup.jpg")
		{
		  yTemp -= 2;
		  yVel -= 2;
		  inAir = true;
		}
	    }
	  
     	  yVel = yTemp;
	  xTemp = xVel;
	  xVel = 0;	  

	  //Collision Y-axis.
	  if(collision(Platforms[i]))
	    {
	      if(yVel > 0 && enemy != 0)
		{
		  if(enemy != 0)
		    { 
		      yVel = yVel *-1;
		      enemy->health -= 1;
		      Mix_PlayChannel(-1, playerJumpsEnemy, 0);
		      if(enemy->health == 0)
			{
			  if(Platforms.at(i) != NULL)
			    {
			      delete Platforms.at(i);
			      Platforms.at(i) = NULL;
			      Platforms.erase(Platforms.begin()+i);
			    }
			  Mix_PlayChannel(-1, enemyDies, 0);
			  continue;
			}
		    }
		}	      
	      else if(yVel > 0 && Platforms[i]->picture == "Images/Blocks/redblock.png")
		{
		  yVel = yVel*-1.5;
		}	      
	      else if(yVel > 0)
		{
		  if(isMovingPlatform)
		    {
		      if(mp != 0)
			x += mp->moveSpeed;
		    }
		  yVel = 0;
		  y = Platforms[i]->y - height;
		  inAir = false;		  
		}
	      else
		{		  
		  yVel = 0;
		  y = Platforms[i]->y + Platforms[i]->height;  	  
		}
	    }                        
	  xVel = xTemp;
	}
    }

  x += xVel;
  y += yVel;          
}

void Player::friction()
{
  if(!rightKey && !leftKey)
    {
      if(xVel < 1 && xVel > -1)
	{
	  xVel = 0;        
	}
     else if(xVel > 0)
       {
	 xVel -= 0.3;
       }      
     else if(xVel < 0)
       {
	 xVel += 0.3;  
       }      
    } 
}

void Player::setCamera(int screenWidth, int screenHeight, int& bgX, int& bgY, SDL_Surface*& background)
{
  //X-axis.
  if((x + cameraX) > (screenWidth - 400))
    {
      cameraX += ( (x+cameraX)  - (screenWidth - 400) ) * -1;
      bgX = int(cameraX + 0.5) % background->w; 
      if(bgX <= -background->w)
	{
	  bgX = 0;
	}
    }
  else if((x + cameraX) < 400)
    {
      cameraX += 400 - (x + cameraX);
      bgX = int(cameraX + 0.5) % background->w ;
      if(bgX >= background->w)
	{
	  bgX = 0; 
	}
    }
  //Y-axis.
  if((y + cameraY) > (screenHeight - 275))
    {
      cameraY += ( (y + cameraY)  - (screenHeight - 275) ) * -1;
    }
  else if((y + cameraY) < 150)
    {
      cameraY += 150 - (y + cameraY);
    }
}

void Player::handlePlayer(int screenWidth, int screenHeight, int& bgX, int& bgY, SDL_Surface*& background)
{    
  gravity();
  friction();
  setCamera(screenWidth, screenHeight, bgX, bgY, background);
    if(leftKey && !rightKey)
      {
	if(xVel > moveSpeed*-1)	  
	  xVel --;	
	
	animations = 2; 
	
	if(noHurt)	  
	  animations = 4;	
      }
    else if(rightKey && !leftKey)
      {
	if(xVel < moveSpeed)
	  xVel++;

	animations = 1;  
 
	if(noHurt)
	  animations = 3;    
      }
    else if(leftKey)
      {
	animations = 2;

	if(noHurt)
	  animations = 4;
      }
    else if(rightKey)
      {
	animations = 1;

	if(noHurt)
	  animations = 3;
      }
    else
      {
	if(prevRight)
	  {
	    animations = 0; 
      
	    if(noHurt)
	      animations = 5;
	  }  
	else if(prevLeft)
	  {
	    animations = 7; 
      
	    if(noHurt)
	      animations = 6;	  
	  }
      }
  }

int Player::shooting()
{
  int direction;
  if(prevRight)
    {
      direction = 10;
      return direction;
    }
  if(prevLeft)
    {
      direction = -10;
      return direction;
    }
}

void Player::displayHealth(SDL_Surface* screen)
{
  //Falling down.
  if(y > 1500)
    health = 0;

  int health_ = int(health);
  SDL_Rect offset;

  offset.x = 5;
  offset.y = 5;  
 
  //Print.
  for(int i = 0; i < health_; i++)
    {
      SDL_BlitSurface(heartPic, NULL, screen, &offset);
      offset.x += 40;
    }
}

void Player::displayAmmo(SDL_Surface* screen)
{
  SDL_Rect offset;

  offset.x = 1004;
  offset.y = 5;
  
  //Print.
  for(int i = 0; i < ammo; i++)
    {
      SDL_BlitSurface(bulletPic, NULL, screen, &offset);
      offset.x -= 15;
    }
}
