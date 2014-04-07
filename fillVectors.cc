int fillVectors(std::vector<Object*>& startMenuV, std::vector<Object*>& pausMenuV, std::vector<Object*>& gameOverV, std::vector<Object*>& selectLevelV, const int& screenHeight, const int& screenWidth)
{
  startMenuV.push_back(new Object(95, 0, 180, 800, "Images/New_Game.jpg")); //0
  startMenuV.push_back(new Object(120, 0, 180, 800, "Images/New_Game_Markerad.jpg")); 
  startMenuV.push_back(new Object(95, 220, 180, 800, "Images/Select_Level.jpg")); //4
  startMenuV.push_back(new Object(115, 220, 180, 800, "Images/Select_Level_Markerad.jpg"));
  startMenuV.push_back(new Object(95, 440, 180, 800, "Images/Exit_Game.jpg")); //6
  startMenuV.push_back(new Object(120, 440, 180, 800, "Images/Exit_Game_Markerad.jpg"));

  pausMenuV.push_back(new Object(100, 0, 180, 800, "Images/Resume_Game.jpg") );
  pausMenuV.push_back(new Object(120, 0, 180, 800, "Images/Resume_Game_Markerad.jpg") );
  pausMenuV.push_back(new Object(100, 180, 180, 800, "Images/Exit_Game.jpg") );
  pausMenuV.push_back(new Object(120, 180, 180, 800, "Images/Exit_Game_Markerad.jpg") );

  gameOverV.push_back(new Object(5, 200, 180, 1300, "Images/Restart.png") );
  gameOverV.push_back(new Object(50, 200, 180, 1300, "Images/Restart_Markerad.png") );
  gameOverV.push_back(new Object(5, 380, 180, 800, "Images/Main_Menu.png") );
  gameOverV.push_back(new Object(50, 380, 180, 800, "Images/Main_Menu_markerad.png") );
  gameOverV.push_back(new Object(0, 0, screenHeight, screenWidth, "Images/Game_Over.jpg") );

  selectLevelV.push_back(new Object(5, 200, 180, 1300, "Images/Level1.png") );
  selectLevelV.push_back(new Object(25, 200, 180, 1300, "Images/Level1_markerad.png") );
  selectLevelV.push_back(new Object(5, 350, 180, 800, "Images/Level2.png") );
  selectLevelV.push_back(new Object(25, 350, 180, 800, "Images/Level2_markerad.png") );
  selectLevelV.push_back(new Object(5, 500, 180, 800, "Images/Back.png") );
  selectLevelV.push_back(new Object(25, 500, 180, 800, "Images/Back_markerad.png") );
}
