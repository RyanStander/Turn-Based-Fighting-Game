#include "character.hpp"
#include <stdlib.h>
#include <algorithm>

Character::Character(std::string name, std::string spriteFile, int str, int dex, int intel) :
    name(name), spriteFile(spriteFile), str(str), dex(dex),intel(intel), hp(0), attack(0),
    hack(0), speed(0), defense(0), security(0), illusive(0), repair(0), strHPInc(5), strDefInc(2), strAttInc(1),
    dexIlluInc(5), dexSpdInc(1), dexAttInc(2), intHackInc(3), intSecInc(3), intRepInc(1), maxHp(0)
{
    ResetStats(str,dex,intel);
}

Character::~Character() { }

#pragma region stats
int Character::getStr() const {
    return this->str;
}
void Character::setStr(int str) {
    this->str = str;
    hp = str * strHPInc;
    maxHp = hp;
    defense = str * strDefInc;
    attack = str*strAttInc+dex*dexAttInc;
}

int Character::getDex() const {
    return this->dex;
}
void Character::setDex(int dex) {
    this->dex = dex;
    illusive = dex*dexIlluInc;
    speed = dex*dexSpdInc;
    attack = str * strAttInc + dex * dexAttInc;
}

int Character::getIntel() const {
    return this->intel;
}
void Character::setIntel(int intel) {
    this->intel = intel;
    hack = intel*intHackInc;
    security = intel*intSecInc;
    repair = intel*intRepInc;
}
#pragma endregion

#pragma region offensive
int Character::attackCharacter(const Character& character) const {
    //Just a random function
    
    //attack + -2~2 
    int attackPower = attack + rand() % 5-2; 
    // defense + -1~1
    int defensePower = character.getDefense()  + rand() % 3 - 1;

    return std::max(attackPower - defensePower, 0);
}
bool Character::takeDamage(int damage) {
    hp = std::max(hp - damage, 0);
    return hp == 0;
}
int Character::getAttack() const {
    return this->attack;
}
void Character::setAttack(int attack) {
    this->attack = attack;
}

int Character::hackCharacter(const Character& character) const {
    //Just a random function

    //attack + 0~3 
    int hackPower = hack + rand() % 5 - 2;
    // defense + -1~1
    int securityPower = character.getSecurity() + rand() % 3 - 1;

    return std::max(hackPower - securityPower, 0);
}
int Character::getHack() const {
    return this->hack;
}
void Character::setHack(int hack) {
    this->hack = hack;
}

int Character::getSpeed() const {
    return this->speed;
}
void Character::setSpeed(int speed) {
    this->speed = speed;
}
#pragma endregion

#pragma region defensive
int Character::RepairSelf() {
    //if repair is 8
    // repair + -3~4
    int healPower = repair + rand() % repair - repair / 2 + 1;
    hp = std::min(hp + healPower, maxHp);
    return healPower;
}
int Character::getRepair() const {
    return this->repair;
}
void Character::setRepair(int repair) {
    this->repair = repair;
}

int Character::getDefense() const {
    return this->defense;
}
void Character::setDefense(int defense) {
    this->defense = defense;
}

int Character::getSecurity() const {
    return this->security;
}
void Character::setSecurity(int security) {
    this->security = security;
}

int Character::getIllusive() const {
    return this->illusive;
}
void Character::setIllusive(int illusive) {
    this->illusive = illusive;
}

int Character::getHP() const {
    return this->hp;
}
void Character::setHP(int hp) {
    this->hp = hp;
}
#pragma endregion

std::string Character::getName() const {
    return this->name;
}

std::string Character::getSpriteFile() const {
    return this->spriteFile;
}

void Character::RandomStats(int statCount)
{
    for (int i = 0; i < statCount; i++)
    {
        switch (rand() % 3) {
        case 0:
            setStr(str + 1);
            break;
        case 1:
            setDex(dex + 1);
            break;
        case 2:
            setIntel(intel + 1);
            break;
        }
    }
}

int Character::getMaxHP() const
{
    return maxHp;
}

void Character::ResetStats(int str, int dex, int intel)
{
    setStr(str);
    setDex(dex);
    setIntel(intel);
    setHP(str*strHPInc);
}

void Character::setName(std::string name) {
    this->name = name;
}

