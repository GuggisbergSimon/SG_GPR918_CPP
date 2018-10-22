#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <thomas/player_character.h>
#include "thomas/ground.h"
#include <vector>

class ThomasContactListener : public b2ContactListener
{
public:
	void BeginContact(b2Contact* contact) override
	{
		auto* userDataA = contact->GetFixtureA()->GetUserData();
		auto* userDataB = contact->GetFixtureB()->GetUserData();
		PlayerCharacter* pCharPtr = nullptr;
		if(userDataA)
		{
			pCharPtr = static_cast<PlayerCharacter*>(userDataA);
		}
		if (userDataB)
		{
			pCharPtr = static_cast<PlayerCharacter*>(userDataB);
		}
		if(pCharPtr)
		{
			pCharPtr->SetOnGround(true);
		}
	}
	void EndContact(b2Contact* contact) override
	{
		auto* userDataA = contact->GetFixtureA()->GetUserData();
		auto* userDataB = contact->GetFixtureB()->GetUserData();
		PlayerCharacter* pCharPtr = nullptr;
		if (userDataA)
		{
			pCharPtr = static_cast<PlayerCharacter*>(userDataA);
		}
		if (userDataB)
		{
			pCharPtr = static_cast<PlayerCharacter*>(userDataB);
		}
		if (pCharPtr)
		{
			pCharPtr->SetOnGround(false);
		}
	}
};

int main()
{
	b2World world(b2Vec2(0.0f, 9.81f));
	ThomasContactListener contactListener;
	world.SetContactListener(&contactListener);

	PlayerCharacter pChar(world,sf::Vector2f(400.0f, 300.0f), 50.0f);
	auto grounds = std::vector<Ground>{
		{world, sf::Vector2f(400.0f, 500.0f), sf::Vector2f(800.0f, 100.0f)},
		{world, sf::Vector2f(800.0f, 300.0f), sf::Vector2f(600.0f, 100.0f)} 
	};

	sf::RenderWindow window(sf::VideoMode(800.0f,600.0f), "Thomas was round");
	sf::Clock clock;
	
	while(window.isOpen())
	{
		sf::Time dt = clock.restart();
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event{};
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();
		}
		
		pChar.ManageInput();
		world.Step(dt.asSeconds(), 10, 10);
		//Update of PlayerCharacter and Grounds
		pChar.Update(dt.asSeconds());

		window.clear(sf::Color::Black);
		//Draw PlayerCharacter and Grounds
		for(auto& g : grounds)
		{
			g.Draw(window);
		}
		pChar.Draw(window);
		window.display();
	}
}
