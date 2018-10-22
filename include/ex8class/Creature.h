#ifndef EX8_CREATURE_H
#define EX8_CREATURE_H

#include <ex8class/GameObject.h>
#include "Vector2d.h"

class Simulation;

class Creature : public GameObject
{
public:

	Creature(Simulation * simulation, int hungerSpeedIncrement);
	void Update() override;
	char GetImage() override;


private:
	//Return position. If food is not find, we return the value (-1,-1)
	Vector2D FindNearbyFoodPosition();

	//Return position. If creature is not find, we return the value (-1,-1)
	Vector2D FindNearbyCreaturePosition();
	void MoveRandomly();
	void Die();

	void IncrementHunger();

	int hungerPercent;
	int hungerSpeedIncrement;



};

#endif