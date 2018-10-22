//
//  Characters.cpp
//  Test
//
//  Created by Elias Farhan on 14/12/16.
//  Copyright © 2016 Elias Farhan. All rights reserved.
//

#include "Characters.h"
#include <fstream>
#include <random>
#include <json.hpp>

// for convenience
using json = nlohmann::json;
//////////Character////////////

Character::Character(int health, int attack, int defense, int strength):
health(health), attack(attack), defense(defense), strength(strength)
{
   
}

bool Character::isAlive()
{
	return health > 0;
}

void Character::takeDamage(int damage)
{
    health -= damage;
}


int Character::getAttack()
{
    return attack;
}

int Character::getStrength()
{
	return strength;
}

int Character::getHealth()
{
	return health;
}

int Character::getDefense()
{
    return defense;
}


//////////Monster////////////

void Monster::fight(Hero& hero)
{
    int damage = static_cast<double>(attack)/hero.getDefense()*strength;
	if (damage < 1) 
	{
		damage = 1;
	}
	if (damage > strength)
	{
		damage = strength;
	}
    std::cout << "Monster gives "<<damage<<" to Hero\n";
    hero.takeDamage(damage);
}

void Monster::death()
{
    std::cout << "Yet another dead monster!\n";

}

Hero::Hero(int health, int attack, int defense, int strength) : Character(health, attack, defense, strength)
{
	std::ifstream saveDataFile("data/debug_hero.json");//RAII Resource Allocation Is Initialization
	if (saveDataFile.is_open())
	{
		json saveDataJson;
		try {
			saveDataJson << saveDataFile;

			this->strength = saveDataJson["strength"];
			this->defense = saveDataJson["defense"];
			this->attack = saveDataJson["attack"];
		}
		catch(nlohmann::detail::parse_error& e)
		{
			std::cerr << "[Error] no json in save file \n";
		}
		
	}
	else
	{
		std::cerr << "[Error] Could not open file\n";
	}
	saveDataFile.close();
}

//////////Hero////////////


void Hero::fight(Monster& monster)
{
	int damage = static_cast<double>(attack)/monster.getDefense()*strength;
    if(damage < 1)
        damage = 1;
    if(damage > strength)
        damage = strength;

    std::cout << "Hero gives "<<damage<<" to Monster\n";
    monster.takeDamage(damage);
}
void Hero::death()
{
	
    std::cout << "The hero is dead, long live the hero!\n";
}

void Hero::levelUp()
{
	strength += rand() % 5;
	defense += rand() % 5;
	attack += rand() % 5;
}

void Hero::save()
{
	std::ofstream saveDataFile("data/debug_hero.json");
	if (saveDataFile.is_open())
	{
		json saveDataJson;
		saveDataJson["strength"] = strength;
		saveDataJson["defense"] = defense;
		saveDataJson["attack"] = attack;

		saveDataFile << saveDataJson.dump();
	}
	else
	{
		std::cerr << "[Error] Could not open file to write\n";
	}
	saveDataFile.close();
}
