#include "Game.hpp"



Game::Game(sf::Font& font, sf::Color& fillColor):
window(sf::VideoMode(1280, 720), "Cyber Fighter!", sf::Style::Titlebar | sf::Style::Close),
curScene(1),
justSwitched(true),
player("Player", "head.png", 1, 1, 1),
enemy("Enemy", "head_hurt.png", 1, 1, 1),
mainMenu(window, player, enemy, font, fillColor, curScene, justSwitched,difficulty),
skillScene(window, player, enemy, font, fillColor, curScene, justSwitched, skillLimit),
fightScene(window, player, enemy, font, fillColor, curScene, justSwitched, skillLimit),
gameOver(window, player, enemy, font, fillColor, curScene, justSwitched, skillLimit),
difficulty(0)
{
    srand(time(NULL));
    skillLimit = 10;

    enemy.RandomStats(skillLimit);

#pragma region SceneSetups
    mainMenu.AddMainMenuObjects();
    skillScene.AddSkillSceneObjects();
    fightScene.AddFightSceneObjects();
    gameOver.CreateGameObjects();

    handler.addScene(fightScene);
    handler.addScene(skillScene);
    handler.addScene(mainMenu);
    handler.addScene(gameOver);
#pragma endregion 

#pragma region SceneManager

    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else {
                switch (curScene) {
                case 1:
                    mainMenu.handleEvent(event, window);
                    break;
                case 2:
                    skillScene.handleEvent(event, window);
                    break;
                case 3:
                    fightScene.handleEvent(event, window);
                    break;
                case 4:
                    gameOver.handleEvent(event, window);
                    break;
                }
            }
        }
        if (justSwitched) {
            switch (curScene) {
            case 1:
                handler.popScene();
                handler.stackScene("MainMenu");
                mainMenu.LoadLeaderboard();
                fightScene.setKills(0);
                break;
            case 2:
                handler.popScene();
                handler.stackScene("SkillScene");
                enemy.ResetStats(1, 1, 1);
                enemy.RandomStats(10);
                player.ResetStats(1, 1, 1);
                skillLimit = 10;
                skillScene.UpdateText(skillLimit,player);
                break;
            case 3:
                handler.popScene();
                handler.stackScene("FightScene");
                fightScene.UpdateValues(player, enemy);
                break;
            case 4:
                handler.popScene();
                handler.stackScene("GameOver");
                break;
            }
            justSwitched = false;
        }

        if ((!fightScene.IsPlayerTurn()) && (curScene == 3)) {
            fightScene.EnemyTakeTurn(enemy, player,difficulty);
        }
        if (player.getHP() == 0) {
            curScene = 4;
            player.ResetStats(1, 1, 1);
            skillLimit = 10;
            justSwitched = true;
            gameOver.PlayerDied(player,fightScene.GetKills());
        }
        if (enemy.getHP() == 0 && (curScene == 3)) {
            enemy.ResetStats(1, 1, 1);
            enemy.RandomStats(10);
            if (difficulty==0) {
                player.setHP(player.getMaxHP());
            }
            fightScene.UpdateValues(player,enemy);
            fightScene.IncKills();
        }
        window.clear(sf::Color::White);
        handler.update();
        handler.render(window);
        window.display();

    }
#pragma endregion
}

Game::~Game()
{
}
