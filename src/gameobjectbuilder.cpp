#include "constant.h"
#include "gameobjectbuilder.h"
#include "simulation.h"

Creature* GameObjectBuilder::buildChild(Simulation& simulation, std::vector<Vector2D> positions)
{
	Creature* creature = new Creature(&simulation, 20);
	creature->setPosition(positions.at(simulation.getValueRandom(0, positions.size() - 1)));
	return creature;
}

Creature* GameObjectBuilder::buildCreature(Simulation& simulation)
{
	Creature* creature = new Creature(&simulation, 20);
	int x;
	int y;
	do
	{
		x = simulation.getValueRandom(0, MAP_SIZE - 1);
		y = simulation.getValueRandom(0, MAP_SIZE - 1);
	}
	while (simulation.map.gameObjectExistAt(Vector2D(x, y)));
	creature->setPosition(Vector2D(x, y));
	return creature;
}

Food* GameObjectBuilder::buildFood(Simulation& simulation)
{
	Food* food = new Food(&simulation);
	int x;
	int y;
	do
	{
		x = simulation.getValueRandom(0, MAP_SIZE - 1);
		y = simulation.getValueRandom(0, MAP_SIZE - 1);
	}
	while (simulation.map.gameObjectExistAt(Vector2D(x, y)));
	food->setPosition(Vector2D(x, y));
	return food;
}
