#ifndef EX8_FOOD
#define EX8_FOOD

#include "gameobject.h"

class Food : public GameObject
{
public:
	Food(Simulation* simulation);
	char getImage();
};

#endif EX8_FOOD
