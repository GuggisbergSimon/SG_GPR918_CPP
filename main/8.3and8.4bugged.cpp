// CreatureSimulationBadCode.cpp : Defines the entry point for the console application.
//


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

class  GameObjectBuilder {
public:
	static std::shared_ptr<Creature> buildCreature(Simulation & simulation);
	static std::shared_ptr<Food> buildFood(Simulation & simulation);
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
	std::unique_ptr<Simulation> simulation;
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
			row.fill(nullptr);
		}

	}

	bool AddGameObjectAt(std::shared_ptr<GameObject> gameObject) {
		Vector2D position = gameObject->getPosition();
		return AddGameObjectAt(gameObject, position.x, position.y);
	}

	bool AddGameObjectAt(std::shared_ptr<GameObject> gameObject, int positionX, int positionY) {
		std::shared_ptr<GameObject> mapPosition = map[positionX][positionY];
		if (mapPosition == nullptr) {
			map[positionX][positionY] = gameObject;
			gameObjectsForUpdate.push_back(gameObject);
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
		std::shared_ptr<T> gameObject = std::dynamic_pointer_cast<T>(map[position.x][position.y]); //compiler error
		return gameObject != nullptr;
	}

	std::shared_ptr<Creature> GetCreatureAt(Vector2D position) {
		std::shared_ptr <Creature> creature = std::dynamic_pointer_cast<Creature>(map[position.x][position.y]);
		return creature;
	}

	bool gameObjectExistAt(Vector2D position) {
		return map[position.x][position.y] != nullptr;
	}

	bool RemoveObjectAt(Vector2D position) {
		if (map[position.x][position.y] != nullptr) {
			//////delete map[position.x][position.y]; //IDE error, because it's now an intelligent pointer, we should not touch it, I think
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
		map[positionX][positionY] = map[currentPosition.x][currentPosition.y];
		map[currentPosition.x][currentPosition.y] = nullptr;
		//map[positionX][positionY] = std::make_shared<GameObject>(gameObject); //compiler error normalement plus besoin de cette ligne
		gameObject.setPosition(Vector2D(positionX, positionY));

		return true;
	}

	void update() {
		for (auto & gameObject : gameObjectsForUpdate) {
			gameObject->update();

		}
		//Destroy element 
		//nani the fuck

		//Destroy map elements 
		for (auto & gameObject : gameObjectsForUpdate) {
			if (gameObject->isObjectDestroyed()) {
				RemoveObjectAt(gameObject->getPosition());
			}
		}
		//Destroy updates elements
		//if GameObject is a list
		//gameObjectsForUpdate.remove_if([](std::shared_ptr<GameObject> gameObject) {return gameObject->isObjectDestroyed();});
		//or a vector
		//gameObjectsForUpdate.erase(std::remove_if(gameObjectsForUpdate.begin(),gameObjectsForUpdate.end(),
		//	[](std::shared_ptr<GameObject> const& gameObject) {return gameObject->isObjectDestroyed();}),gameObjectsForUpdate.end());
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
	std::array<std::array<std::shared_ptr<GameObject>, MAP_SIZE>, MAP_SIZE> map;
	std::list<std::shared_ptr<GameObject>> gameObjectsForUpdate;




};

class Simulation {
public:

	Map map;



	Simulation(int seed) {
		random.seed(seed);
	}

	void init() {
		//Create 5 creatures
		for (int i = 0; i < 5; i++) {
			map.AddGameObjectAt(std::dynamic_pointer_cast<GameObject>(GameObjectBuilder::buildCreature(*this)));
		}


		//Create 6 foods
		for (int i = 0; i < 6; i++) {
			map.AddGameObjectAt(std::dynamic_pointer_cast<GameObject>(GameObjectBuilder::buildFood(*this)));
		}
		map.DisplayMap();
	}
	void start() {
		while (isEndSimulation()) {
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
		return (map.countCreaturesInMap() > 0);
	}


};

class Creature : public GameObject
{
public:

	Creature(Simulation * simulation, int hungerSpeedIncrement) :GameObject(simulation), hungerSpeedIncrement(hungerSpeedIncrement) {
		hungerPourcent = 0;
		isparent = false;
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

		//checks for nearby food and eats it
		Vector2D foodPosition = findnearbyFoodPosition();
		if (foodPosition.x >= 0) {

			GameObject & gameObject = simulation->map.getContentAtPosition(foodPosition);
			if (!gameObject.isObjectDestroyed()) {
				gameObject.destroy();
				hungerPourcent = 0;
			}
		}
		
		//add a newborn to the map where there is a place
		Vector2D creaturePosition = findnearbyCreaturePosition();
		if (creaturePosition.x >= 0 && !(creaturePosition.x == this->getPosition().x && creaturePosition.y == this->getPosition().y)) {
			std::shared_ptr<Creature> creature = simulation->map.GetCreatureAt(creaturePosition);
			if (!creature->isParent()) {
				simulation->map.AddGameObjectAt(std::dynamic_pointer_cast<GameObject>(GameObjectBuilder::buildCreature(*simulation)));
				isparent = true;
				creature->setParent();
			}
		}
		
		// I decided to increment its hunger at the end so that it still has a chance until the last second
		incrementHunger();
	}
	char getImage() {
		return 'C';
	}

	bool isParent() {
		return isparent;
	}

	void setParent() {
		isparent = true;
	}

private:

	int hungerPourcent;
	int hungerSpeedIncrement;
	std::list<std::shared_ptr<Creature>> friends;
	bool isparent;

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

std::shared_ptr<Creature> GameObjectBuilder::buildCreature(Simulation & simulation) {
	std::shared_ptr<Creature> creature(new Creature(&simulation, 20));
	int x;
	int y;
	do {
		x = simulation.getValueRandom(0, MAP_SIZE - 1);
		y = simulation.getValueRandom(0, MAP_SIZE - 1);
	} while (simulation.map.gameObjectExistAt(Vector2D(x,y)));
	creature->setPosition(Vector2D(x, y));
	return creature;
}

std::shared_ptr<Food> GameObjectBuilder::buildFood(Simulation & simulation) {
	std::shared_ptr<Food> food(new Food(&simulation));
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

