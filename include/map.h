#include <constant.h>
#include <array>
#include <list>
#include "gameobject.h"

#ifndef EX8_MAP
#define EX8_MAP

class Map
{
public :
	Map();
	bool AddGameObjectAt(GameObject* gameObject);
	bool AddGameObjectAt(GameObject* gameObject, int positionX, int positionY);
	GameObject& getContentAtPosition(Vector2D position);
	template <typename T>
	bool gameObjectOfTypeExistAt(Vector2D position);
	bool gameObjectExistAt(Vector2D position);
	bool RemoveObjectAt(Vector2D position);
	bool MoveGameObjetTo(GameObject& gameObject, int positionX, int positionY);
	void update();
	void DisplayMap();
	int countCreaturesInMap();
private :
	std::array<std::array<GameObject*, MAP_SIZE>, MAP_SIZE> map;
	std::list<GameObject *> gameObjectsForUpdate;
};

#endif EX8_MAP
