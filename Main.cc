#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_image.h"
#include "Object.h"
#include "MovingObject.h"
#include "fps.h"
#include "Player.h"
#include "Enemy.h"
#include "Enemy_Simple.h"
#include "Enemy_Creeper.h"
#include "Enemy_Tower.h"
#include "Enemy_Tank.h"
#include "MovingPlatform.h"
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>
#include <complex>
#include <valarray>
#include <stdio.h>
#include <math.h>
#include "Menu.cc"
#include "Load_Level.cc"
#include "Load_Sound.cc"

const int screen_width = 1024;
const int screen_height = 768;
const int screen_bpp = 32;
const int FRAMES_PER_SECOND = 45;
SDL_Surface *screen = NULL;
SDL_Event event;
Mix_Music* music = NULL;
Mix_Chunk* Player_Shoot = NULL;
Mix_Chunk* Player_Jump = NULL;
Mix_Chunk* Player_Hurt = NULL;
Mix_Chunk* Player_Jumps_Enemy = NULL;
Mix_Chunk* Enemy_Dies = NULL;
Mix_Chunk* Game_Over = NULL;

void handle_background( int x, int y, SDL_Surface* source, SDL_Surface* destination, float cameraY )
{
  SDL_Rect offset;
  //Current background.
  offset.x = x;
  offset.y = y + int(cameraY + 0.5 - 143);
  SDL_BlitSurface( source, NULL, destination, &offset );
  //Next background.
  offset.x = x + source->w;
  offset.y = y + int(cameraY + 0.5 - 143);
  SDL_BlitSurface( source, NULL, destination, &offset );
  //Previous background.
  offset.x = x - source->w;
  offset.y = y + int(cameraY + 0.5 - 143);
  SDL_BlitSurface( source, NULL, destination, &offset );
  //Next next background due to thin background.
  offset.x = x + 2*source->w;
  offset.y = y + int(cameraY + 0.5 - 143);
  SDL_BlitSurface( source, NULL, destination, &offset );
}

SDL_Surface *load_image(std::string filename)
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

bool init()
{
  if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
      return false;
    }
  if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
    {
      return false;
    }
  screen = SDL_SetVideoMode( screen_width, screen_height, screen_bpp, SDL_SWSURFACE );
  if( screen == NULL )
    {
      return false;
    }
  SDL_WM_SetCaption( "City Under Siege", NULL );

  return true;
}

void Tower_Shoot(float StartX, float StartY, float TargetX, float TargetY, float& xVel, float& yVel)
{
  float narl, mots, hyp, grader;
  float arctan;
  narl = TargetX - StartX; //Adjacent side.
  mots = TargetY - StartY; //Opposite side.  
  arctan = atan(narl/mots); //Degrees.
  xVel = sin(arctan);
  yVel = cos(arctan);
  
  if(narl > 0 && mots > 0)
    {
      xVel = sin(arctan)*3;
      yVel = cos(arctan)*3;
    }
  else if(narl > 0 && mots < 0)
    {
      xVel = (-sin(arctan))*3;
      yVel = (-cos(arctan))*3;
    }
  else if(narl < 0 && mots > 0)
    {
      xVel = sin(arctan)*3;
      yVel = cos(arctan)*3;
    }
  else if(narl < 0 && mots < 0)
    {
      xVel = (-sin(arctan))*3;
      yVel = (-cos(arctan))*3;
    }
}

void BulletHit(std::vector<Object*>& Platforms, std::vector<Object*>& Bullets, int playerx, int screen_width, int screen_height)
{
  for(int b = 0; b < Bullets.size(); b++) //Check all bullets.
    {
      MovingObject* bullet = dynamic_cast<MovingObject*>(Bullets[b]);
      for(int p = 0; p < Platforms.size(); p++) //Check collision with all objects except bullets.
	{
	  Enemy* enemy;
	  Enemy_Tower* enemy_tower;
	  
	  if(bullet->Collision(Platforms[p]))
	    {
	      enemy = dynamic_cast<Enemy*>(Platforms[p]);
	      enemy_tower = dynamic_cast<Enemy_Tower*>(Platforms[p]);
	      
	      if(bullet->Collision(Platforms[p]) && enemy_tower == 0)
		{
		  if( Bullets.at(b) != NULL ) //Remove bullet.
		    {
		      delete Bullets.at(b);
		      Bullets.at(b) = NULL;
		      Bullets.erase(Bullets.begin()+b);
		    }
		  if(enemy != 0 && enemy->Health != 0) //Enemy hit but not dead.
		    {
		      enemy->Health -= 1;
		    }
		  else if(enemy != 0 && enemy->Health == 0) //Killed enemy.
		    {
		      if( Platforms.at(p) != NULL ) //Remove enemy so that it is not blitted on screen.
			{
			  delete Platforms.at(p);
			  Platforms.at(p) = NULL;
			  Platforms.erase(Platforms.begin()+p);
			}
		    }
		}
	      //If shot outside screen +/- 774, remove it.
	      else if(bullet->x > (playerx + 774) || bullet->x < (playerx - 774))
		{
		  if( Bullets.at(b) != NULL ) 
		    {
		      delete Bullets.at(b);
		      Bullets.at(b) = NULL;
		      Bullets.erase(Bullets.begin()+b);
		    }
		}
	    }
	}
    }
}

int main(int argc, char* args[])
{
  int Start_Menu_Position = 0;
  int Paus_Menu_Position = 0;
  int Select_Level_Position = 0;
  int Game_Over_Position = 0;
  bool Paus_Menu = false;
  bool Start_Menu = true;
  bool Game = false;
  bool quit = false;
  bool Load_Level = false;
  bool Select_Level = false;
  std::string level;
  int NoHurtCounter = 0;
  std::vector<Object*> Start_Menu_V;
  Start_Menu_V.push_back(new Object(95, 0, 180, 800, "bild/New_Game.jpg")); //0
  Start_Menu_V.push_back(new Object(120, 0, 180, 800, "bild/New_Game_Markerad.jpg")); 
  Start_Menu_V.push_back(new Object(95, 220, 180, 800, "bild/Select_Level.jpg")); //4
  Start_Menu_V.push_back(new Object(115, 220, 180, 800, "bild/Select_Level_Markerad.jpg"));
  Start_Menu_V.push_back(new Object(95, 440, 180, 800, "bild/Exit_Game.jpg")); //6
  Start_Menu_V.push_back(new Object(120, 440, 180, 800, "bild/Exit_Game_Markerad.jpg"));
  std::vector<Object*> Paus_Menu_V;  
  Paus_Menu_V.push_back(new Object(100, 0, 180, 800, "bild/Resume_Game.jpg") );
  Paus_Menu_V.push_back(new Object(120, 0, 180, 800, "bild/Resume_Game_Markerad.jpg") );
  Paus_Menu_V.push_back(new Object(100, 180, 180, 800, "bild/Exit_Game.jpg") );
  Paus_Menu_V.push_back(new Object(120, 180, 180, 800, "bild/Exit_Game_Markerad.jpg") );
  std::vector<Object*> Game_Over_V;
  Game_Over_V.push_back(new Object(5, 200, 180, 1300, "bild/Restart.png") );
  Game_Over_V.push_back(new Object(50, 200, 180, 1300, "bild/Restart_Markerad.png") );
  Game_Over_V.push_back(new Object(5, 380, 180, 800, "bild/Main_Menu.png") );
  Game_Over_V.push_back(new Object(50, 380, 180, 800, "bild/Main_Menu_markerad.png") );
  Game_Over_V.push_back(new Object(0, 0, screen_height, screen_width, "bild/Game_Over.jpg") );
  std::vector<Object*> Select_Level_V;
  Select_Level_V.push_back(new Object(5, 200, 180, 1300, "bild/Level1.png") );
  Select_Level_V.push_back(new Object(25, 200, 180, 1300, "bild/Level1_markerad.png") );
  Select_Level_V.push_back(new Object(5, 350, 180, 800, "bild/Level2.png") );
  Select_Level_V.push_back(new Object(25, 350, 180, 800, "bild/Level2_markerad.png") );
  Select_Level_V.push_back(new Object(5, 500, 180, 800, "bild/Back.png") );
  Select_Level_V.push_back(new Object(25, 500, 180, 800, "bild/Back_markerad.png") );
  Player player(4700, 650, 40, 79, 8, "bild/PlayerAnimations.png", 5, 3, 7);
  player.Width = 35;
  Timer fps;
  MovingPlatform* mp;
  Object* checkpic;
  Enemy* enemy;
  Enemy_Simple* enemy_simple;
  Enemy_Creeper* enemy_creeper;
  Enemy_Tower* enemy_tower;
  Enemy_Tank* enemy_tank;
  MovingObject* bullet1;
  MovingObject* bullet2;
  MovingObject* bulletloop;
  Object* Leverpointer;
  Object* Blockpointer;
  bool launched = false;
  bool Created = false, Created2 = false, Created3 = false;
  bool Created4 = false, Created5 = false;
  int ShootCount = 0;
  std::vector<Object*> Platforms, Bullets;
  std::string BackgroundName;
  SDL_Surface *background = NULL;
  int bgX = 0, bgY = 0;

  if( init() == false )
    {
      return 1;
    }

  while( quit == false ) //Main game loop.
    {
      while(Start_Menu == true) //Start menu loop.
	{
	  Mix_HaltMusic();
	  if(Start_Game_Menu(quit, Game, Start_Menu, Load_Level, Select_Level, screen, event, level, player, Start_Menu_Position, 
			     Start_Menu_V) == 1) 
	    {
	      return 1;    
	    }
	  while(Select_Level == true)
	    {    
	      if(Select_Level_Menu(Select_Level, Load_Level, Start_Menu, quit, Game, player.Game_Over, screen, event, level, 
				   Select_Level_Position, Select_Level_V, player) == 1)
		{
		  return 1;	      
		}
	    }
	}
      while (player.Paus_Menu == true) //Paus menu loop.
	{
	  if( Paus_Menu_F(Start_Menu, Game, quit, player.Paus_Menu, screen, event, Paus_Menu_Position, Paus_Menu_V) == 1) 
	    {
	      return 1;	  
	    }
	}
      while (player.Game_Over == true) //Game over screen loop.
	{
	  Mix_HaltMusic();
	  if( Game_Over_Menu(Load_Level, quit, Game, Start_Menu, player.Paus_Menu, player.Game_Over, screen, event, screen_height, 
			     screen_width, Game_Over_Position, Game_Over_V, level, player) == 1) 
	    {
	      return 1; 	  
	    }
	}
      if (Load_Level == true)
	{
	  Load_Level = false;
	  load_level(Platforms, level, BackgroundName, player, Bullets);
	  background = IMG_Load( BackgroundName.c_str() );
	  Load_Sound(level, music, Player_Shoot, Player_Jump, Player_Hurt, Player_Jumps_Enemy, Enemy_Dies, Game_Over);
	}
      if (Game == true) //Active game loop.
	{
	  fps.start();
	  while( SDL_PollEvent( &event ) ) //Key pressed, handle the input.
	    {
	      player.Handle_Input(event, Player_Shoot, Player_Jump);
	      if( event.type == SDL_QUIT ) 
		{
		  quit = true;
		  Game = false;
		}
	    }
	  if(Mix_PlayingMusic() == 0) //Start music.
	    {
	    if( Mix_PlayMusic(music, -1) == -1 )
		{
		  return 1;
		}
	    }
	  if(player.Shoot && player.Ammo != 0) //Player shoots. If he has ammo spawn bullet.
	    {
	      int speed = player.Shooting();
	      if(speed > 0)
		{
		  bullet1 = new MovingObject(player.x+20, player.y+39, 8, 4, speed, "bild/bulletright.png");
		}
	      if(speed < 0)
		{
		  bullet1 = new MovingObject(player.x, player.y+39, 8, 4, speed, "bild/bulletleft.png");
		}
	  
	      Bullets.push_back(bullet1);
	      player.Shoot = false;
	      player.Ammo -= 1;
	    }	  
	  if(Bullets.size() != 0) //Handle movement of all bullets.
	    {
	      for(int i = 0; i < Bullets.size(); i++)
		{
		  bulletloop = dynamic_cast<MovingObject*>(Bullets[i]);
		  bulletloop->BulletMovement();
		}
	    }
	  
	  if(player.Health == 0) //Player dies.
	    {
	      player.yVel -= 50;
	    }
	  
	  for(int i = 0; i < Platforms.size(); ++i) //Handle AI for all enemies and platforms.
	    {
	      mp = dynamic_cast<MovingPlatform*>(Platforms[i]);
	      enemy = dynamic_cast<Enemy*>(Platforms[i]);
	      enemy_simple = dynamic_cast<Enemy_Simple*>(Platforms[i]);
	      enemy_creeper = dynamic_cast<Enemy_Creeper*>(Platforms[i]);
	      enemy_tower = dynamic_cast<Enemy_Tower*>(Platforms[i]);
	      
	      if(mp!=0)
		{
		  mp->Elevate();
		}
	      else if(enemy_simple != 0)
		{
		  if(enemy_simple->y > enemy_simple->GroundLevel) 
		    {
		      enemy_simple->inAir = false;
		    }		  
		  enemy_simple->AI_Simple();
		  enemy_simple->Gravity();
		}
	      else if(enemy_creeper != 0)
		{
		  if(player.x > enemy_creeper->x - enemy_creeper->Range && player.x < enemy_creeper->x + enemy_creeper->Range)
		    {
		      enemy_creeper->AI_Creeper(player.x);
		    }
		}
	      else if(enemy_tower != 0)
		{
		  enemy_tower->AI_Tower();

		  if((enemy_tower->x - enemy_tower->Range) < player.x && 
		     (enemy_tower->x + enemy_tower->Range) > player.x && 
		     (enemy_tower->y - enemy_tower->Range) < player.y && 
		     (enemy_tower->y + enemy_tower->Range) > player.y)
		    {		  
		      enemy_tower->ShootCount += 1;
		      if(enemy_tower->ShootCount > enemy_tower->ShootDelay)
			{
			  bullet2 = new MovingObject(enemy_tower->x+enemy_tower->Width/2-5, 
						     enemy_tower->y+enemy_tower->Height/2, 
						     10, 10, 0, "bild/laser.png");
			  Tower_Shoot(enemy_tower->x, enemy_tower->y, player.x, player.y, 
				      bullet2->xVel, bullet2->yVel);
			  Bullets.push_back(bullet2);
			  enemy_tower->ShootCount = 0;
			}
		    }
		}
	      if(enemy != 0 && enemy_simple == 0)
		{
		  enemy->EnemyMove(Platforms);
		}
	    }
	  
	  BulletHit(Platforms, Bullets, player.x, screen_width, screen_height); //Collision for bullets.
	  player.Handle_Player(screen_width, screen_height, bgX, bgY, background); //Handle gravity, friction and animations for player.
	  player.Move(Platforms, Bullets, Player_Hurt, Player_Jumps_Enemy, Enemy_Dies, quit, Game, Start_Menu); //Collision player-world.

	  //Player immortality-after-being-hurt-counter check.
	  if(player.NoHurt == true)
	    {
	      NoHurtCounter += 1;
	      if(NoHurtCounter >= 50)
	      {
		player.NoHurt = false;
		NoHurtCounter = 0;
	      }
	    }

	  //Print objects to screen.
	  if(level == "City_Level.txt")
	    {
	      SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0x26, 0xB8, 0xE9 ) );	  
	    }
	  if(level == "Forest_Level.txt")
	    {
	      SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0x79, 0xC9, 0xFA ) );	 
	    }
	  handle_background(bgX, bgY, background, screen, player.CameraY);
	  for(int i = 0; i < Bullets.size(); i++)
	    {
	      Bullets[i]->Show(screen, player.CameraX, player.CameraY);
	    }
	  player.Show(screen, player.CameraX, player.CameraY);      
	  for (int i = 0; i < Platforms.size(); i++)
	    {
	      Platforms[i]->Show(screen, player.CameraX, player.CameraY);
	    }      	  
      	  player.DisplayHealth(screen);
	  player.DisplayAmmo(screen);	  
	  if(SDL_Flip(screen) == -1)
	    {
	      return 1;
	    }
	  if( fps.get_ticks() < 1000 / FRAMES_PER_SECOND )
	    {
	      SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
	    }
	  
	  //Check if it is game over.
	  if (player.Health == 0)
	    {
	      player.Game_Over = true;
	      Game = false;
	    }
	}
    }
  
  //Exit program.
  SDL_FreeSurface(background);
  Mix_FreeChunk(Player_Shoot);
  Mix_FreeChunk(Player_Jump);
  Mix_FreeChunk(Player_Hurt);
  Mix_FreeChunk(Player_Jumps_Enemy);
  Mix_FreeChunk(Enemy_Dies);
  Mix_FreeChunk(Game_Over);
  Mix_FreeMusic(music);
  Mix_CloseAudio();

  SDL_Quit();
  return 0;
}
