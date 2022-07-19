#pragma once

#include <SFML/Graphics.hpp>

#include <fstream>
#include <iostream>
#include <functional>
#include <string>

#include "spriteObject.hpp"
#include "character.hpp"
#include "sceneHandler.hpp"
#include "MainMenu.hpp"
#include "SkillScene.hpp"
#include "FightScene.hpp"
#include "GameOver.hpp"

class Game {
private:
	sf::RenderWindow window;

	int curScene;
	int difficulty;
	bool justSwitched;

	Character player;
	Character enemy;
	int skillLimit;

	MainMenu mainMenu;
	SkillScene skillScene;
	FightScene fightScene;
	GameOver gameOver;

	SceneHandler handler;

	sf::Event event;
public:
	Game(sf::Font &font, sf::Color &fillColor);
	~Game();
};