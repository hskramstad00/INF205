#include "monster.h"
#include <iostream>

int main()
{   
    Monster monster{ 100 };

    monster.takeDamage(50);

    std::cout << "Monster hp: " << monster.getHp() << '\n';

    return 0;
}