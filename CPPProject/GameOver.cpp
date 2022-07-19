#include "GameOver.hpp"

GameOver::GameOver(sf::RenderWindow& window, Character& player, Character& enemy, sf::Font& font, sf::Color& fillColor, int& curScene, bool& justSwitched, bool didPlayerWin):
	Scene("GameOver"),
	title("Title", font, "Game Over"),
	score("Score", font, "Score: 0"),
	quitButton("quitButton", font, "QUIT", sf::Vector2f(192.5f, 50.0f), fillColor),
	menuButton("MenuButton", font, "Menu", sf::Vector2f(192.5f, 50.0f), fillColor)
{
	title.setPosition(sf::Vector2f(500.0f, 50.0f));
	title.setCharacterSize(43);
	title.setFillColor(fillColor);

	score.setPosition(sf::Vector2f(1000.0f, 190.0f));
	score.setCharacterSize(35);
	score.setFillColor(fillColor);

	quitButton.setPosition(sf::Vector2f(108.0f, 300.0f));
	quitButton.setButtonAction([&window]() {
		window.close();
		});
	menuButton.setPosition(sf::Vector2f(508.0f, 560.0f));
	menuButton.setButtonAction([&curScene, &justSwitched]() {
		curScene = 1;
		justSwitched = true;
		});
}

GameOver::~GameOver()
{
}

void GameOver::CreateGameObjects()
{
	addGameObject(title);
	addGameObject(score);
	addGameObject(quitButton);
	addGameObject(menuButton);
}

void GameOver::PlayerDied(Character& player, int kills)
{
	score.setText("Score: " + std::to_string(kills));
	std::fstream myfileRead("leaderboard.cmgt");
	if (!myfileRead.fail()) {
		std::string nameLine;
		std::string scoreLine;

		for (int i = 0; i < 5; i++)
		{
			std::getline(myfileRead, scoreLine);
			std::getline(myfileRead, nameLine);
			if (scoreLine == "") {
				scoreLine = "0";
			}
			FillLeaderboard(i, std::stoi(scoreLine), nameLine);
		}
		myfileRead.close();
	}
	leaderboardStats[5].name = player.getName();
	leaderboardStats[5].score = kills;
	orderLeaderboard();
	std::ofstream myfileWrite("leaderboard.cmgt", std::ios::trunc);
	if (!myfileWrite.fail()) {
		for (int i = 0; i < 5; i++)
		{
			myfileWrite << leaderboardStats[i].score << std::endl;
			myfileWrite << leaderboardStats[i].name << std::endl;
		}
		myfileWrite.close();
	}
}

void GameOver::FillLeaderboard(int point, int score, std::string name)
{
	leaderboardStats[point].name = name;
	leaderboardStats[point].score = score;
}

void GameOver::orderLeaderboard()
{
	std::sort(leaderboardStats, leaderboardStats + 6, [](LeaderboardStats a, LeaderboardStats b) {return a.score > b.score; });
}


