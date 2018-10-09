#ifndef EX8_CREATURE
#define EX8_CREATURE

#include "gameobject.h"

class Creature : public GameObject
{
public:
	Creature(Simulation* simulation, int hungerSpeedIncrement);
	void update();
	char getImage();
	bool isParenthood();
	void setParenthood(bool parenthood);
private:
	int hungerPourcent;
	int hungerSpeedIncrement;
	bool isParent;
	Vector2D findnearbyFoodPosition();
	Vector2D findnearbyCreaturePosition();
	void randomMove();
	void die();
	void incrementHunger();
};

#endif EX8_CREATURE
