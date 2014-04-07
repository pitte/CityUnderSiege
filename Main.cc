//SDL library.
#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_image.h"
//Standard includes.
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>
#include <complex>
#include <valarray>
#include <stdio.h>
#include <math.h>
//Our files.
#include "Object.h"
#include "Moving_Object.h"
#include "fps.h"
#include "Player.h"
#include "Enemy.h"
#include "Enemy_Simple.h"
#include "Enemy_Creeper.h"
#include "Enemy_Tower.h"
#include "Moving_Platform.h"
#include "Menu.cc"
#include "loadLevel.cc"
#include "loadSound.cc"
#include "fillVectors.cc"

const int screenWidth = 1024;
const int screenHeight = 768;
const int screenBpp = 32;
const int FRAMES_PER_SECOND = 45;
SDL_Surface *screen = NULL;
SDL_Event event;
Mix_Music* music = NULL;
Mix_Chunk* playerShoot = NULL;
Mix_Chunk* playerJump = NULL;
Mix_Chunk* playerHurt = NULL;
Mix_Chunk* playerJumpsEnemy = NULL;
Mix_Chunk* enemyDies = NULL;
Mix_Chunk* gameOver = NULL;

void bulletHit(std::vector<Object*>& Platforms, std::vector<Object*>& Bullets, int playerX, int screenWidth, int screenHeight);
void towerShoot(float startX, float startY, float targetX, float targetY, float& xVel, float& yVel);
bool init();
SDL_Surface *loadImage(std::string filename);
void handleBackground( int x, int y, SDL_Surface* source, SDL_Surface* destination, float cameraY );

int main(int argc, char* args[])
{
  int startMenuPosition = 0;
  int pausMenuPosition = 0;
  int selectLevelPosition = 0;
  int gameOverPosition = 0;
  bool pausMenu = false;
  bool startMenu = true;
  bool game = false;
  bool quit = false;
  bool loadLevelB = false;
  bool selectLevel = false;
  std::string level;
  int noHurtCounter = 0;
  std::vector<Object*> startMenuV;
  std::vector<Object*> pausMenuV;  
  std::vector<Object*> gameOverV;
  std::vector<Object*> selectLevelV;
  
  fillVectors(startMenuV, pausMenuV, gameOverV, selectLevelV, screenHeight, screenWidth);

  Player player(4700, 650, 40, 79, 8, "Images/PlayerAnimations.png", 5, 3, 7);
  player.width = 35;
  Timer fps;
  Moving_Platform* mp;
  Object* checkPic;
  Enemy* enemy;
  Enemy_Simple* enemySimple;
  Enemy_Creeper* enemyCreeper;
  Enemy_Tower* enemyTower;
  Moving_Object* bullet1;
  Moving_Object* bullet2;
  Moving_Object* bulletLoop;
  Object* leverPointer;
  Object* blockPointer;
  bool launched = false;
  bool created = false, created2 = false, created3 = false;
  bool created4 = false, created5 = false;
  int shootCount = 0;
  std::vector<Object*> Platforms, Bullets;
  std::string backgroundName;
  SDL_Surface *background = NULL;
  int bgX = 0, bgY = 0;

  if( init() == false )
    {
      return 1;
    }

  //Main game loop.
  while( quit == false ) 
    {
      //Start menu loop.
      while(startMenu == true) 
	{
	  Mix_HaltMusic();
	  if(startGameMenu(quit, game, startMenu, loadLevelB, selectLevel, screen, event, level, player, startMenuPosition, 
			     startMenuV) == 1) 
	    {
	      return 1;    
	    }
	  while(selectLevel == true)
	    {    
	      if(selectLevelMenu(selectLevel, loadLevelB, startMenu, quit, game, player.gameOver, screen, event, level, 
			 selectLevelPosition, selectLevelV, player) == 1)
		{
		  return 1;	      
		}
	    }
	}
      //Paus menu loop.
      while (player.pausMenu == true) 
	{
	  if( pausMenuF(startMenu, game, quit, player.pausMenu, screen, event, pausMenuPosition, pausMenuV) == 1) 
	    {
	      return 1;	  
	    }
	}
      //Game over screen loop.
      while (player.gameOver == true) 
	{
	  Mix_HaltMusic();
	  if( gameOverMenu(loadLevelB, quit, game, startMenu, player.pausMenu, player.gameOver, screen, event, screenHeight, 
			     screenWidth, gameOverPosition, gameOverV, level, player) == 1) 
	    {
	      return 1; 	  
	    }
	}
      if (loadLevelB == true)
	{
	  loadLevelB = false;
	  loadLevel(Platforms, level, backgroundName, player, Bullets);
	  background = IMG_Load( backgroundName.c_str() );
	  loadSound(level, music, playerShoot, playerJump, playerHurt, playerJumpsEnemy, enemyDies, gameOver);
	}
      //Active game loop.
      if (game == true) 
	{
	  fps.start();
	  //Key pressed, handle the input.
	  while( SDL_PollEvent( &event ) ) 
	    {
	      player.handleInput(event, playerShoot, playerJump);
	      if( event.type == SDL_QUIT ) 
		{
		  quit = true;
		  game = false;
		}
	    }
	  //Start music.
	  if(Mix_PlayingMusic() == 0) 
	    {
	    if( Mix_PlayMusic(music, -1) == -1 )
		{
		  return 1;
		}
	    }
	  //Player shoots. If he has ammo -> spawn bullet.
	  if(player.shoot && player.ammo != 0) 
	    {
	      int speed = player.shooting();
	      if(speed > 0)
		{
		  bullet1 = new Moving_Object(player.x+20, player.y+39, 8, 4, speed, "Images/bulletright.png");
		}
	      if(speed < 0)
		{
		  bullet1 = new Moving_Object(player.x, player.y+39, 8, 4, speed, "Images/bulletleft.png");
		}
	  
	      Bullets.push_back(bullet1);
	      player.shoot = false;
	      player.ammo -= 1;
	    }	  
	  //Handle movement of all bullets.
	  if(Bullets.size() != 0) 
	    {
	      for(int i = 0; i < Bullets.size(); i++)
		{
		  bulletLoop = dynamic_cast<Moving_Object*>(Bullets[i]);
		  bulletLoop->bulletMovement();
		}
	    }
	  
	  //Player dies.
	  if(player.health == 0) 
	    {
	      player.yVel -= 50;
	    }
	  
	  //Handle AI for all enemies and platforms.
	  for(int i = 0; i < Platforms.size(); ++i) 
	    {
	      mp = dynamic_cast<Moving_Platform*>(Platforms[i]);
	      enemy = dynamic_cast<Enemy*>(Platforms[i]);
	      enemySimple = dynamic_cast<Enemy_Simple*>(Platforms[i]);
	      enemyCreeper = dynamic_cast<Enemy_Creeper*>(Platforms[i]);
	      enemyTower = dynamic_cast<Enemy_Tower*>(Platforms[i]);
	      
	      if(mp!=0)
		{
		  mp->elevate();
		}
	      else if(enemySimple != 0)
		{
		  if(enemySimple->y > enemySimple->groundLevel) 
		    {
		      enemySimple->inAir = false;
		    }		  
		  enemySimple->aiSimple();
		  enemySimple->gravity();
		}
	      else if(enemyCreeper != 0)
		{
		  if(player.x > enemyCreeper->x - enemyCreeper->range && player.x < enemyCreeper->x + enemyCreeper->range)
		    {
		      enemyCreeper->aiCreeper(player.x);
		    }
		}
	      else if(enemyTower != 0)
		{
		  enemyTower->aiTower();

		  if((enemyTower->x - enemyTower->range) < player.x && 
		     (enemyTower->x + enemyTower->range) > player.x && 
		     (enemyTower->y - enemyTower->range) < player.y && 
		     (enemyTower->y + enemyTower->range) > player.y)
		    {		  
		      enemyTower->shootCount += 1;
		      if(enemyTower->shootCount > enemyTower->shootDelay)
			{
			  bullet2 = new Moving_Object(enemyTower->x+enemyTower->width/2-5, 
						     enemyTower->y+enemyTower->height/2, 
						     10, 10, 0, "Images/laser.png");
			  towerShoot(enemyTower->x, enemyTower->y, player.x, player.y, 
				      bullet2->xVel, bullet2->yVel);
			  Bullets.push_back(bullet2);
			  enemyTower->shootCount = 0;
			}
		    }
		}
	      if(enemy != 0 && enemySimple == 0)
		{
		  enemy->enemyMove(Platforms);
		}
	    }
	  
	  //Collision for bullets.
	  bulletHit(Platforms, Bullets, player.x, screenWidth, screenHeight); 
	  //Handle gravity, friction and animations for player.
	  player.handlePlayer(screenWidth, screenHeight, bgX, bgY, background); 
	  //Collision player-world.
	  player.move(Platforms, Bullets, playerHurt, playerJumpsEnemy, enemyDies, quit, game, startMenu); 

	  //Player immortality-after-being-hurt-counter check.
	  if(player.noHurt == true)
	    {
	      noHurtCounter += 1;
	      if(noHurtCounter >= 50)
	      {
		player.noHurt = false;
		noHurtCounter = 0;
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
	  handleBackground(bgX, bgY, background, screen, player.cameraY);
	  for(int i = 0; i < Bullets.size(); i++)
	    {
	      Bullets[i]->show(screen, player.cameraX, player.cameraY);
	    }
	  player.show(screen, player.cameraX, player.cameraY);      
	  for (int i = 0; i < Platforms.size(); i++)
	    {
	      Platforms[i]->show(screen, player.cameraX, player.cameraY);
	    }      	  
      	  player.displayHealth(screen);
	  player.displayAmmo(screen);	  
	  if(SDL_Flip(screen) == -1)
	    {
	      return 1;
	    }
	  if( fps.get_ticks() < 1000 / FRAMES_PER_SECOND )
	    {
	      SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
	    }
	  
	  //Check if it is game over.
	  if (player.health == 0)
	    {
	      player.gameOver = true;
	      game = false;
	    }
	}
    }
  
  //Exit program.
  SDL_FreeSurface(background);
  Mix_FreeChunk(playerShoot);
  Mix_FreeChunk(playerJump);
  Mix_FreeChunk(playerHurt);
  Mix_FreeChunk(playerJumpsEnemy);
  Mix_FreeChunk(enemyDies);
  Mix_FreeChunk(gameOver);
  Mix_FreeMusic(music);
  Mix_CloseAudio();

  SDL_Quit();
  return 0;
}

void handleBackground( int x, int y, SDL_Surface* source, SDL_Surface* destination, float cameraY )
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

SDL_Surface *loadImage(std::string filename)
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
  screen = SDL_SetVideoMode( screenWidth, screenHeight, screenBpp, SDL_SWSURFACE );
  if( screen == NULL )
    {
      return false;
    }
  SDL_WM_SetCaption( "City Under Siege", NULL );

  return true;
}

void towerShoot(float startX, float startY, float targetX, float targetY, float& xVel, float& yVel)
{
  float adjacent, opposite, hyp;
  float arctan;
  adjacent = targetX - startX; //Adjacent side.
  opposite = targetY - startY; //Opposite side.
  arctan = atan(adjacent/opposite); //Degrees.
  xVel = sin(arctan);
  yVel = cos(arctan);
  
  if(adjacent > 0 && opposite > 0)
    {
      xVel = sin(arctan)*3;
      yVel = cos(arctan)*3;
    }
  else if(adjacent > 0 && opposite < 0)
    {
      xVel = (-sin(arctan))*3;
      yVel = (-cos(arctan))*3;
    }
  else if(adjacent < 0 && opposite > 0)
    {
      xVel = sin(arctan)*3;
      yVel = cos(arctan)*3;
    }
  else if(adjacent < 0 && opposite < 0)
    {
      xVel = (-sin(arctan))*3;
      yVel = (-cos(arctan))*3;
    }
}

void bulletHit(std::vector<Object*>& Platforms, std::vector<Object*>& Bullets, int playerX, int screenWidth, int screenHeight)
{
  //Check all bullets.
  for(int b = 0; b < Bullets.size(); b++)
    {
      Moving_Object* bullet = dynamic_cast<Moving_Object*>(Bullets[b]);
      //Check collision with all objects except bullets.
      for(int p = 0; p < Platforms.size(); p++) 
	{
	  Enemy* enemy;
	  Enemy_Tower* enemyTower;
	  
	  if(bullet->collision(Platforms[p]))
	    {
	      enemy = dynamic_cast<Enemy*>(Platforms[p]);
	      enemyTower = dynamic_cast<Enemy_Tower*>(Platforms[p]);
	      
	      if(bullet->collision(Platforms[p]) && enemyTower == 0)
		{
		  //Remove bullet.
		  if( Bullets.at(b) != NULL ) 
		    {
		      delete Bullets.at(b);
		      Bullets.at(b) = NULL;
		      Bullets.erase(Bullets.begin()+b);
		    }
		  //Enemy hit but not dead.
		  if(enemy != 0 && enemy->health != 0) 
		    {
		      enemy->health -= 1;
		    }
		  //Killed enemy.
		  else if(enemy != 0 && enemy->health == 0) 
		    {
		      //Remove enemy so that it is not blitted on screen.
		      if( Platforms.at(p) != NULL ) 
			{
			  delete Platforms.at(p);
			  Platforms.at(p) = NULL;
			  Platforms.erase(Platforms.begin()+p);
			}
		    }
		}
	      //If shot outside screen +/- 774, remove it.
	      else if(bullet->x > (playerX + 774) || bullet->x < (playerX - 774))
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
