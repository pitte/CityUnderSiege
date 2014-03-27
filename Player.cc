#include "MovingPlatform.h"
#include "MovingObject.h"
#include "Object.h"
#include "Enemy.h"
#include "Enemy_Creeper.h"
#include "Player.h"

void Player::Handle_Input(SDL_Event event, Mix_Chunk* Player_Shoot, Mix_Chunk* Player_Jump)
{
  if(event.type == SDL_KEYDOWN)
    {
      switch(event.key.keysym.sym)
	{
	case SDLK_UP:
	  if(!inAir)
	    {
	      yVel -= 20; inAir = true;
	      Mix_PlayChannel(-1, Player_Jump, 0);
	    }
	  break;
	case SDLK_LEFT: LeftKey = true; PrevLeft = true; PrevRight = false;
	  break; 
	case SDLK_RIGHT: RightKey = true; PrevLeft = false; PrevRight = true;
	  break;
	case SDLK_LCTRL: Shoot = true;
	  if(Ammo != 0)
	    Mix_PlayChannel(-1, Player_Shoot, 0);
	  break;
	case SDLK_LALT: Use = true;
	  break;	  
	default: break;
	}
    }
  else if(event.type == SDL_KEYUP)
    {
      switch(event.key.keysym.sym)
	{	  
	case SDLK_LEFT:
	  LeftKey = false;  
          break;       
	case SDLK_RIGHT:
          RightKey = false;
          break;	  
	case SDLK_LCTRL:
	  Shoot = false;
	  break;	  
	case SDLK_LALT:
	  Use = false;
	  break;	  
	case SDLK_ESCAPE:
	  Paus_Menu = !Paus_Menu;
	  break;	  
	default: break;
	}
    }
}

void Player::Move(std::vector<Object*>& Platforms, std::vector<Object*>& Bullets, Mix_Chunk* Player_Hurt,  Mix_Chunk* Player_Jumps_Enemy, Mix_Chunk* Enemy_Dies)
{
  MovingPlatform* mp;
  Enemy* enemy;
  MovingObject* bullet;
  Object* bulletobject;
  bool IsMovingPlatform = false;
  bool disappear = false;
  
  for(int b = 0; b < Bullets.size(); b++)
    {
      bulletobject = dynamic_cast<Object*>(Bullets[b]);
      if(Collision(Bullets[b]) && bulletobject->Picture == "bild/laser.png")
	{
	  if(!NoHurt)
	    { 
	      Health -= 1;
	      Mix_PlayChannel(-1, Player_Hurt, 0);
	    }
	  NoHurt = true;
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
      mp = dynamic_cast<MovingPlatform*>(Platforms[i]);
      enemy = dynamic_cast<Enemy*>(Platforms[i]);
      
      if( mp != 0)
	{
	  IsMovingPlatform = true;
	}
      
      if( Collision(Platforms[i]) )
	{
	  float yTemp = yVel;
	  float xTemp = xVel;
	  
	  if(Platforms[i]->Picture == "bild/weaponcrate.png")
	    {
	      if( Platforms.at(i) != NULL )
		{
		  delete Platforms.at(i);
		  Platforms.at(i) = NULL;
		  Platforms.erase(Platforms.begin()+i);
		}

	      int ammonum = 5;
	      while(ammonum != 0 && Ammo != 20)
		{
		  Ammo++;
		  ammonum--;
		}
	      continue; 
	    }
	  else if(Platforms[i]->Picture == "bild/healthcrate.png")
	    {
	      if( Platforms.at(i) != NULL )
		{
		  delete Platforms.at(i);
		  Platforms.at(i) = NULL;
		  Platforms.erase(Platforms.begin()+i);
		}
	      if(Health != 5)
		Health += 1;
	      continue;
	    } 
	  /*
	    else if(Platforms[i]->Picture == "bild/levelComplete.png") //måste skicka med dessa bools i funktionen.
	    {
	    quit = false;
	    Game = false;
	    Start_Menu = true;
	    }
	  */
	  else
	    yVel = 0;
	      
	  //Collision X-axis.
	  if(Collision(Platforms[i]))
	    {
	      if(xVel == 0)
		{
		  if(IsMovingPlatform)
		    {
		      if(mp->MoveSpeed > 0)
			x = Platforms[i]->x + Platforms[i]->Width;
		      else
			x = Platforms[i]->x - Width;
		    }		  
		  else if(enemy != 0)
		    {
		      if(!NoHurt)
			{ 
			  Health -= 1;
			  Mix_PlayChannel(-1, Player_Hurt, 0);
			}
		      NoHurt = true;
		      if(enemy->x < x)
			{
			  x = enemy->x + enemy->Width;
			  xVel = (MoveSpeed+5);
			}		      
		      else
			{
			  x = enemy->x - Width;
			  xVel = (MoveSpeed+5) * -1;
			}
		      yTemp = -7;
		      inAir = true;
		    }
		}
	      else if(xVel > 0)
		{
		  x = Platforms[i]->x - Width - xVel;
		  if(enemy != 0)
		    {
		      if(!NoHurt)
			{ 
			  Health -= 1;
			  Mix_PlayChannel(-1, Player_Hurt, 0);
			}
		      NoHurt = true;
		      xVel = (MoveSpeed+5)*-1;
		      yTemp = -7;
		      inAir = true;
		    }
		}
	      else
		{
		  x = Platforms[i]->x + Platforms[i]->Width - xVel;
		  if(enemy != 0)
		    { 
		      if(!NoHurt)
			{ 
			  Health -= 1;
			  Mix_PlayChannel(-1, Player_Hurt, 0);
			}
		      NoHurt = true;
		      xVel = (MoveSpeed+5);
		      yTemp = -7;
		      inAir = true;
		    }
		}
	      if(Platforms[i]->Picture == "bild/Blocks/flyblockup.jpg")
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
	  if(Collision(Platforms[i]))
	    {
	      if(yVel > 0 && enemy != 0)
		{
		  if(enemy != 0)
		    { 
		      yVel = yVel *-1;
		      enemy->Health -= 1;
		      Mix_PlayChannel(-1, Player_Jumps_Enemy, 0);
		      if(enemy->Health == 0)
			{
			  if(Platforms.at(i) != NULL)
			    {
			      delete Platforms.at(i);
			      Platforms.at(i) = NULL;
			      Platforms.erase(Platforms.begin()+i);
			    }
			  Mix_PlayChannel(-1, Enemy_Dies, 0);
			  continue;
			}
		    }
		}	      
	      else if(yVel > 0 && Platforms[i]->Picture == "bild/Blocks/redblock.png")
		{
		  yVel = yVel*-1.5;
		}	      
	      else if(yVel > 0)
		{
		  if(IsMovingPlatform)
		    {
		      if(mp != 0)
			x += mp->MoveSpeed;
		    }		  
		  yVel = 0;
		  y = Platforms[i]->y - Height;
		  inAir = false;		  
		}
	      else
		{		  
		  yVel = 0;
		  y = Platforms[i]->y + Platforms[i]->Height;  	  
		}
	    }                        
	  xVel = xTemp;
	}
    }

  x += xVel;
  y += yVel;          
}

void Player::Friction()
{
  if(!RightKey && !LeftKey)
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

void Player::SetCamera(int screen_width, int screen_height, int& bgX, int& bgY, SDL_Surface*& background)
{
  //X-axis.
  if((x + CameraX) > (screen_width - 400))
    {
      CameraX += ( (x+CameraX)  - (screen_width - 400) ) * -1;
      bgX = int(CameraX + 0.5) % background->w; 
      if(bgX <= -background->w)
	{
	  bgX = 0;
	}
    }
  else if((x + CameraX) < 400)
    {
      CameraX += 400 - (x + CameraX);
      bgX = int(CameraX + 0.5) % background->w ;
      if(bgX >= background->w)
	{
	  bgX = 0; 
	}
    }
  //Y-axis.
  if((y + CameraY) > (screen_height - 275))
    {
      CameraY += ( (y + CameraY)  - (screen_height - 275) ) * -1;
    }
  else if((y + CameraY) < 150)
    {
      CameraY += 150 - (y + CameraY);
    }
}

void Player::Handle_Player(int screen_width, int screen_height, int& bgX, int& bgY, SDL_Surface*& background)
{    
  Gravity();
  Friction();
  SetCamera(screen_width, screen_height, bgX, bgY, background);      
    if(LeftKey && !RightKey)
      {
	if(xVel > MoveSpeed*-1)
	  xVel --;

	Animations = 2; 

	if(NoHurt)
	  Animations = 4;  
      }
    else if(RightKey && !LeftKey)
      {
	if(xVel < MoveSpeed)
	  xVel++;

	Animations = 1;  
 
	if(NoHurt)
	  Animations = 3;    
      }
    else if(LeftKey)
      {
	Animations = 2;

	if(NoHurt)
	  Animations = 4;
      }
    else if(RightKey)
      {
	Animations = 1;

	if(NoHurt)
	  Animations = 3;
      }
    else
      {
	if(PrevRight)
	  {
	    Animations = 0; 
      
	    if(NoHurt)
	      Animations = 5;
	  }  
	else if(PrevLeft)
	  {
	    Animations = 7; 
      
	    if(NoHurt)
	      Animations = 6;	  
	  }
      }
  }

int Player::Shooting()
{
  int direction;
  if(PrevRight)
    {
      direction = 10;
      return direction;
    }
  if(PrevLeft)
    {
      direction = -10;
      return direction;
    }
}

void Player::DisplayHealth(SDL_Surface* screen)
{
  //Falling down.
  if(y > 1500)
    Health = 0;

  int Health_ = int(Health);
  SDL_Rect offset;

  offset.x = 5;
  offset.y = 5;  
 
  for(int i = 0; i < Health_; i++)
    {
      SDL_BlitSurface(HeartPic, NULL, screen, &offset);
      offset.x += 40;
    }
}

void Player::DisplayAmmo(SDL_Surface* screen)
{
  SDL_Rect offset;

  offset.x = 1004;
  offset.y = 5;
  
  for(int i = 0; i < Ammo; i++)
    {
      SDL_BlitSurface(BulletPic, NULL, screen, &offset);
      offset.x -= 15;
    }
}
