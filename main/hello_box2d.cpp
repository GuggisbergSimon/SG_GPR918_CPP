#include <Box2D/Box2D.h>
#include <iostream>


void WorldStep(b2World* world, b2Body* body)
{

	world->Step(0.02f, 10, 10);
	std::cout << "Body position: " << body->GetPosition().x << ", " << body->GetPosition().y << "\n";

}

int main()
{
	b2World world(b2Vec2(0.0f,9.81f));
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.fixedRotation = false;
	bodyDef.linearVelocity.Set(100.0f, 0.0f);
	auto* body = world.CreateBody(&bodyDef);

	for(int i = 0; i<100;i++)
	{
		WorldStep(&world, body);
	}

	return EXIT_SUCCESS;
}