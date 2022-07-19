#pragma once

#include <fstream>
#include <string>
#include <algorithm> 

#include "scene.hpp"
#include "textObject.hpp"
#include "character.hpp"
#include "button.hpp"

class GameOver : public Scene {
private:
	TextObject title;
	TextObject score;
	Button quitButton;
	Button menuButton;
	struct LeaderboardStats {
		int score;
		std::string name;
	};
	LeaderboardStats  leaderboardStats[6];
public:
	GameOver(sf::RenderWindow& window, Character& player, Character& enemy, sf::Font& font, sf::Color& fillColor, int& curScene, bool& justSwitched,bool didPlayerWin);
	~GameOver();

	void CreateGameObjects();

	void PlayerDied(Character& player, int kills);

	void FillLeaderboard(int point,int score, std::string name);

	void orderLeaderboard();

};