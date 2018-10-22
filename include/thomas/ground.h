#ifndef THOMAS_GROUND_H
#define THOMAS_GROUND_H
#include <SFML/Graphics/RectangleShape.hpp>
#include <Box2D/Dynamics/b2Body.h>
#include <SFML/Graphics/RenderWindow.hpp>

class Ground
{
public:
	Ground(b2World& world, sf::Vector2f position, sf::Vector2f size);

	void Draw(sf::RenderWindow& window);
private:
	sf::RectangleShape rect;
	b2Body* body;
	b2Fixture* fixture;
};

#endif