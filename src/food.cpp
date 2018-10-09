#include "gameobject.h"

class Food : public GameObject
{
public:
	Food(Simulation* simulation) : GameObject(simulation)
	{
	}

	char getImage()
	{
		return 'F';
	}
};
