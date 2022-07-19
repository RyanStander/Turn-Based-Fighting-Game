#pragma once

#include <fstream>

#include "scene.hpp"
#include "textObject.hpp"
#include "character.hpp"
#include "button.hpp"
#include "spriteObject.hpp"

class SkillScene : public Scene {
private:
	TextObject playerName;
	SpriteObject playerAvatar;

	TextObject strText, dexText, intelText,
		hpText, attackText, defenseText, illusiveText,speedText, hackText, securityText, repairText;
	
	TextObject skillLeft;
	
	Button toFightButton, toMainButton,
		pStr, rStr, pDex, rDex, pIntel, rIntel;
public:
	SkillScene(sf::RenderWindow& window, Character& player, Character& enemy, sf::Font& font, sf::Color& fillColor, int& curScene, bool& justSwitched, int &skillLimit);
	~SkillScene();

	void AddSkillSceneObjects();

	void UpdateText(int& skillLimit, Character& player);
};