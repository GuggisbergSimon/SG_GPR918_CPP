#include <ex8class/Map.h>
#include <iostream>


Map::Map() {
	

}

bool Map::AddGameObjectAt(std::unique_ptr<GameObject> gameObject) {
	Vector2D position = gameObject->GetPosition();
	return AddGameObjectAt(std::move(gameObject), position.x, position.y);
}

bool Map::AddGameObjectAt(std::unique_ptr<GameObject> gameObject, int positionX, int positionY) {

	if (map[positionX][positionY] == nullptr) 
	{
		gameObjectsForUpdate.push_back(gameObject.get());
		map[positionX][positionY] = std::move(gameObject);
		return true;
	}

	return false;
}

GameObject* Map::GetContentAtPosition(Vector2D position) {
	return map[position.x][position.y].get();
}

bool Map::CheckObjectExistAt(Vector2D position) {
	return map[position.x][position.y] != nullptr;
}

bool Map::RemoveObjectAt(Vector2D position) {
	if (map[position.x][position.y] != nullptr) 
	{
		map[position.x][position.y] = nullptr;
		return true;
	}
	return false;
}

bool Map::MoveGameObjetTo(GameObject & gameObject, int newPosX, int newPosY) {
	if (newPosX >= map.size() || newPosY >= map[0].size()) {
		return false;
	}
	if (map[newPosX][newPosY] != nullptr)
	{
		return false;
	}
	Vector2D currentPosition = gameObject.GetPosition();
	map[newPosX][newPosY] = std::move(map[currentPosition.x][currentPosition.y]);
	map[currentPosition.x][currentPosition.y] = nullptr;
	gameObject.SetPosition(Vector2D(newPosX, newPosY));

	return true;
}

void Map::Update() {
	for (auto & gameObject : gameObjectsForUpdate) {
		gameObject->Update();

	}
	//Destroy element 

	//Destroy map elements 
	for (auto & gameObject : gameObjectsForUpdate) {
		if (gameObject->IsObjectDestroyed()) {
			RemoveObjectAt(gameObject->GetPosition());
		}
	}
	gameObjectsForUpdate.remove_if([](GameObject * gameObject) {return gameObject->IsObjectDestroyed(); });

	//Destroy updates elements 
	}

void Map::DisplayMap() {
	system("cls");

	std::cout << "-------------------------" << std::endl;

	for (int x = 0; x < map.size(); x++) {
		std::cout << "|";
		for (int y = 0; y < map[x].size(); y++) {
			if (CheckObjectExistAt(Vector2D(x, y))) {
				std::cout << map[x][y]->GetImage();
			}
			else {
				std::cout << " ";
			}
		}
		std::cout << "|" << std::endl;
	}
	std::cout << "-------------------------" << std::endl;

	system("Pause");
}

int Map::CountCreaturesInMap() {
	int counter = 0;
	for (int x = 0; x < map.size(); x++) {
		for (int y = 0; y < map[x].size(); y++) {
			if (CheckObjectOfTypeExistAt<Creature>(Vector2D(x, y))) {
				counter++;
			}
		}

	}

	return 0;
}