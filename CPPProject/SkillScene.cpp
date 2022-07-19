#include "SkillScene.hpp"

SkillScene::SkillScene(sf::RenderWindow& window, Character& player, Character& enemy, sf::Font& font, sf::Color& fillColor, int& curScene, bool& justSwitched, int& skillLimit):
	Scene("SkillScene"), 
	playerName("characterNameText", font, player.getName()),playerAvatar("soldierSprite", player.getSpriteFile()),
	strText("skillStrengthText", font, "Strength: " + std::to_string(player.getStr())), 
	dexText("skillDexterityText", font, "Dexterity: " + std::to_string(player.getDex())),
	intelText("skillIntelegenceText", font, "Intelegence: " + std::to_string(player.getIntel())), 
	hpText("skillHpText", font, "Health: " + std::to_string(player.getHP())),
	attackText("skillAttackText", font, "Attack: " + std::to_string(player.getAttack())), 
	defenseText("skillDefenseText", font, "Defense: " + std::to_string(player.getDefense())),
	illusiveText("skillIllusiveText", font, "Illusive: " + std::to_string(player.getIllusive())), 
	speedText("skillSpeedText", font, "Speed: " + std::to_string(player.getSpeed())),
	hackText("skillHackText", font, "Hack: " + std::to_string(player.getHack())),
	securityText("skillSecurityText", font, "Security: " + std::to_string(player.getSecurity())),
	repairText("skillRepairText", font, "Repair: " + std::to_string(player.getRepair())),
	skillLeft("SkillLeft", font, "Skill Points Left: 10"),
	toFightButton("NextButton", font, "NEXT",sf::Vector2f(192.5f, 50.0f), fillColor),
	toMainButton("BackButton", font, "BACK",sf::Vector2f(192.5f, 50.0f), fillColor),
	pStr("plusStrength", font, "+", sf::Vector2f(30.0f, 30.0f), fillColor),
	rStr("reduceStrength", font, "-", sf::Vector2f(30.0f, 30.0f), fillColor),
	pDex("plusDex", font, "+", sf::Vector2f(30.0f, 30.0f), fillColor),
	rDex("reduceDex", font, "-", sf::Vector2f(30.0f, 30.0f), fillColor),
	pIntel("plusIntel", font, "+", sf::Vector2f(30.0f, 30.0f), fillColor),
	rIntel("reduceIntel", font, "-", sf::Vector2f(30.0f, 30.0f), fillColor)
{
#pragma region TextObjects
	playerName.setPosition(sf::Vector2f(109.0f, 34.0f));
	playerName.setCharacterSize(26);
	playerName.setFillColor(fillColor);

	playerAvatar.setPosition(sf::Vector2f(135.0f, 90.0f));
	playerAvatar.setScale(sf::Vector2f(2.5f, 2.5f));

	strText.setPosition(sf::Vector2f(161.0f, 238.0f));
	strText.setCharacterSize(26);
	strText.setFillColor(fillColor);

	dexText.setPosition(sf::Vector2f(148.0f, 290.0f));
	dexText.setCharacterSize(26);
	dexText.setFillColor(fillColor);

	intelText.setPosition(sf::Vector2f(140.0f, 345.0f));
	intelText.setCharacterSize(26);
	intelText.setFillColor(fillColor);

	hpText.setPosition(sf::Vector2f(940.0f, 105.0f));
	hpText.setCharacterSize(26);
	hpText.setFillColor(fillColor);

	attackText.setPosition(sf::Vector2f(940.0f, 185.0f));
	attackText.setCharacterSize(26);
	attackText.setFillColor(fillColor);

	defenseText.setPosition(sf::Vector2f(940.0f, 145.0f));
	defenseText.setCharacterSize(26);
	defenseText.setFillColor(fillColor);

	illusiveText.setPosition(sf::Vector2f(940.0f, 225.0f));
	illusiveText.setCharacterSize(26);
	illusiveText.setFillColor(fillColor);

	speedText.setPosition(sf::Vector2f(940.0f, 265.0f));
	speedText.setCharacterSize(26);
	speedText.setFillColor(fillColor);

	hackText.setPosition(sf::Vector2f(940.0f, 305.0f));
	hackText.setCharacterSize(26);
	hackText.setFillColor(fillColor);

	securityText.setPosition(sf::Vector2f(940.0f, 345.0f));
	securityText.setCharacterSize(26);
	securityText.setFillColor(fillColor);

	repairText.setPosition(sf::Vector2f(940.0f, 385.0f));
	repairText.setCharacterSize(26);
	repairText.setFillColor(fillColor);

	skillLeft.setPosition(sf::Vector2f(500.0f, 50.0f));
	skillLeft.setCharacterSize(33);
	skillLeft.setFillColor(fillColor);
#pragma endregion

#pragma region Buttons
	toFightButton.setPosition(sf::Vector2f(108.0f, 500.0f));
	toFightButton.setButtonAction([&curScene, &justSwitched,&skillLimit]() {
		if (skillLimit) {
			curScene = 3;
			justSwitched = true;
		}
		});

	toMainButton.setPosition(sf::Vector2f(108.0f, 600.0f));
	toMainButton.setButtonAction([&curScene, &justSwitched]() {
		curScene = 1;
		justSwitched = true;
		});

	pStr.setPosition(sf::Vector2f(40.0f, 238.0f));
	pStr.setButtonAction([&player, &skillLimit,this]() {
		if (skillLimit > 0) {
			skillLimit--;
			player.setStr(player.getStr() + 1);
			strText.setText("Strength: " + std::to_string(player.getStr()));
			hpText.setText("Health: " + std::to_string(player.getHP()));
			attackText.setText("Attack: " + std::to_string(player.getAttack()));
			defenseText.setText("Defense: " + std::to_string(player.getDefense()));
			skillLeft.setText("Skill Points Left: " + std::to_string(skillLimit));
		}
		});

	rStr.setPosition(sf::Vector2f(340.0f, 238.0f));
	rStr.setButtonAction([&player, &skillLimit, this]() {
		if (player.getStr() > 1) {
			skillLimit++;
			player.setStr(player.getStr() - 1);
			strText.setText("Strength: " + std::to_string(player.getStr()));
			hpText.setText("Health: " + std::to_string(player.getHP()));
			attackText.setText("Attack: " + std::to_string(player.getAttack()));
			defenseText.setText("Defense: " + std::to_string(player.getDefense()));
			skillLeft.setText("Skill Points Left: " + std::to_string(skillLimit));
		}
		});

	pDex.setPosition(sf::Vector2f(40.0f, 290.0f));
	pDex.setButtonAction([&player, &skillLimit,this]() {
		if (skillLimit > 0) {
			skillLimit--;
			player.setDex(player.getDex() + 1);
			dexText.setText("Dexterity: " + std::to_string(player.getDex()));
			illusiveText.setText("Illusive: " + std::to_string(player.getIllusive()));
			attackText.setText("Attack: " + std::to_string(player.getAttack()));
			speedText.setText("Speed: " + std::to_string(player.getSpeed()));
			skillLeft.setText("Skill Points Left: " + std::to_string(skillLimit));
		}
		});

	rDex.setPosition(sf::Vector2f(340.0f, 290.0f));
	rDex.setButtonAction([&player, &skillLimit,this]() {
		if (player.getDex() > 1) {
			skillLimit++;
			player.setDex(player.getDex() - 1);
			dexText.setText("Dexterity: " + std::to_string(player.getDex()));
			illusiveText.setText("Illusive: " + std::to_string(player.getIllusive()));
			attackText.setText("Attack: " + std::to_string(player.getAttack()));
			speedText.setText("Speed: " + std::to_string(player.getSpeed()));
			skillLeft.setText("Skill Points Left: " + std::to_string(skillLimit));
		}
		});

	pIntel.setPosition(sf::Vector2f(40.0f, 345.0f));
	pIntel.setButtonAction([&player, &skillLimit,this]() {
		if (skillLimit > 0) {
			skillLimit--;
			player.setIntel(player.getIntel() + 1);
			intelText.setText("Intelegence: " + std::to_string(player.getIntel()));
			hackText.setText("Hack: " + std::to_string(player.getHack()));
			securityText.setText("Security: " + std::to_string(player.getSecurity()));
			repairText.setText("Repair: " + std::to_string(player.getRepair()));
			skillLeft.setText("Skill Points Left: " + std::to_string(skillLimit));
		}
		});

	rIntel.setPosition(sf::Vector2f(340.0f, 345.0f));
	rIntel.setButtonAction([&player, &skillLimit,this]() {
		if (player.getIntel() > 1) {
			skillLimit++;
			player.setIntel(player.getIntel() - 1);
			intelText.setText("Intelegence: " + std::to_string(player.getIntel()));
			hackText.setText("Hack: " + std::to_string(player.getHack()));
			securityText.setText("Security: " + std::to_string(player.getSecurity()));
			repairText.setText("Repair: " + std::to_string(player.getRepair()));
			skillLeft.setText("Skill Points Left: " + std::to_string(skillLimit));
		}
		});
#pragma endregion
}

SkillScene::~SkillScene()
{
}

void SkillScene::AddSkillSceneObjects()
{
#pragma region TextObjects
	addGameObject(playerName);
	addGameObject(playerAvatar);
	addGameObject(strText);
	addGameObject(dexText);
	addGameObject(intelText);
	addGameObject(attackText);
	addGameObject(defenseText);
	addGameObject(hpText);
	addGameObject(illusiveText);
	addGameObject(speedText);
	addGameObject(hackText);
	addGameObject(securityText);
	addGameObject(repairText);
	addGameObject(skillLeft);
#pragma endregion

#pragma region Buttons
	addGameObject(toFightButton);
	addGameObject(toMainButton);
	addGameObject(pStr);
	addGameObject(rStr);
	addGameObject(pDex);
	addGameObject(rDex);
	addGameObject(pIntel);
	addGameObject(rIntel);
#pragma endregion
}

void SkillScene::UpdateText(int &skillLimit,Character &player)
{
	skillLeft.setText("Skill Points Left: " + std::to_string(skillLimit));
	strText.setText("Strength: " + std::to_string(player.getStr()));
	dexText.setText("Dexterity: " + std::to_string(player.getStr()));
	hpText.setText("Health: " + std::to_string(player.getHP()));
	attackText.setText("Attack: " + std::to_string(player.getAttack()));
	defenseText.setText("Defense: " + std::to_string(player.getDefense()));
	intelText.setText("Intelegence: " + std::to_string(player.getIntel()));
	hackText.setText("Hack: " + std::to_string(player.getHack()));
	securityText.setText("Security: " + std::to_string(player.getSecurity()));
	repairText.setText("Repair: " + std::to_string(player.getRepair()));
	illusiveText.setText("Illusive: " + std::to_string(player.getIllusive()));
	speedText.setText("Speed: " + std::to_string(player.getSpeed()));
}
