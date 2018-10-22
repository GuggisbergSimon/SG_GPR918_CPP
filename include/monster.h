//
// Created by unite on 15.08.2018.
//

#ifndef SAE918_MONSTER_H
#define SAE918_MONSTER_H

class Player;

class Monster
{
public:
	void init();
private:
	static int monsterCount;
	Player& player;

};

#endif //SAE918_MONSTER_H
