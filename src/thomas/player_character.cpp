#include <thomas/player_character.h>
#include <Box2D/Box2D.h>
#include "physics.h"
#include "SFML/Window/Keyboard.hpp"

PlayerCharacter::PlayerCharacter(b2World & world, sf::Vector2f position, float radius):
position(position)
{
	circleShape.setPosition(position);
	circleShape.setRadius(radius);
	circleShape.setOrigin(radius, radius);
	circleShape.setFillColor(sf::Color::Green);

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.fixedRotation = true;
	bodyDef.position = pixel2meter(position);
	bodyDef.userData = this;

	body = world.CreateBody(&bodyDef);

	b2FixtureDef fixtureDef;
	b2CircleShape b2Circle;
	fixtureDef.friction = 0.0f;
	b2Circle.m_radius = pixel2meter(radius);
	
	fixtureDef.shape = &b2Circle;

	b2FixtureDef footDef;
	b2PolygonShape boxShape;
	boxShape.SetAsBox(pixel2meter(5.0f), pixel2meter(5.0f), b2Vec2(0.0f, pixel2meter(radius)), 0.0f);
	footDef.shape = &boxShape;
	footDef.isSensor = true;
	footDef.userData = this;
	body->CreateFixture(&footDef);
	fixture = body->CreateFixture(&fixtureDef);
}

void PlayerCharacter::ManageInput()
{
	float horizontalInput = 0.0f;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
	{
		horizontalInput = -1.0f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
	{
		horizontalInput = 1.0f;
	}

	float verticalJump = body->GetLinearVelocity().y;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && !wasJumpKeyPressed && isOnGround)
	{
		//Jump
		verticalJump = -5.0f;
	}
	body->SetLinearVelocity(b2Vec2(pixel2meter(playerSpeed)*horizontalInput, verticalJump));

	wasJumpKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up);
}

void PlayerCharacter::Update(float dt)
{
	//Update circle position with body
	position = meter2pixel(body->GetPosition());
	circleShape.setPosition(position);
}

void PlayerCharacter::Draw(sf::RenderWindow & window)
{
	window.draw(circleShape);
}

sf::Vector2f PlayerCharacter::GetPosition()
{
	return position;
}

void PlayerCharacter::SetPosition(sf::Vector2f v)
{
	position = v;
}

void PlayerCharacter::SetOnGround(bool contact)
{
	isOnGround = contact;
}
