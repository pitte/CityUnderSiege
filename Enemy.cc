#include "Enemy.h"


void Enemy::EnemyMove(std::vector<Object*> Platforms)
{
  for(int i = 0; i < Platforms.size(); i++) {
      Object* checkpic = dynamic_cast<Object*>(Platforms[i]);
      if(checkpic->Picture != "bild/enemysimple.jpg") {
	  if(Collision(Platforms[i])) {
	      if(x < Platforms[i]->x)
		x = Platforms[i]->x - Width;
	      if(x > Platforms[i]->x)
		x = Platforms[i]->x + Platforms[i]->Width;
	    }
	}
    }
}
