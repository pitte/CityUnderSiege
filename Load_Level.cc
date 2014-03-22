void load_level(std::vector<Object*>& Platforms, std::string& level, std::string& BackgroundName, Player& player)
{
  float bl1, bl2, bl3, bl4, bl5, bl6, bl7, bl8, bl9, bl10, bl11;

  std::string x;
  std::ifstream bandesign;
  std::vector<std::string> blocken;
  player.xVel = 0;
  player.yVel = 0;
  Platforms.clear();
  
  bandesign.open(level.c_str());

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
	      std::istringstream b5(blocken[6]);//movespeed
	      std::istringstream b6(blocken[7]);//health
	      std::istringstream b7(blocken[8]);//to
	      std::istringstream b8(blocken[9]);//frames
	      std::istringstream b9(blocken[10]);//anim
	      std::istringstream b10(blocken[11]);//ground
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
	      std::istringstream b5(blocken[6]);//movespeed
	      std::istringstream b6(blocken[7]);//health
	      std::istringstream b7(blocken[8]);//radius
	      std::istringstream b8(blocken[9]);//frames
	      std::istringstream b9(blocken[10]);//anim
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
	      std::istringstream b5(blocken[6]);//movespeed
	      std::istringstream b6(blocken[7]);//to i y
	      std::istringstream b7(blocken[8]);//health
	      std::istringstream b8(blocken[9]);//radius
	      std::istringstream b9(blocken[10]);//delay
	      std::istringstream b10(blocken[11]);//frames
	      std::istringstream b11(blocken[12]);//anim
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
	      std::istringstream b5(blocken[6]);//movespeed
	      std::istringstream b6(blocken[7]);//health
	      std::istringstream b7(blocken[8]);//range
	      std::istringstream b8(blocken[9]);//frames
	      std::istringstream b9(blocken[10]);//anim
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
