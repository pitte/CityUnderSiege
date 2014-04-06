#ifndef PLAYER_H
#define PLAYER_H
#include "Moving_Object.h"
#include <string>
#include <vector>

class Player : public Moving_Object
{
 public:
 Player(float x_, float y_, float width_, float height_, float moveSpeed_, std::string picture_, int frames_ = 0, int animations_ = 0, float health_ = '3')
   : Moving_Object(x_, y_, width_, height_, moveSpeed_, picture_, frames_, animations_, health_)
    {
      leftKey = false; rightKey = false;
      shoot = false;
      use = false;
      ammo = 20;
      startX = x_; startY = y_;
      cameraX = 0; cameraY = 0;
      pausMenu = false; gameOver = false;
      prevRight = true; prevLeft = false;
      heartPic = IMG_Load("Images/Heart.png");
      bulletPic = IMG_Load("Images/cartridge.png");
      noHurt = false;
    }
 
  void friction();
  void setCamera(int screenWidth, int screenHeight, int& bgX, int& bgY, SDL_Surface*& background);     
  void handleInput(SDL_Event event, Mix_Chunk* playerShoot, Mix_Chunk* playerJump);
  void handlePlayer(int screenWidth, int screenHeight, int& bgX, int& bgY, SDL_Surface*& background );
  void move(std::vector<Object*>& Platforms, std::vector<Object*>& Bullets, Mix_Chunk* playerHurt, Mix_Chunk* playerJump, Mix_Chunk* enemyDies, bool& quit, bool& game, bool& startMenu);
  int shooting();
  void displayHealth(SDL_Surface* screen);
  void displayAmmo(SDL_Surface* screen);
  
  bool prevRight, prevLeft;
  bool pausMenu;
  bool gameOver;
  bool noHurt;
  float startX;
  float startY;
  bool use;
  bool shoot;
  bool launched;
  int ammo;
  float cameraX, cameraY;
  bool rightKey, leftKey;
  SDL_Surface* heartPic;
  SDL_Surface* bulletPic;
};

#endif
