#pragma once

#include <fstream>

#include "scene.hpp"
#include "textObject.hpp"
#include "character.hpp"
#include "button.hpp"
#include "spriteObject.hpp"

class FightScene : public Scene {
private:
	TextObject playerName;
	SpriteObject playerAvatar;

	TextObject hpText, attackText, hackText, repairText;
	TextObject combatText;

	TextObject enemyName, enemyHPText;
	SpriteObject enemyAvatar;

	Button attackButton, hackButton, repairButton, exportButton, returnMenuButton;

	bool isPlayerTurn;

	int kills;
public:
	FightScene(sf::RenderWindow& window, Character& player, Character& enemy, sf::Font& font, sf::Color& fillColor, int& curScene, bool& justSwitched, int& skillLimit);
	~FightScene();

	void AddFightSceneObjects();

	void UpdateValues(Character& player, Character& enemy);

	bool IsPlayerTurn();

	void EnemyTakeTurn(Character& enemy, Character& player, int& difficulty);

	int GetKills() const;
	void IncKills();
	void setKills(int val);
};