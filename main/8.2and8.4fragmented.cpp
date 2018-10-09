#include <string>
#include <iostream>
#include "simulation.h"

void simulate()
{
	Simulation simulation(445);
	simulation.init();
	simulation.start();
	std::cout << "Simulation ended" << std::endl;
}


int main()
{
	simulate();

	return 0;
}
