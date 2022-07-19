#pragma once

#include "MainMenu.hpp"

MainMenu::MainMenu(sf::RenderWindow& window, Character& player, Character& enemy, sf::Font& font, sf::Color& fillColor, int& curScene, bool& justSwitched, int& difficulty) :
	Scene("MainMenu"),
	menuTitle("menuTitle", font, "Cyber Fighter"),
	leaderboard("Leaderboard", font, "Leaderboard:\n"),
	difficultyText("difficultyText", font, "Difficulty: Easy\n\nModifier: Heal on victory\nAverage enemies"),
	startGameButton("startGameButton", font, "START", sf::Vector2f(192.5f, 50.0f), fillColor),
	quitButton("quitButton", font, "QUIT", sf::Vector2f(192.5f, 50.0f), fillColor),
	loadButton("loadButton", font, "LOAD", sf::Vector2f(192.5f, 50.0f), fillColor),
	eraseButton("loadButton", font, "ERASE", sf::Vector2f(192.5f, 50.0f), fillColor),
	toggleDifficulty("ToggleDifficulty",font,"TOGGLE", sf::Vector2f(192.5f, 50.0f), fillColor)
{
	menuTitle.setPosition(sf::Vector2f(500.0f, 50.0f));
	menuTitle.setCharacterSize(43);
	menuTitle.setFillColor(fillColor);

	leaderboard.setPosition(sf::Vector2f(1000.0f, 190.0f));
	leaderboard.setCharacterSize(35);
	leaderboard.setFillColor(fillColor);

	difficultyText.setPosition(sf::Vector2f(500.0f, 125.0f));
	difficultyText.setCharacterSize(24);
	difficultyText.setFillColor(fillColor);

	startGameButton.setPosition(sf::Vector2f(108.0f, 200.0f));
	startGameButton.setButtonAction([&curScene, &justSwitched]() {
		curScene = 2;
		justSwitched = true;
		});

	quitButton.setPosition(sf::Vector2f(108.0f, 300.0f));
	quitButton.setButtonAction([&window]() {
		window.close();
		});

	loadButton.setPosition(sf::Vector2f(108.0f, 400.0f));
	loadButton.setButtonAction([&player,&enemy,&curScene,&justSwitched]() {
		std::ifstream myfileRead("gameSave.cmgt");
		if (!myfileRead.fail()) {
			std::string line;

			std::getline(myfileRead, line);
			if (line != "") {
				player.setName(line);

				std::getline(myfileRead, line);
				player.setStr(std::stoi(line));

				std::getline(myfileRead, line);
				player.setDex(std::stoi(line));

				std::getline(myfileRead, line);
				player.setIntel(std::stoi(line));

				std::getline(myfileRead, line);
				player.setHP(std::stoi(line));

				//---------------------

				std::getline(myfileRead, line);
				enemy.setName(line);

				std::getline(myfileRead, line);
				enemy.setStr(std::stoi(line));

				std::getline(myfileRead, line);
				enemy.setDex(std::stoi(line));

				std::getline(myfileRead, line);
				enemy.setIntel(std::stoi(line));

				std::getline(myfileRead, line);
				enemy.setHP(std::stoi(line));
				myfileRead.close();

				justSwitched = true;
				curScene = 3;
			}
		}
		});

	eraseButton.setPosition(sf::Vector2f(108.0f, 500.0f));
	eraseButton.setButtonAction([&window,this]() {
		std::ofstream myfileClear;
		myfileClear.open("gameSave.cmgt", std::ofstream::out | std::ofstream::trunc);
		myfileClear.close();
		std::ofstream leaderboardClear;
		leaderboardClear.open("leaderboard.cmgt", std::ofstream::out | std::ofstream::trunc);
		leaderboardClear.close();
		LoadLeaderboard();
		});

	toggleDifficulty.setPosition(sf::Vector2f(500.0f, 300.0f));
	toggleDifficulty.setButtonAction([&difficulty,this]() {
		if (difficulty == 0) {
			difficulty = 1;
			difficultyText.setText("Difficulty: Hard\n\nModifier: Victory Heal Disabled\nAgressive enemies");
		}
		else {
			difficulty = 0;
			difficultyText.setText("Difficulty: Easy\n\nModifier: Heal on victory\nAverage enemies");
		}
		});
}

MainMenu::~MainMenu()
{
}

void MainMenu::AddMainMenuObjects()
{
	addGameObject(menuTitle);
	addGameObject(startGameButton);
	addGameObject(quitButton);
	addGameObject(loadButton);
	addGameObject(eraseButton);
	addGameObject(leaderboard);
	addGameObject(difficultyText);
	addGameObject(toggleDifficulty);
}

void MainMenu::LoadLeaderboard()
{
	leaderboard.setText("Leaderboard: \n");
	std::ifstream myfileRead("leaderboard.cmgt");
	if (!myfileRead.fail()) {
		std::string lineval;
		std::string linestr;

		for (int i = 0; i < 5; i++)
		{
			if (!myfileRead.eof()) {
				std::getline(myfileRead, lineval);
				std::getline(myfileRead, linestr);
				leaderboard.setText(leaderboard.getTextStr() + linestr + " - " + lineval + "\n");
			}
		}
		
	}
}
