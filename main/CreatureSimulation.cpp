// CreatureSimulationBadCode.cpp : Defines the entry point for the console application.
//


#include <array>
#include <string>
#include <iostream>
#include <memory>
#include <random>
#include <list>

#include <ex8/Simulation.h>


void simulate() {
	Simulation simulation(445);
	simulation.Init ();
	simulation.Start ();

	std::cout << "Simulation ended" << std::endl;
}


int main()
{
	simulate();

	return EXIT_SUCCESS;
}

