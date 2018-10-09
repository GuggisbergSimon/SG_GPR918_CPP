#include "food.h"

Food::Food(Simulation* simulation) : GameObject(simulation)
{
}

char Food::getImage()
{
	return 'F';
}
