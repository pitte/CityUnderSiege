

int Start_Game_Menu(bool &quit, bool &Game, bool &Start_Menu, bool &Load_Level, bool &Select_Level, SDL_Surface* &screen, SDL_Event &event, std::string &level, Player &player, int &Start_Menu_Position, std::vector<Object*> &Start_Menu_V)
{
  
  SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) );
	  

  if(Start_Menu_Position == 0) //new game markerad
    {
      Start_Menu_V[1]->Show(screen, 0, 0);
      Start_Menu_V[2]->Show(screen, 0, 0);
      Start_Menu_V[4]->Show(screen, 0, 0);
    }

  else if(Start_Menu_Position == 1) //select level
    {
      Start_Menu_V[0]->Show(screen, 0, 0);
      Start_Menu_V[3]->Show(screen, 0, 0);
      Start_Menu_V[4]->Show(screen, 0, 0);
    }

  else if(Start_Menu_Position == 2) // exit game
    {
      Start_Menu_V[0]->Show(screen, 0, 0);
      Start_Menu_V[2]->Show(screen, 0, 0);
      Start_Menu_V[5]->Show(screen, 0, 0);
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
	      --Start_Menu_Position;
	      if (Start_Menu_Position < 0)
		{
		  Start_Menu_Position = 2;
		}
	      break;


	    case SDLK_DOWN:  
	      ++Start_Menu_Position;
	      if (Start_Menu_Position == 3)
		{
		  Start_Menu_Position = 0;
		}
	      break;

	    case SDLK_RETURN: 
	      if (Start_Menu_Position == 0) 
		{
		  //New Game
		  level = "City_Level.txt";
		  player.x = 300; //19000
		  player.y = 400; //0
		  player.Health = 5;
		  player.Ammo = 0;
		  player.xVel = 0;
		  player.yVel = 0;
		  player.NoHurt = false;
		  player.RightKey = false;
		  player.LeftKey = false;
		  Load_Level = true;
		  Game = true;
		  Start_Menu = false;
		}

	      else if (Start_Menu_Position == 1)
		{
		  // Select level
		  Select_Level = true;
		}

	      else if (Start_Menu_Position == 2)
		{
		  //Exit Game
		  quit = true;
		  Game = false;
		  Start_Menu = false;
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
	  Game = false;
	  Start_Menu = false;
	}
    }
}









int Paus_Menu_F(bool &Start_Menu, bool &Game, bool &quit, bool &Paus_Menu, SDL_Surface* &screen, SDL_Event &event, int &Paus_Menu_Position, std::vector<Object*> &Paus_Menu_V)
{

  if (Paus_Menu_Position == 0)
    {
      //resume game
      Paus_Menu_V[1]->Show(screen, 0, 0);
      Paus_Menu_V[2]->Show(screen, 0, 0);
    }

  else if (Paus_Menu_Position == 1)
    {
      //exit game
      Paus_Menu_V[0]->Show(screen, 0, 0);
      Paus_Menu_V[3]->Show(screen, 0, 0);
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
	      --Paus_Menu_Position;
	      if (Paus_Menu_Position < 0)
		{
		  Paus_Menu_Position = 1;
		}
	      break;


	    case SDLK_DOWN:  
	      ++Paus_Menu_Position;
	      if (Paus_Menu_Position == 2)
		{
		  Paus_Menu_Position = 0;
		}
	      break;

	    case SDLK_RETURN: 
	      if (Paus_Menu_Position == 0) 
		{
		  //Resume Game
		  Paus_Menu = false;
		}
	      else if (Paus_Menu_Position == 1)
		{
		  //Exit Game
		  quit = false;
		  Game = false;
		  Paus_Menu = false;
		  Start_Menu = true;
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
	      Paus_Menu = false;
	      break;

	    default: break;
	    }
	}
      if( event.type == SDL_QUIT )
	{
	  Paus_Menu = false;
	  quit = true;
	  Game = false;
	  Start_Menu = false;
	}
    }
}


int Game_Over_Menu(bool &Load_Level, bool &quit, bool &Game, bool &Start_Menu, bool &Paus_Menu, bool &Game_Over, SDL_Surface* &screen, SDL_Event &event, int screen_height, int screen_width, int &Game_Over_Position, std::vector<Object*> &Game_Over_V, std::string &level, Player& player)
{


  if (Game_Over_Position == 0)
    {
      //Restart Level
      Game_Over_V[4]->Show(screen, 0, 0);
      Game_Over_V[1]->Show(screen, 0, 0);
      Game_Over_V[2]->Show(screen, 0, 0);
    }

  else if (Game_Over_Position == 1)
    {
      //Main Menu
      Game_Over_V[4]->Show(screen, 0, 0);
      Game_Over_V[0]->Show(screen, 0, 0);
      Game_Over_V[3]->Show(screen, 0, 0);
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
	      --Game_Over_Position;
	      if (Game_Over_Position < 0)
		{
		  Game_Over_Position = 1;
		}
	      break;

	    case SDLK_DOWN:  
	      ++Game_Over_Position;
	      if (Game_Over_Position > 1)
		{
		  Game_Over_Position = 0;
		}
	      break;

	    case SDLK_RETURN: 
	      if (Game_Over_Position == 0) 
		{
		  //restart
		  Game_Over = false;
		  Game = true;
		  Load_Level = true;
		  player.Health = 5;
		  player.Ammo = 0;
		  player.NoHurt = false;
		  player.xVel = 0;
		  player.yVel = 0;
		  player.RightKey = false;
		  player.LeftKey = false;
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
	      else if (Game_Over_Position == 1)
		{
		  //main menu
		  Game_Over = false;
		  Game = false;
		  Start_Menu = true;
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
	  Paus_Menu = false;
	  quit = true;
	  Game = false;
	  Start_Menu = false;
	  Game_Over = false;
	}
    }
}




int Select_Level_Menu(bool &Select_Level, bool &Load_Level, bool &Start_Menu, bool &quit, bool &Game, bool &Game_Over, SDL_Surface* &screen, SDL_Event &event, std::string &level, int &Select_Level_Position, std::vector<Object*> Select_Level_V, Player &player)
{

  

  SDL_FillRect( screen, &screen->clip_rect, 
		SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) );


  if (Select_Level_Position == 0)
    {
      //Level 1
    
      Select_Level_V[1]->Show(screen, 0, 0);
      Select_Level_V[2]->Show(screen, 0, 0);
      Select_Level_V[4]->Show(screen, 0, 0);
    }

  else if (Select_Level_Position == 1)
    {
      //Level 2
     
      Select_Level_V[0]->Show(screen, 0, 0);
      Select_Level_V[3]->Show(screen, 0, 0);
      Select_Level_V[4]->Show(screen, 0, 0);
    }
  else if (Select_Level_Position == 2)
    {
      //Back
   
      Select_Level_V[0]->Show(screen, 0, 0);
      Select_Level_V[2]->Show(screen, 0, 0);
      Select_Level_V[5]->Show(screen, 0, 0);
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
	      --Select_Level_Position;
	      if (Select_Level_Position < 0)
		{
		  Select_Level_Position = 2;
		}
	      break;

	    case SDLK_DOWN:  
	      ++Select_Level_Position;
	      if (Select_Level_Position == 3)
		{
		  Select_Level_Position = 0;
		}
	      break;

	    case SDLK_RETURN: 
	      if (Select_Level_Position == 0) 
		{
		  //level 1
		  Select_Level = false;
		  Start_Menu = false;
		  Load_Level = true;
		  Game = true;
		  player.x = 300;
		  player.y = 400;
		  player.xVel = 0;
		  player.yVel = 0;
		  player.Health = 5;
		  player.Ammo = 0;
		  player.NoHurt = false;
		  player.RightKey = false;
		  player.LeftKey = false;
		  level = "City_Level.txt";
		}
	      else if (Select_Level_Position == 1)
		{
		  //level 2
		  player.xVel = 0;
		  player.yVel = 0;
		  player.x = 400;
		  player.y = 400;
		  player.Health = 5;
		  player.Ammo = 0;
		  Select_Level = false;
		  Start_Menu = false;
		  Load_Level = true;
		  Game = true;
		  player.NoHurt = false;
		  player.RightKey = false;
		  player.LeftKey = false;
		  level = "Forest_Level.txt";
		}
	      else if (Select_Level_Position == 2)
		{
		  //Main Menu
		  Select_Level = false;
		  Start_Menu = true;
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
	  Select_Level = false;
	  quit = true;
	  Game = false;
	  Start_Menu = false;
	  Game_Over = false;
	}
    }
}
