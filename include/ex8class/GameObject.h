#ifndef EX8_GAMEOBJECT_H
#define EX8_GAMEOBJECT_H
#include <ex8class/Vector2d.h>
#include <memory>

class Simulation;

class GameObject {

public:
	GameObject(Simulation * simulation, Vector2D position);

	GameObject(Simulation * simulation);

	virtual void Update();

	virtual void Start();

	virtual char GetImage();

	Vector2D GetPosition();

	void SetPosition(Vector2D position);

	bool IsObjectDestroyed();

	void Destroy();


protected:
	Vector2D position;
	Simulation * simulation;
	bool isDestroyed;

};

class Food;
class Creature;

class  GameObjectBuilder {
public:
	static std::unique_ptr<Creature> BuildCreature(Simulation& simulation);
	static std::unique_ptr<Food> BuildFood(Simulation& simulation);
};

#endif