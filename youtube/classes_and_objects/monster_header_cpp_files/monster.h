#pragma once
// pragma once means that it prevents the file to be included multipel times in a singel complications
class Monster
{
    private:
        int mHp;

    public:
        Monster(int hp);
        int getHp();
        void takeDamage(int amount);
};