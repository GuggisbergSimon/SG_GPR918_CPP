#include <thomas/ground.h>
#include <Box2D/Box2D.h>
#include "physics.h"

Ground::Ground(b2World & world, sf::Vector2f position, sf::Vector2f size)
{
	rect.setPosition(position);
	rect.setSize(size);
	rect.setOrigin(size / 2.0f);
	rect.setFillColor(sf::Color::Red);

	b2BodyDef bodyDef;
	bodyDef.position = pixel2meter(position);

	body = world.CreateBody(&bodyDef);
	b2FixtureDef fixtureDef;

	b2PolygonShape boxShape;
	boxShape.SetAsBox(pixel2meter(size.x / 2.0f), pixel2meter(size.y / 2.0f));
	fixtureDef.shape = &boxShape;
	fixture = body->CreateFixture(&fixtureDef);
}

void Ground::Draw(sf::RenderWindow & window)
{
	window.draw(rect);
}
