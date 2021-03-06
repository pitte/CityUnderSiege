/*
  Reads a level from file, complete with enemy placement.
*/

void loadLevel(std::vector<Object*>& Platforms, std::string& level, std::string& backgroundName, Player& player, std::vector<Object*>& Bullets)
{
  float bl1, bl2, bl3, bl4, bl5, bl6, bl7, bl8, bl9, bl10, bl11;
  std::string x;
  std::ifstream levelDesign;
  std::vector<std::string> blocks;
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

  levelDesign.open( level.c_str() );

  while(levelDesign>>x)
    {
      if(x != ";")
	{
	  blocks.push_back(x);
	}
      else if(x == ";")
	{
	  std::istringstream b1(blocks[0]);
	  std::istringstream b2(blocks[1]);
	  std::istringstream b3(blocks[2]);
	  std::istringstream b4(blocks[3]);

	  b1>>bl1;
	  b2>>bl2;
	  b3>>bl3;
	  b4>>bl4;

	  if(blocks[5] == "object")
	    {
	      std::istringstream b5(blocks[6]);
	      std::istringstream b6(blocks[7]);
	      b5>>bl5;
	      b6>>bl6;
	      Platforms.push_back(new Object(bl1, bl2, bl3, bl4, blocks[4], bl5, bl6));
	      blocks.clear();
	    }
	  else if(blocks[5] == "moving")
	    {
	      std::istringstream b5(blocks[6]);
	      std::istringstream b6(blocks[7]);
	      b5>>bl5;
	      b6>>bl6;
	      Platforms.push_back(new Moving_Platform(bl1, bl2, bl3, bl4, bl5, blocks[4], bl6));
	      blocks.clear();
	    }
	  else if(blocks[5] == "background")
	    {
	      backgroundName = blocks[4];
	      blocks.clear();
	    }
	  else if(blocks[5] == "simple")
	    {
	      std::istringstream b5(blocks[6]); //Movespeed.
	      std::istringstream b6(blocks[7]); //Health.
	      std::istringstream b7(blocks[8]); //To.
	      std::istringstream b8(blocks[9]); //Frames.
	      std::istringstream b9(blocks[10]); //Anim.
	      std::istringstream b10(blocks[11]); //Ground.
	      b5>>bl5;
	      b6>>bl6;
	      b7>>bl7;
	      b8>>bl8;
	      b9>>bl9;
	      b10>>bl10;
	      Platforms.push_back(new Enemy_Simple(bl1, bl2, bl3, bl4, bl5, blocks[4], bl6, bl7, bl8, bl9, bl10));
	      blocks.clear();
	    }
	  else if(blocks[5] == "creeper")
	    {
	      std::istringstream b5(blocks[6]); //Movespeed.
	      std::istringstream b6(blocks[7]); //Health.
	      std::istringstream b7(blocks[8]); //Radius.
	      std::istringstream b8(blocks[9]); //Frames.
	      std::istringstream b9(blocks[10]); //Anim.
	      b5>>bl5;
	      b6>>bl6;
	      b7>>bl7;
	      b8>>bl8;
	      b9>>bl9;
	      Platforms.push_back(new Enemy_Creeper(bl1, bl2, bl3, bl4, bl5, blocks[4], bl6, bl7, bl8, bl9));
	      blocks.clear();
	    }
	  else if(blocks[5] == "tower")
	    {
	      std::istringstream b5(blocks[6]); //Movespeed.
	      std::istringstream b6(blocks[7]); //To i y.
	      std::istringstream b7(blocks[8]); //Health.
	      std::istringstream b8(blocks[9]); //Radius.
	      std::istringstream b9(blocks[10]); //Delay.
	      std::istringstream b10(blocks[11]); //Frames.
	      std::istringstream b11(blocks[12]); //Anim.
	      b5>>bl5;
	      b6>>bl6;
	      b7>>bl7;
	      b8>>bl8;
	      b9>>bl9;
	      b10>>bl10;
	      b11>>bl11;
	      Platforms.push_back(new Enemy_Tower(bl1, bl2, bl3, bl4, bl5, blocks[4], bl6, bl7, bl8, bl9, bl10, bl11));
	      blocks.clear();
	    }
	}
    }
}
