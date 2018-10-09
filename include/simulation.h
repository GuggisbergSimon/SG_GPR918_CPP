#ifndef EX8_SIMULATION
#define EX8_SIMULATION

#include <random>
#include "map.h"

class Simulation
{
public:
	Map map;
	Simulation(int seed);
	void init();
	void start();
	int getValueRandom(int min, int max);

private:
	int nbrCreatures;
	int nbrHunters;
	int nbrFoodStuff;
	std::default_random_engine random;
	void update();
	bool isEndSimulation();
};

#endif EX8_SIMULATION
