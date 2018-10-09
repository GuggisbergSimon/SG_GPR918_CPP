#include <iostream>
#include "simulation.h"
#include "gameobjectbuilder.h"

Map map;


Simulation::Simulation(int seed) : random(seed)
{
}

void Simulation::init()
{
	//Create 5 creatures
	for (int i = 0; i < 5; i++)
	{
		map.AddGameObjectAt((GameObject*)GameObjectBuilder::buildCreature(*this));
	}


	//Create 6 foods 
	for (int i = 0; i < 6; i++)
	{
		map.AddGameObjectAt((GameObject*)GameObjectBuilder::buildFood(*this));
	}
	map.DisplayMap();
}

void Simulation::start()
{
	while (!isEndSimulation())
	{
		update();
		map.DisplayMap();
	}
	std::cout << std::endl << "------ END OF SIMULATION -------------" << std::endl;
	system("Pause");
}

int Simulation::getValueRandom(int min, int max)
{
	std::uniform_int_distribution<int> distribution(min, max);
	int randomValue = distribution(random);
	return randomValue;
}


int nbrCreatures;
int nbrHunters;
int nbrFoodStuff;

std::default_random_engine random;


void Simulation::update()
{
	map.update();
}

bool Simulation::isEndSimulation()
{
	return map.countCreaturesInMap() <= 0;
}
