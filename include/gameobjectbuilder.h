#ifndef EX8_GAMEOBJECTBUILDER
#define EX8_GAMEOBJECTBUILDER

class Simulation;
class Creature;
class Food;

#include <vector>
#include "vector2d.h"

class GameObjectBuilder
{
public:
	static Creature* buildCreature(Simulation& simulation);
	static Creature* buildChild(Simulation& simulation, std::vector<Vector2D> positions);
	static Food* buildFood(Simulation& simulation);
};

#endif EX8_GAMEOBJECTBUILDER
