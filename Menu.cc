int startGameMenu(bool &quit, bool &game, bool &startMenu, bool &loadLevel, bool &selectLevel, SDL_Surface* &screen, SDL_Event &event, std::string &level, Player &player, int &startMenuPosition, std::vector<Object*> &startMenuV)
{
  SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) );
  
  if(startMenuPosition == 0) //New game.
    {
      startMenuV[1]->show(screen, 0, 0);
      startMenuV[2]->show(screen, 0, 0);
      startMenuV[4]->show(screen, 0, 0);
    }
  else if(startMenuPosition == 1) //Select level.
    {
      startMenuV[0]->show(screen, 0, 0);
      startMenuV[3]->show(screen, 0, 0);
      startMenuV[4]->show(screen, 0, 0);
    }
  else if(startMenuPosition == 2) //Exit game.
    {
      startMenuV[0]->show(screen, 0, 0);
      startMenuV[2]->show(screen, 0, 0);
      startMenuV[5]->show(screen, 0, 0);
    }
	  	  	  
  if(SDL_Flip(screen) == -1)
    {
      return 1;
    }
	  
  while( SDL_PollEvent( &event ) )
    {	  
      if(event.type == SDL_KEYDOWN)
	{
	  switch(event.key.keysym.sym)
	    {
	    case SDLK_UP:
	      --startMenuPosition;
	      if (startMenuPosition < 0)
		{
		  startMenuPosition = 2;
		}
	      break;
	    case SDLK_DOWN:  
	      ++startMenuPosition;
	      if (startMenuPosition == 3)
		{
		  startMenuPosition = 0;
		}
	      break;
	    case SDLK_RETURN: 
	      if (startMenuPosition == 0) 
		{
		  //New Game.
		  level = "City_Level.txt";
		  player.x = 300; //19000
		  player.y = 400; //0
		  player.health = 5;
		  player.ammo = 0;
		  player.xVel = 0;
		  player.yVel = 0;
		  player.noHurt = false;
		  player.rightKey = false;
		  player.leftKey = false;
		  loadLevel = true;
		  game = true;
		  startMenu = false;
		}
	      else if (startMenuPosition == 1)
		{
		  // Select level.
		  selectLevel = true;
		}
	      else if (startMenuPosition == 2)
		{
		  //Exit Game.
		  quit = true;
		  game = false;
		  startMenu = false;
		}
	      break; 
	    default: break;
	    }
	}
      else if(event.type == SDL_KEYUP)
	{
	  switch(event.key.keysym.sym)
	    {
	    default: break;
	    }
	}

      if( event.type == SDL_QUIT )
	{
	  quit = true;
	  game = false;
	  startMenu = false;
	}
    }
}

int pausMenuF(bool &startMenu, bool &game, bool &quit, bool &pausMenu, SDL_Surface* &screen, SDL_Event &event, int &pausMenuPosition, std::vector<Object*> &pausMenuV)
{
  if (pausMenuPosition == 0)
    {
      //Resume game.
      pausMenuV[1]->show(screen, 0, 0);
      pausMenuV[2]->show(screen, 0, 0);
    }
  else if (pausMenuPosition == 1)
    {
      //Exit game.
      pausMenuV[0]->show(screen, 0, 0);
      pausMenuV[3]->show(screen, 0, 0);
    }

  if(SDL_Flip(screen) == -1)
    {
      return 1;
    }

  while( SDL_PollEvent( &event ) )
    {	  
      if(event.type == SDL_KEYDOWN)
	{
	  switch(event.key.keysym.sym)
	    {
	    case SDLK_UP:
	      --pausMenuPosition;
	      if (pausMenuPosition < 0)
		{
		  pausMenuPosition = 1;
		}
	      break;
	    case SDLK_DOWN:  
	      ++pausMenuPosition;
	      if (pausMenuPosition == 2)
		{
		  pausMenuPosition = 0;
		}
	      break;
	    case SDLK_RETURN: 
	      if (pausMenuPosition == 0) 
		{
		  //Resume Game.
		  pausMenu = false;
		}
	      else if (pausMenuPosition == 1)
		{
		  //Exit Game.
		  quit = false;
		  game = false;
		  pausMenu = false;
		  startMenu = true;
		}
	      break;
	    default: break;
	    }
	}
      else if(event.type == SDL_KEYUP)
	{
	  switch(event.key.keysym.sym)
	    {
	    case SDLK_ESCAPE:
	      pausMenu = false;
	      break;

	    default: break;
	    }
	}
      if( event.type == SDL_QUIT )
	{
	  pausMenu = false;
	  quit = true;
	  game = false;
	  startMenu = false;
	}
    }
}

int gameOverMenu(bool &loadLevel, bool &quit, bool &game, bool &startMenu, bool &pausMenu, bool &gameOver, SDL_Surface* &screen, SDL_Event &event, int screenHeight, int screenWidth, int &gameOverPosition, std::vector<Object*> &gameOverV, std::string &level, Player& player)
{
  if (gameOverPosition == 0)
    {
      //Restart level.
      gameOverV[4]->show(screen, 0, 0);
      gameOverV[1]->show(screen, 0, 0);
      gameOverV[2]->show(screen, 0, 0);
    }
  else if (gameOverPosition == 1)
    {
      //Main Menu.
      gameOverV[4]->show(screen, 0, 0);
      gameOverV[0]->show(screen, 0, 0);
      gameOverV[3]->show(screen, 0, 0);
    }
  if(SDL_Flip(screen) == -1)
    {
      return 1;
    }

  while( SDL_PollEvent( &event ) )
    {	  
      if(event.type == SDL_KEYDOWN)
	{
	  switch(event.key.keysym.sym)
	    {
	    case SDLK_UP:
	      --gameOverPosition;
	      if (gameOverPosition < 0)
		{
		  gameOverPosition = 1;
		}
	      break;
	    case SDLK_DOWN:  
	      ++gameOverPosition;
	      if (gameOverPosition > 1)
		{
		  gameOverPosition = 0;
		}
	      break;
	    case SDLK_RETURN: 
	      if (gameOverPosition == 0) 
		{
		  //Restart.
		  gameOver = false;
		  game = true;
		  loadLevel = true;
		  player.health = 5;
		  player.ammo = 0;
		  player.noHurt = false;
		  player.xVel = 0;
		  player.yVel = 0;
		  player.rightKey = false;
		  player.leftKey = false;
		  if (level == "City_Level.txt")
		    {
		      player.x = 300;
		      player.y = 400;
		    }
		  else if (level == "Forest_Level.txt")
		    {
		      player.x = 400;
		      player.y = 400;
		    }
		}
	      else if (gameOverPosition == 1)
		{
		  //Main menu.
		  gameOver = false;
		  game = false;
		  startMenu = true;
		}
	      break;
	    default: break;
	    }
	}
      else if(event.type == SDL_KEYUP)
	{
	  switch(event.key.keysym.sym)
	    {
	    default: break;
	    }
	}
      if( event.type == SDL_QUIT )
	{
	  pausMenu = false;
	  quit = true;
	  game = false;
	  startMenu = false;
	  gameOver = false;
	}
    }
}

int selectLevelMenu(bool &selectLevel, bool &loadLevel, bool &startMenu, bool &quit, bool &game, bool &gameOver, SDL_Surface* &screen, SDL_Event &event, std::string &level, int &selectLevelPosition, std::vector<Object*> selectLevelV, Player &player)
{
  SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) );
  
  if (selectLevelPosition == 0)
    {
      //Level 1.
      selectLevelV[1]->show(screen, 0, 0);
      selectLevelV[2]->show(screen, 0, 0);
      selectLevelV[4]->show(screen, 0, 0);
    }  
  else if (selectLevelPosition == 1)
    {
      //Level 2.
      selectLevelV[0]->show(screen, 0, 0);
      selectLevelV[3]->show(screen, 0, 0);
      selectLevelV[4]->show(screen, 0, 0);
    }
  else if (selectLevelPosition == 2)
    {
      //Back.
      selectLevelV[0]->show(screen, 0, 0);
      selectLevelV[2]->show(screen, 0, 0);
      selectLevelV[5]->show(screen, 0, 0);
    }

  if(SDL_Flip(screen) == -1)
    {
      return 1;
    }

  while( SDL_PollEvent( &event ) )
    {	  
      if(event.type == SDL_KEYDOWN)
	{
	  switch(event.key.keysym.sym)
	    {
	    case SDLK_UP:
	      --selectLevelPosition;
	      if (selectLevelPosition < 0)
		{
		  selectLevelPosition = 2;
		}
	      break;
	    case SDLK_DOWN:  
	      ++selectLevelPosition;
	      if (selectLevelPosition == 3)
		{
		  selectLevelPosition = 0;
		}
	      break;
	    case SDLK_RETURN: 
	      if (selectLevelPosition == 0) 
		{
		  //Level 1.
		  selectLevel = false;
		  startMenu = false;
		  loadLevel = true;
		  game = true;
		  player.x = 300;
		  player.y = 400;
		  player.xVel = 0;
		  player.yVel = 0;
		  player.health = 5;
		  player.ammo = 0;
		  player.noHurt = false;
		  player.rightKey = false;
		  player.leftKey = false;
		  level = "City_Level.txt";
		}
	      else if (selectLevelPosition == 1)
		{
		  //Level 2.
		  player.xVel = 0;
		  player.yVel = 0;
		  player.x = 400;
		  player.y = 400;
		  player.health = 5;
		  player.ammo = 0;
		  selectLevel = false;
		  startMenu = false;
		  loadLevel = true;
		  game = true;
		  player.noHurt = false;
		  player.rightKey = false;
		  player.leftKey = false;
		  level = "Forest_Level.txt";
		}
	      else if (selectLevelPosition == 2)
		{
		  //Main Menu.
		  selectLevel = false;
		  startMenu = true;
		}
	      break;		 
	    default: break;
	    }
	}
      else if(event.type == SDL_KEYUP)
	{
	  switch(event.key.keysym.sym)
	    {
	    default: break;
	    }
	}
      if( event.type == SDL_QUIT )
	{
	  selectLevel = false;
	  quit = true;
	  game = false;
	  startMenu = false;
	  gameOver = false;
	}
    }
}
