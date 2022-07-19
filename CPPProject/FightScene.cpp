#include "FightScene.hpp"

FightScene::FightScene(sf::RenderWindow& window, Character& player, Character& enemy, sf::Font& font, sf::Color& fillColor, int& curScene, bool& justSwitched, int& skillLimit) :
    Scene("FightScene"),
    playerName("characterNameText", font, player.getName()),
    playerAvatar("soldierSprite", player.getSpriteFile()),
    hpText("hpText", font, "Health: " + std::to_string(player.getHP())),
    attackText("attackText", font, "Attack: " + std::to_string(player.getAttack())),
    hackText("hackText", font, "Hack: " + std::to_string(player.getHack())),
    repairText("repairText", font, "Repair: " + std::to_string(player.getRepair())),
    enemyName("enemyNameText", font, enemy.getName()),
    enemyAvatar("enemySprite", enemy.getSpriteFile()),
    enemyHPText("enemyHPText", font, "Health: " + std::to_string(enemy.getHP())),
    combatText("CombatText", font, "Fight!"),
    attackButton("attackButton", font, "Attack", sf::Vector2f(192.5f, 50.0f), fillColor),
    hackButton("hackButton", font, "Hack", sf::Vector2f(192.5f, 50.0f), fillColor),
    repairButton("repairButton", font, "Repair", sf::Vector2f(192.5f, 50.0f), fillColor),
    exportButton("exportButton", font, "Export", sf::Vector2f(192.5f, 50.0), fillColor),
    returnMenuButton("returnMenuButton", font, "Menu", sf::Vector2f(192.5f, 50.0f), fillColor),
    kills(0)
{
    isPlayerTurn = true;
#pragma region TextObjects
    playerName.setPosition(sf::Vector2f(109.0f, 34.0f));
    playerName.setCharacterSize(26);
    playerName.setFillColor(fillColor);

    playerAvatar.setPosition(sf::Vector2f(135.0f, 90.0f));
    playerAvatar.setScale(sf::Vector2f(2.5f, 2.5f));

    hpText.setPosition(sf::Vector2f(140.0f, 238.0f));
    hpText.setCharacterSize(26);
    hpText.setFillColor(fillColor);

    attackText.setPosition(sf::Vector2f(140.0f, 290.0f));
    attackText.setCharacterSize(26);
    attackText.setFillColor(fillColor);

    hackText.setPosition(sf::Vector2f(140.0f, 345.0f));
    hackText.setCharacterSize(26);
    hackText.setFillColor(fillColor);

    repairText.setPosition(sf::Vector2f(140.0f, 400.0f));
    repairText.setCharacterSize(26);
    repairText.setFillColor(fillColor);

    enemyName.setPosition(sf::Vector2f(809.0f, 34.0f));
    enemyName.setCharacterSize(26);
    enemyName.setFillColor(fillColor);

    enemyAvatar.setPosition(sf::Vector2f(835.0f, 90.0f));
    enemyAvatar.setScale(sf::Vector2f(2.5f, 2.5f));

    enemyHPText.setPosition(sf::Vector2f(861.0f, 238.0f));
    enemyHPText.setCharacterSize(26);
    enemyHPText.setFillColor(fillColor);

    combatText.setPosition(sf::Vector2f(751.0f, 508.0f));
    combatText.setCharacterSize(23);
    combatText.setFillColor(fillColor);
#pragma endregion

#pragma region Buttons
    attackButton.setPosition(sf::Vector2f(108.0f, 500.0f));
    attackButton.setButtonAction([&player, &enemy,this]() {
        if (rand() % 100 + 1 > enemy.getIllusive()) {
            int damage = player.attackCharacter(enemy);
            enemy.takeDamage(damage);
            combatText.setText(enemy.getName() + " got attacked for " + std::to_string(damage) + " damage!");
            enemyHPText.setText("Health: " + std::to_string(enemy.getHP()));
        }else{
            combatText.setText(enemy.getName() + " dodge the attack!");
        }
        isPlayerTurn = false;
        });

    hackButton.setPosition(sf::Vector2f(308.0f, 500.0f));
    hackButton.setButtonAction([&player, &enemy,this]() {
        if (rand() % 100 + 1 > enemy.getIllusive()) {
        int damage = player.hackCharacter(enemy);
        enemy.takeDamage(damage);
        enemyHPText.setText("Health: " + std::to_string(enemy.getHP()));
        combatText.setText(enemy.getName() + " got hacked for " + std::to_string(damage) + " damage!");
        }
        else {
            combatText.setText(enemy.getName() + " illuded the hack!");
        }
        isPlayerTurn = false;
        });

    repairButton.setPosition(sf::Vector2f(508.0f, 500.0f));
    repairButton.setButtonAction([&player,this]() {
        combatText.setText(player.getName() + " repaired themselves for " + std::to_string(player.RepairSelf()) + " health!");
        hpText.setText("Health: " + std::to_string(player.getHP()));
        isPlayerTurn = false;
        });

    exportButton.setPosition(sf::Vector2f(308.0f, 560.0f));
    exportButton.setButtonAction([&player,&enemy]() {
        std::ofstream myfileWrite("gameSave.cmgt", std::ios::trunc);
        myfileWrite << player.getName() << std::endl;
        myfileWrite << player.getStr() << std::endl;
        myfileWrite << player.getDex() << std::endl;
        myfileWrite << player.getIntel() << std::endl;
        myfileWrite << player.getHP() << std::endl;
        myfileWrite << enemy.getName() << std::endl;
        myfileWrite << enemy.getStr() << std::endl;
        myfileWrite << enemy.getDex() << std::endl;
        myfileWrite << enemy.getIntel() << std::endl;
        myfileWrite << enemy.getHP() << std::endl;
        myfileWrite.close();
        });

    returnMenuButton.setPosition(sf::Vector2f(508.0f, 560.0f));
    returnMenuButton.setButtonAction([&curScene, &justSwitched]() {
        curScene = 1;
        justSwitched = true;
        });
#pragma endregion
}

FightScene::~FightScene()
{
}

void FightScene::AddFightSceneObjects()
{
    addGameObject(playerName);
    addGameObject(playerAvatar);
    addGameObject(hpText);
    addGameObject(attackText);
    addGameObject(hackText);
    addGameObject(repairText);
    addGameObject(combatText);

    addGameObject(attackButton);
    addGameObject(hackButton);
    addGameObject(repairButton);
    addGameObject(exportButton);
    addGameObject(returnMenuButton);

    addGameObject(enemyName);
    addGameObject(enemyAvatar);
    addGameObject(enemyHPText);
}

void FightScene::UpdateValues(Character& player,Character& enemy)
{
    hpText.setText("Health: " + std::to_string(player.getHP()));
    attackText.setText("Attack: " + std::to_string(player.getAttack()));
    hackText.setText("Hack: " + std::to_string(player.getHack()));
    repairText.setText("Repair: " + std::to_string(player.getRepair()));
    enemyHPText.setText("Health: "+ std::to_string(enemy.getHP()));

    if (player.getSpeed() >= enemy.getSpeed()) {
        isPlayerTurn = true;
        combatText.setText(player.getName()+" is faster, they get first strike");
    }
    else {
        isPlayerTurn = false;
        combatText.setText(enemy.getName() + " is faster, they get first strike");
    }
}

bool FightScene::IsPlayerTurn()
{
    return isPlayerTurn;
}

void FightScene::EnemyTakeTurn(Character &enemy,Character &player,int &difficulty)
{
    //lower hp higher need for heal
    //but only if repair is high
    //missinghp/3*int

    //start with attack->hack->(missinghp/2+repair)->do nothing
    //random between 0 and total value
    //prev~prev+stat range for it to be considered true
    //if in the range perform
    int doNothingChance;
    int repairChanceModifier;
    if (difficulty == 1) {
        doNothingChance = 2;
        repairChanceModifier = 5;
    }
    else {
        doNothingChance = 5;
        repairChanceModifier = 3;
    }
    
    int chosenAction = rand() % (enemy.getAttack() + enemy.getHack() +((enemy.getMaxHP()-enemy.getHP())/ repairChanceModifier *enemy.getRepair())+doNothingChance);
    int startVal = 0;
    int endVal = enemy.getAttack();
    printf_s("chosenAction is %i ;", chosenAction);
    if (startVal<=chosenAction && endVal>chosenAction) {
        printf_s("Whack between %i ~ %i\n", startVal, endVal);
        if (rand() % 100 + 1 > enemy.getIllusive()) {
            int damage = enemy.attackCharacter(player);
            player.takeDamage(damage);
            combatText.setText(combatText.getTextStr() + "\n\nPlayer got attacked for " + std::to_string(damage) + " damage!");
        }
        else {
            combatText.setText(combatText.getTextStr() + "\n\n" + player.getName() + " evaded the attack!");
        }
    }
    startVal = endVal;
    endVal += enemy.getHack();
    if (startVal <= chosenAction && endVal > chosenAction) {
        printf_s("Hack between %i ~ %i\n", startVal, endVal);
        if (rand()%100 + 1 > enemy.getIllusive()) {
        int damage = enemy.hackCharacter(player);
        player.takeDamage(damage);
        combatText.setText(combatText.getTextStr() + "\n\nPlayer got hacked for " + std::to_string(damage) + " damage!");
        }
        else {
            combatText.setText(combatText.getTextStr() +"\n\n" +player.getName() + " illuded the hack!");
        }
    }
    startVal = endVal;
    endVal += ((enemy.getMaxHP() - enemy.getHP()) / repairChanceModifier * enemy.getRepair());
    if (startVal <= chosenAction && endVal > chosenAction) {
        printf_s("Repair between %i ~ %i\n", startVal, endVal);

        combatText.setText(combatText.getTextStr() + "\n\nEnemy repaired themself for " + std::to_string(enemy.RepairSelf()) + " health!");
        enemyHPText.setText("Health: " + std::to_string(enemy.getHP()));
    }
    startVal = endVal;
    endVal += doNothingChance;
    if (startVal <= chosenAction && endVal >= chosenAction) {
        printf_s("Fart between %i ~ %i\n", startVal, endVal);

        combatText.setText(combatText.getTextStr() + "\n\nENEMY ATTA-...oh they're not doing anything...?" );
    }

    
    hpText.setText("Health: " + std::to_string(player.getHP()));
    isPlayerTurn = true;
}

int FightScene::GetKills() const
{
    return kills;
}

void FightScene::IncKills()
{
    printf_s("another one");
    kills++;
}

void FightScene::setKills(int val)
{
    kills = val;
}
