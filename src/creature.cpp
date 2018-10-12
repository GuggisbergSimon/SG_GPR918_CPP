#include <vector>
#include "creature.h"
#include "constant.h"
#include "gameobjectbuilder.h"
#include "food.h"
#include "simulation.h"

Creature::Creature(Simulation* simulation, int hungerSpeedIncrement) : GameObject(simulation),
                                                                       hungerSpeedIncrement(hungerSpeedIncrement)
{
	hungerPourcent = 0;
	isParent = false;
}

void Creature::update()
{
	if (isDestroyed)
	{
		return;
	}
	randomMove();

	if (hungerPourcent >= 100)
	{
		die();
		return;
	}
	Vector2D foodPosition = findnearbyFoodPosition();
	if (foodPosition.x >= 0)
	{
		GameObject& gameObject = simulation->map.getContentAtPosition(foodPosition);
		if (!gameObject.isObjectDestroyed())
		{
			gameObject.destroy();
			hungerPourcent = 0;
		}
	}
	Vector2D creaturePosition = findnearbyCreaturePosition();
	//to add in conditions : check if there is an area when can spawn
	if (creaturePosition.x >= 0)
	{
		Creature& creature = *dynamic_cast<Creature*>(&simulation->map.getContentAtPosition(creaturePosition));
		if (!creature.isParenthood())
		{
			std::vector<Vector2D> positions;
			for (int x = position.x - 1; x < position.x + 2; x++)
			{
				if (x < 0 || x >= MAP_SIZE)
				{
					continue;
				}
				for (int y = position.y - 1; y < position.y + 2; y++)
				{
					if (y < 0 || y >= MAP_SIZE)
					{
						continue;
					}
					positions.push_back(Vector2D(x, y));
				}
			}
			simulation->map.AddGameObjectAt(GameObjectBuilder::buildChild(*simulation, positions));
			creature.setParenthood(true);
			setParenthood(true);
		}
	}

	incrementHunger();
}

char Creature::getImage()
{
	return 'C';
}

bool Creature::isParenthood()
{
	return isParent;
}

void Creature::setParenthood(bool parenthood)
{
	isParent = parenthood;
}

//Return position. If food is not find, we return the value (-1,-1)
Vector2D Creature::findnearbyFoodPosition()
{
	Vector2D positionCentral = position;
	for (int x = positionCentral.x - 1; x < positionCentral.x + 2; x++)
	{
		if (x < 0 || x >= MAP_SIZE)
		{
			continue;
		}
		for (int y = positionCentral.y - 1; y < positionCentral.y + 2; y++)
		{
			if (y < 0 || y >= MAP_SIZE)
			{
				continue;
			}
			Vector2D currentPosition(x, y);
			if (simulation->map.gameObjectOfTypeExistAt<Food>(currentPosition))
			{
				return currentPosition;
			}
		}
	}

	return Vector2D(-1, -1);
}

//Return position. If creature is not find, we return the value (-1,-1)
Vector2D Creature::findnearbyCreaturePosition()
{
	Vector2D positionCentral = position;
	for (int x = positionCentral.x - 1; x < positionCentral.x + 2; x++)
	{
		if (x < 0 || x >= MAP_SIZE)
		{
			continue;
		}
		for (int y = positionCentral.y - 1; y < positionCentral.y + 2; y++)
		{
			if (y < 0 || y >= MAP_SIZE)
			{
				continue;
			}
			Vector2D currentPosition(x, y);
			if (simulation->map.gameObjectOfTypeExistAt<Creature>(currentPosition))
			{
				return currentPosition;
			}
		}
	}

	return Vector2D(-1, -1);
}

void Creature::randomMove()
{
	int positionXMin = position.x - 1;
	if (positionXMin < 0)
		positionXMin = 0;
	int positionXMax = position.x + 1;
	if (positionXMax >= MAP_SIZE)
		positionXMax = MAP_SIZE - 1;

	int positionYMin = position.y - 1;
	if (positionYMin < 0)
		positionYMin = 0;
	int positionYMax = position.y + 1;
	if (positionYMax >= MAP_SIZE)
		positionYMax = MAP_SIZE - 1;
	int newX = simulation->getValueRandom(positionXMin, positionXMax);
	int newY = simulation->getValueRandom(positionYMin, positionYMax);
	simulation->map.MoveGameObjetTo(*this, newX, newY);
}

void Creature::die()
{
	isDestroyed = true;
}

void Creature::incrementHunger()
{
	hungerPourcent += hungerSpeedIncrement;
}
