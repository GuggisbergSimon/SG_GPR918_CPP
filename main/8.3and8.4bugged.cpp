
#include <array>
#include <string>
#include <iostream>
#include <memory>
#include <random>
#include <list>

struct Vector2D {
	Vector2D(int x, int y) :x(x), y(y) {

	}
	Vector2D() {
		x = 0;
		y = 0;
	}
	int x;
	int y;
};



const int MAP_SIZE = 10;
class Map;
class Simulation;
class Creature;
class Food;
class GameObject;

class  GameObjectBuilder {
public:
	static std::unique_ptr<Creature> buildCreature(Simulation & simulation);
	static std::unique_ptr<Food> buildFood(Simulation & simulation);
};

class GameObject {

public:
	GameObject(Simulation * simulation, Vector2D position) :simulation(simulation), position(position) {

	}

	GameObject(Simulation * simulation) :simulation(simulation) {
		isDestroyed = false;
	}

	virtual void update() {

	}

	virtual void start() {

	}

	virtual char getImage() {
		return '?';
	}

	Vector2D getPosition() {
		return position;
	}

	void setPosition(Vector2D position) {
		this->position = position;
	}

	bool isObjectDestroyed() {
		return isDestroyed;
	}

	void destroy() {
		isDestroyed = true;
	}


protected:
	Vector2D position;
	Simulation * simulation;
	bool isDestroyed;

};

class Food : public GameObject {
public:
	Food(Simulation * simulation) :GameObject(simulation) {

	}

	char getImage() {
		return 'F';
	}

};

class Map {
public:
	Map() {
		for (auto & row : map) {
			for (auto& column : row)
			{
				column = nullptr;
			}
			//row.fill(nullptr);
		}

	}

	bool AddGameObjectAt(std::unique_ptr<GameObject> &gameObject) {
		Vector2D position = gameObject->getPosition();
		return AddGameObjectAt(std::move(gameObject), position.x, position.y);
	}

	bool AddGameObjectAt(std::unique_ptr<GameObject> gameObject, int positionX, int positionY) {
		GameObject * mapPosition = map[positionX][positionY].get();
		if (mapPosition == nullptr) {
			map[positionX][positionY] = move(std::make_unique<GameObject>(*gameObject));
			gameObjectsForUpdate.push_back(move(std::make_unique<GameObject>(*gameObject)));
			return true;
		}
		return false;
	}

	GameObject & getContentAtPosition(Vector2D position) {
		return *map[position.x][position.y];
	}

	template<typename T> bool gameObjectOfTypeExistAt(Vector2D position) {
		if (map[position.x][position.y] == nullptr) {
			return false;
		}

		//also not sure if get() for position.x and position.y
		/*GameObject* object = map[position.x][position.y].get();
		std::cout << "test" << std::endl;
		T * gameObject = dynamic_cast<T*>(object);
		return gameObject != nullptr;*/
		return true;
	}


	bool gameObjectExistAt(Vector2D position) {
		return map[position.x][position.y] != nullptr;
	}

	bool RemoveObjectAt(Vector2D position) {
		if (map[position.x][position.y] != nullptr) {
			//delete map[position.x][position.y];
			//just put the line in comment CHECK IF MEMORY IS NOT DESCENDING WHEN REMOVING OBJECTS
			map[position.x][position.y] = nullptr;
			return true;
		}
		return false;
	}

	bool MoveGameObjetTo(GameObject & gameObject, int positionX, int positionY) {
		if (positionX >= map.size() || positionY >= map[0].size()) {
			return false;
		}
		if (map[positionX][positionY] != nullptr)
		{
			return false;
		}
		Vector2D currentPosition = gameObject.getPosition();
		map[currentPosition.x][currentPosition.y] = nullptr;
		map[positionX][positionY] = std::make_unique<GameObject>(gameObject);
		gameObject.setPosition(Vector2D(positionX, positionY));
		
		return true;
	}

	void update() {
		for (auto & gameObject : gameObjectsForUpdate) {
			gameObject->update();
		}
		//Destroy element 

		//Destroy map elements 
		for (auto & gameObject : gameObjectsForUpdate) {
			if (gameObject->isObjectDestroyed()) {
				RemoveObjectAt(gameObject->getPosition());
			}
		}
		//Destroy updates elements 
		for (auto& gameObject : gameObjectsForUpdate)
		{
			if (gameObject->isObjectDestroyed())
			{
				gameObjectsForUpdate.remove(gameObject);
			}
		}
		//kinda works... to debug
		//gameObjectsForUpdate.remove_if([](GameObject * gameObject) {return gameObject->isObjectDestroyed(); });
	}

	void DisplayMap() {
		system("cls");

		std::cout << "-------------------------" << std::endl;

		for (int x = 0; x < map.size(); x++) {
			std::cout << "|";
			for (int y = 0; y < map[x].size(); y++) {
				if (gameObjectExistAt(Vector2D(x, y))) {
					std::cout << map[x][y]->getImage();
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

	int countCreaturesInMap() {
		int counter = 0;
		for (int x = 0; x < map.size(); x++) {
			for (int y = 0; y < map[x].size(); y++) {
				if (gameObjectOfTypeExistAt<Creature>(Vector2D(x, y))) {
					counter++;
				}
			}

		}

		return counter;
	}

private:
	std::array<std::array<std::unique_ptr<GameObject>, MAP_SIZE>, MAP_SIZE> map;
	std::list<std::unique_ptr<GameObject>> gameObjectsForUpdate;




};

class Simulation {
public:

	Map map;



	Simulation(int seed) :random(seed) {

	}

	void init() {
		//Create 5 creatures 
		for (int i = 0; i < 5; i++) {
			std::unique_ptr<Creature> creature = GameObjectBuilder::buildCreature(*this);
			map.AddGameObjectAt(std::move(creature));
			//map.AddGameObjectAt(GameObjectBuilder::buildCreature(*this).get());
		}


		//Create 6 foods 
		for (int i = 0; i < 6; i++) {
			map.AddGameObjectAt(GameObjectBuilder::buildFood(*this).get());
		}
		map.DisplayMap();
	}

	void start() {
		while (!isEndSimulation()) {
			update();
			map.DisplayMap();
		}
		std::cout << std::endl << "------ END OF SIMULATION -------------" << std::endl;
		system("Pause");
	}

	int getValueRandom(int min, int max) {
		std::uniform_int_distribution<int> distribution(min, max);
		int randomValue = distribution(random);
		return randomValue;
	}




private:

	int nbrCreatures;
	int nbrHunters;
	int nbrFoodStuff;

	std::default_random_engine random;



	void update() {

		map.update();


	}

	bool isEndSimulation() {
		return map.countCreaturesInMap() <= 0;
	}


};


class Creature : public GameObject
{
public:

	Creature(Simulation * simulation, int hungerSpeedIncrement) :GameObject(simulation), hungerSpeedIncrement(hungerSpeedIncrement) {
		hungerPourcent = 0;

	}




	void update() {
		if (isDestroyed) {
			return;
		}
		randomMove();

		if (hungerPourcent >= 100) {
			die();
			return;
		}
		Vector2D foodPosition = findnearbyFoodPosition();
		if (foodPosition.x >= 0) {

			GameObject & gameObject = simulation->map.getContentAtPosition(foodPosition);
			if (!gameObject.isObjectDestroyed()) {
				gameObject.destroy();
				hungerPourcent = 0;
			}
		}

		incrementHunger();
	}
	char getImage() {
		return 'C';
	}


private:

	int hungerPourcent;
	int hungerSpeedIncrement;

	//Return position. If food is not find, we return the value (-1,-1)
	Vector2D findnearbyFoodPosition() {
		Vector2D positionCentral = position;
		for (int x = positionCentral.x - 1; x < positionCentral.x + 2; x++) {
			if (x < 0 || x >= MAP_SIZE) {
				continue;
			}
			for (int y = positionCentral.y - 1; y < positionCentral.y + 2; y++) {
				if (y < 0 || y >= MAP_SIZE) {
					continue;
				}
				Vector2D currentPosition(x, y);
				if (simulation->map.gameObjectOfTypeExistAt<Food>(currentPosition)) {
					return currentPosition;
				}
			}
		}
		return Vector2D(-1, -1);
	}

	//Return position. If creature is not find, we return the value (-1,-1)
	Vector2D findnearbyCreaturePosition() {
		Vector2D positionCentral = position;
		for (int x = positionCentral.x - 1; x < positionCentral.x + 2; x++) {
			if (x < 0 || x >= MAP_SIZE) {
				continue;
			}
			for (int y = positionCentral.y - 1; y < positionCentral.y + 2; y++) {
				if (y < 0 || y >= MAP_SIZE) {
					continue;
				}
				Vector2D currentPosition(x, y);
				if (simulation->map.gameObjectOfTypeExistAt<Creature>(currentPosition)) {
					return currentPosition;
				}
			}
		}
		return Vector2D(-1, -1);
	}



	void randomMove() {
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
	void die() {

		isDestroyed = true;
	}

	void incrementHunger() {
		hungerPourcent += hungerSpeedIncrement;
	}


};

std::unique_ptr<Creature>  GameObjectBuilder::buildCreature(Simulation & simulation) {
	std::unique_ptr<Creature> creature = std::make_unique<Creature>(&simulation, 20);
	int x;
	int y;
	do {
		x = simulation.getValueRandom(0, MAP_SIZE - 1);
		y = simulation.getValueRandom(0, MAP_SIZE - 1);
	} while (simulation.map.gameObjectExistAt(Vector2D(x, y)));
	creature->setPosition(Vector2D(x, y));
	return creature;
}

std::unique_ptr<Food> GameObjectBuilder::buildFood(Simulation & simulation) {
	std::unique_ptr<Food> food = std::make_unique<Food>(&simulation);
	int x;
	int y;
	do {
		x = simulation.getValueRandom(0, MAP_SIZE - 1);
		y = simulation.getValueRandom(0, MAP_SIZE - 1);
	} while (simulation.map.gameObjectExistAt(Vector2D(x, y)));
	food->setPosition(Vector2D(x, y));
	return food;
}


void simulate() {
	Simulation simulation(445);
	simulation.init();
	simulation.start();

	std::cout << "Simulation ended" << std::endl;
}


int main()
{

	simulate();

	return 0;
}

