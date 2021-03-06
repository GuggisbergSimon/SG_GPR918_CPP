#include <iostream>
#include <list>

class Character
{
public:
	Character(int health, int strength, int attack, int defense) : health(health), strength(strength), attack(attack),
	                                                               defense(defense)
	{
	}

	virtual void death()
	{
	}

	void fight(Character& enemy)
	{
		int damage = (attack * strength) / defense;
		if (damage < 1) { damage = 1; }
		enemy.removeHealth(damage);
		std::cout << typeid(*this).name() << " attacks " << typeid(enemy).name() << " and makes " << damage <<
			" points of damage." << std::endl;

		if (!enemy.isAlive())
		{
			enemy.death();
		}
	}

	void removeHealth(int valueLost)
	{
		health -= valueLost;
	}

	bool isAlive()
	{
		return health > 0;
	}

protected :
	int health;
	int strength;
	int attack;
	int defense;
};

class Hero : public Character
{
public:
	Hero(int health, int strength, int attack, int defense) : Character(health, strength, attack, defense)
	{
	}

	void death()
	{
		std::cout << "The hero is dead, long live the hero!" << std::endl;
	}
};

class Monster : public Character
{
public:
	Monster(int health, int strength, int attack, int defense) : Character(health, strength, attack, defense)
	{
	}

	void death()
	{
		std::cout << "Yet another dead monster!" << std::endl;
	}
};

int main()
{
	//values for testing purposes
	std::list<Monster> monsters(3, Monster(10, 10, 10, 10));
	Hero hero = Hero(20, 10, 10, 10);

	//describe each round
	while (monsters.size() > 0 && hero.isAlive())
	{
		Monster& currentMonster = monsters.front();
		hero.fight(currentMonster);
		if (!currentMonster.isAlive())
		{
			monsters.pop_front();
		}
		else
		{
			currentMonster.fight(hero);
		}
	}

	system("pause");
	return 0;
}
