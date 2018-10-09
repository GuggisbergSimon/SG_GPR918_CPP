#ifndef EX8_GAMEOBJECT
#define EX8_GAMEOBJECT

class Simulation;

#include "vector2d.h"

class GameObject
{
public:
	GameObject(Simulation* simulation, Vector2D position);
	GameObject(Simulation* simulation);
	virtual void update();
	virtual void start();
	virtual char getImage();
	Vector2D getPosition();
	void setPosition(Vector2D position);
	bool isObjectDestroyed();
	void destroy();

protected:
	Vector2D position;
	Simulation* simulation;
	bool isDestroyed;
};

#endif EX8_GAMEOBJECT
