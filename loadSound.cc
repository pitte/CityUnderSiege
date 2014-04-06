void loadSound(std::string level, Mix_Music*& music, Mix_Chunk*& playerShoot, 
		Mix_Chunk*& playerJump, Mix_Chunk*& playerHurt, 
		Mix_Chunk*& playerJumpsEnemy, Mix_Chunk*& enemyDies, 
		Mix_Chunk*& gameOver)
{
  if(level == "City_Level.txt")
    music = Mix_LoadMUS("Sound/Music_City_Level.mp3");
  
  if(level == "Forest_Level.txt")
    music = Mix_LoadMUS("Sound/Music_Forest_Level.mp3");
  
  playerShoot = Mix_LoadWAV("Sound/Player_Shoot.wav");
  playerJump = Mix_LoadWAV("Sound/Player_Jump.wav");
  playerHurt = Mix_LoadWAV("Sound/Player_Hurt.wav");
  playerJumpsEnemy = Mix_LoadWAV("Sound/Player_Jumps_Enemy.wav");
  enemyDies = Mix_LoadWAV("Sound/Enemy_Dies.wav");
  gameOver = Mix_LoadWAV("Sound/Game_Over.wav");
}
