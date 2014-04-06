#include "Enemy.h"

void Enemy::enemyMove(std::vector<Object*> Platforms)
{
  for(int i = 0; i < Platforms.size(); i++) {
      Object* checkPic = dynamic_cast<Object*>(Platforms[i]);
      if(checkPic->picture != "Images/enemysimple.jpg") {
	  if(collision(Platforms[i])) {
	      if(x < Platforms[i]->x)
		x = Platforms[i]->x - width;
	      if(x > Platforms[i]->x)
		x = Platforms[i]->x + Platforms[i]->width;
	    }
	}
    }
}
