void Load_Sound(std::string level, Mix_Music*& music, Mix_Chunk*& Player_Shoot, 
		Mix_Chunk*& Player_Jump, Mix_Chunk*& Player_Hurt, 
		Mix_Chunk*& Player_Jumps_Enemy, Mix_Chunk*& Enemy_Dies, 
		Mix_Chunk*& Game_Over)
{
  if(level == "City_Level.txt")
    music = Mix_LoadMUS("ljud/Music_City_Level.mp3");
  
  if(level == "Forest_Level.txt")
    music = Mix_LoadMUS("ljud/Music_Forest_Level.mp3");
  
  Player_Shoot = Mix_LoadWAV("ljud/Player_Shoot.wav");
  Player_Jump = Mix_LoadWAV("ljud/Player_Jump.wav");
  Player_Hurt = Mix_LoadWAV("ljud/Player_Hurt.wav");
  Player_Jumps_Enemy = Mix_LoadWAV("ljud/Player_Jumps_Enemy.wav");
  Enemy_Dies = Mix_LoadWAV("ljud/Enemy_Dies.wav");
  Game_Over = Mix_LoadWAV("ljud/Game_Over.wav");
}
