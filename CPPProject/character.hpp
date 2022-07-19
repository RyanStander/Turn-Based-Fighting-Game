#pragma once

#include <string>

class Character {
    private:
        std::string name;
        std::string spriteFile;
        int str;
        int strHPInc;
        int strDefInc;
        int strAttInc;

        int dex;
        int dexIlluInc;
        int dexSpdInc;
        int dexAttInc;

        int intel;
        int intHackInc;
        int intSecInc;
        int intRepInc;


        int hp;
        int maxHp;
        int attack;
        int hack;
        int speed;
        int defense;
        int security;
        int illusive;
        int repair;

    public:
        Character(std::string name, std::string spriteFile, 
                    int str,int dex, int intel
                    );
        ~Character();

        int getStr() const;
        void setStr(int str);

        int getDex() const;
        void setDex(int dex);

        int getIntel() const;
        void setIntel(int intel);


        int attackCharacter(const Character& character) const;
        bool takeDamage(int damage);

        int getAttack() const;
        void setAttack(int attack);

        int hackCharacter(const Character& character) const;

        int getHack() const;
        void setHack(int hack);

        int getDefense() const;
        void setDefense(int defense);

        int getSecurity() const;
        void setSecurity(int security);

        int getIllusive() const;
        void setIllusive(int illusive);

        int getHP() const;
        void setHP(int hp);

        int getSpeed() const;
        void setSpeed(int speed);

        int RepairSelf();
        int getRepair() const;
        void setRepair(int repair);

        std::string getName() const;
        void setName(std::string name);

        std::string getSpriteFile() const;

        void RandomStats(int statCount);

        int getMaxHP() const;

        void ResetStats(int str, int dex, int intel);
};


