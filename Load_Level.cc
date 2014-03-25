/*
  Reads a level from file, complete with enemy placement.
*/

void load_level(std::vector<Object*>& Platforms, std::string& level, std::string& BackgroundName, Player& player, std::vector<Object*>& Bullets)
{
  float bl1, bl2, bl3, bl4, bl5, bl6, bl7, bl8, bl9, bl10, bl11;
  std::string x;
  std::ifstream bandesign;
  std::vector<std::string> blocken;
  player.xVel = 0;
  player.yVel = 0;

  //Delete the objects since they were created with 'new'.
  if( !Bullets.empty() ) 
    {
      for (unsigned int i = 0; i<Bullets.size(); ++i)
	{
	  if( Bullets.at(i) != NULL ) 
	    {
	      delete Bullets.at(i);
	      Bullets.at(i) = NULL;
	    }
	}
    }
  Bullets.clear(); //Remove the pointers.
  
  //Delete the objects since they were created with 'new'.
  if( !Platforms.empty() ) 
    {
      for (unsigned int i = 0; i<Platforms.size(); ++i)
	{
	  if( Platforms.at(i) != NULL ) 
	    {
	      delete Platforms.at(i);
	      Platforms.at(i) = NULL;
	    }
	}
    }
  Platforms.clear(); //Remove the pointers.

  bandesign.open( level.c_str() );

  while(bandesign>>x)
    {
      if(x != ";")
	{
	  blocken.push_back(x);
	}
      else if(x == ";")
	{
	  std::istringstream b1(blocken[0]);
	  std::istringstream b2(blocken[1]);
	  std::istringstream b3(blocken[2]);
	  std::istringstream b4(blocken[3]);

	  b1>>bl1;
	  b2>>bl2;
	  b3>>bl3;
	  b4>>bl4;

	  if(blocken[5] == "object")
	    {
	      std::istringstream b5(blocken[6]);
	      std::istringstream b6(blocken[7]);
	      b5>>bl5;
	      b6>>bl6;
	      Platforms.push_back(new Object(bl1, bl2, bl3, bl4, blocken[4], bl5, bl6));
	      blocken.clear();
	    }
	  else if(blocken[5] == "moving")
	    {
	      std::istringstream b5(blocken[6]);
	      std::istringstream b6(blocken[7]);
	      b5>>bl5;
	      b6>>bl6;
	      Platforms.push_back(new MovingPlatform(bl1, bl2, bl3, bl4, bl5, blocken[4], bl6));
	      blocken.clear();
	    }
	  else if(blocken[5] == "background")
	    {
	      BackgroundName = blocken[4];
	      blocken.clear();
	    }
	  else if(blocken[5] == "simple")
	    {
	      std::istringstream b5(blocken[6]); //Movespeed.
	      std::istringstream b6(blocken[7]); //Health.
	      std::istringstream b7(blocken[8]); //To.
	      std::istringstream b8(blocken[9]); //Frames.
	      std::istringstream b9(blocken[10]); //Anim.
	      std::istringstream b10(blocken[11]); //Ground.
	      b5>>bl5;
	      b6>>bl6;
	      b7>>bl7;
	      b8>>bl8;
	      b9>>bl9;
	      b10>>bl10;
	      Platforms.push_back(new Enemy_Simple(bl1, bl2, bl3, bl4, bl5, blocken[4], bl6, bl7, bl8, bl9, bl10));
	      blocken.clear();
	    }
	  else if(blocken[5] == "creeper")
	    {
	      std::istringstream b5(blocken[6]); //Movespeed.
	      std::istringstream b6(blocken[7]); //Health.
	      std::istringstream b7(blocken[8]); //Radius.
	      std::istringstream b8(blocken[9]); //Frames.
	      std::istringstream b9(blocken[10]); //Anim.
	      b5>>bl5;
	      b6>>bl6;
	      b7>>bl7;
	      b8>>bl8;
	      b9>>bl9;
	      Platforms.push_back(new Enemy_Creeper(bl1, bl2, bl3, bl4, bl5, blocken[4], bl6, bl7, bl8, bl9));
	      blocken.clear();
	    }
	  else if(blocken[5] == "tower")
	    {
	      std::istringstream b5(blocken[6]); //Movespeed.
	      std::istringstream b6(blocken[7]); //To i y.
	      std::istringstream b7(blocken[8]); //Health.
	      std::istringstream b8(blocken[9]); //Radius.
	      std::istringstream b9(blocken[10]); //Delay.
	      std::istringstream b10(blocken[11]); //Frames.
	      std::istringstream b11(blocken[12]); //Anim.
	      b5>>bl5;
	      b6>>bl6;
	      b7>>bl7;
	      b8>>bl8;
	      b9>>bl9;
	      b10>>bl10;
	      b11>>bl11;
	      Platforms.push_back(new Enemy_Tower(bl1, bl2, bl3, bl4, bl5, blocken[4], bl6, bl7, bl8, bl9, bl10, bl11));
	      blocken.clear();
	    }
	  else if(blocken[5] == "tank")
	    {
	      std::istringstream b5(blocken[6]); //Movespeed.
	      std::istringstream b6(blocken[7]); //Health.
	      std::istringstream b7(blocken[8]); //Range.
	      std::istringstream b8(blocken[9]); //Frames.
	      std::istringstream b9(blocken[10]); //Anim.
	      b5>>bl5;
	      b6>>bl6;
	      b7>>bl7;
	      b8>>bl8;
	      b9>>bl9;
	      Platforms.push_back(new Enemy_Tank(bl1, bl2, bl3, bl4, bl5, blocken[4], bl6, bl7, bl8, bl9));
	      blocken.clear();
	    }
	}
    }
}
