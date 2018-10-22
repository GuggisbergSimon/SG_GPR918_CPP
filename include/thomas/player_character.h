#ifndef THOMAS_PLAYER_H
#define THOMAS_PLAYER_H

#include <SFML/Graphics/CircleShape.hpp>
#include <Box2D/Dynamics/b2World.h>
#include "SFML/Graphics/RenderWindow.hpp"

class PlayerCharacter
{
public:
	PlayerCharacter(b2World& world, sf::Vector2f position, float radius);

	void ManageInput();
	void Update(float dt);
	void Draw(sf::RenderWindow& window);

	sf::Vector2f GetPosition();
	void SetPosition(sf::Vector2f v);
	void SetOnGround(bool contact);
private:
	sf::CircleShape circleShape;
	b2Body* body;
	b2Fixture* fixture;
	sf::Vector2f position;

	const float playerSpeed = 500.0f;
	bool wasJumpKeyPressed = false;
	bool isOnGround = false;
};


#endif
