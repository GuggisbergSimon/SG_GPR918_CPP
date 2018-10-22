#ifndef EX8_MAP_H
#define EX8_MAP_H
#include <ex8class/Vector2d.h>
#include <ex8class/GameObject.h>
#include <ex8class/Creature.h>
#include <ex8class/Food.h>

#include <array>
#include <list>
#include <memory>

const int MAP_SIZE = 10;

class Map {
public:
	Map();

	bool AddGameObjectAt(std::unique_ptr<GameObject> gameObject);

	bool AddGameObjectAt(std::unique_ptr<GameObject> gameObject, int positionX, int positionY);

	GameObject* GetContentAtPosition(Vector2D position);

	template<typename T> bool CheckObjectOfTypeExistAt(Vector2D position);


	bool CheckObjectExistAt(Vector2D position);

	bool RemoveObjectAt(Vector2D position);

	bool MoveGameObjetTo(GameObject & gameObject, int newPosX, int newPosY);

	void Update();

	void DisplayMap();

	int CountCreaturesInMap();

private:
	std::array<std::array<std::unique_ptr<GameObject>, MAP_SIZE>, MAP_SIZE> map;
	std::list<GameObject * > gameObjectsForUpdate;
};

template<typename T> bool Map::CheckObjectOfTypeExistAt(Vector2D position) {
	if (map[position.x][position.y] == nullptr) {
		return false;
	}
	auto * gameObject = dynamic_cast<T*>(map[position.x][position.y].get());
	return gameObject != nullptr;
}

#endif