//
//  SUPER HERO VERSUS HORDE OF MONSTERS
//
//  Created by Elias Farhan on 14/12/16.
//  Copyright © 2016 Elias Farhan. All rights reserved.
//

#include <iostream>
#include <list>
#include <Characters.h>

int main(
)
{
    Hero hero = Hero(10,10,10,10);
    std::list<Monster> monsters = {
        Monster(10, 1, 1, 5),
		Monster(20, 5, 5, 5),
        Monster(30, 10, 10, 5)
    };
    
    for(auto& monster : monsters)
    {
        while (hero.isAlive() && monster.isAlive())
        {
            hero.fight(monster);
            monster.fight(hero);
        }
  
        if(!monster.isAlive()){
            monster.death();
			hero.levelUp();
        }
        if(!hero.isAlive())
		{
            hero.death();
            break;
        }
    }
	hero.save();
    system("pause");
    return 0;
}
