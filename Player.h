#ifndef PLAYER_H
#define PLAYER_H
#include "MovingObject.h"
#include <string>
#include <vector>


class Player : public MovingObject
{
 public:
 Player(float x_, float y_, float Width_, float Height_, float MoveSpeed_, std::string Picture_, int Frames_ = 0, int Animations_ = 0, float Health_ = '3')
   : MovingObject(x_, y_, Width_, Height_, MoveSpeed_, Picture_, Frames_, Animations_, Health_)
    {
      LeftKey = false; RightKey = false;
      Shoot = false;
      Use = false;
      Ammo = 20;
      StartX = x_; StartY = y_;
      CameraX = 0; CameraY = 0;
      Paus_Menu = false; Game_Over = false;
      PrevRight = true; PrevLeft = false;
      HeartPic = IMG_Load("bild/Heart.png");
      BulletPic = IMG_Load("bild/cartridge.png");
      NoHurt = false;
    }
 
  void Friction();
  void SetCamera(int screen_width, int screen_height, int& bgX, int& bgY, SDL_Surface*& background);     
  void Handle_Input(SDL_Event event, Mix_Chunk* Player_Shoot, Mix_Chunk* Player_Jump);
  void Handle_Player(int screen_width, int screen_height, int& bgX, int& bgY, SDL_Surface*& background );
  void Move(std::vector<Object*>& Platforms, std::vector<Object*>& Bullets, Mix_Chunk* Player_Hurt, Mix_Chunk* Player_Jump, Mix_Chunk* Enemy_Dies, bool& quit, bool& Game, bool& Start_Menu);
  int Shooting();
  void DisplayHealth(SDL_Surface* screen);
  void DisplayAmmo(SDL_Surface* screen);
  
  bool PrevRight, PrevLeft;
  bool Paus_Menu;
  bool Game_Over;
  bool NoHurt;
  float StartX;
  float StartY;
  bool Use;
  bool Shoot;
  bool Launched;
  int Ammo;
  float CameraX, CameraY;
  bool RightKey, LeftKey;
  SDL_Surface* HeartPic;
  SDL_Surface* BulletPic;
};

#endif
