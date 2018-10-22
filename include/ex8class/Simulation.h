#ifndef EX8_SIMULATION_H
#define EX8_SIMULATION_H

#include <ex8class/Map.h>
#include <random>

class Simulation {
public:

	Map map;

	Simulation(int seed);

	void Init();
	void Start();

	int GetValueRandom(int min, int max);
private:

	int nbrCreatures;
	int nbrHunters;
	int nbrFoodStuff;
	std::default_random_engine random;

	void Update();
	bool IsSimulationOver();


};

#endif