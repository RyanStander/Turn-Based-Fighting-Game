#pragma once

#include <fstream>

#include "scene.hpp"
#include "textObject.hpp"
#include "character.hpp"
#include "button.hpp"

class MainMenu : public Scene{
private:
	TextObject menuTitle;
	TextObject leaderboard;
	TextObject difficultyText;
	Button startGameButton;
	Button quitButton;
	Button loadButton;
	Button eraseButton;
	Button toggleDifficulty;
	std::ifstream myfileRead;
public:
	MainMenu(sf::RenderWindow &window,Character &player,Character &enemy, sf::Font &font, sf::Color &fillColor, int &curScene, bool& justSwitched,int &difficulty);
	~MainMenu();

	void AddMainMenuObjects();

	void LoadLeaderboard();
};