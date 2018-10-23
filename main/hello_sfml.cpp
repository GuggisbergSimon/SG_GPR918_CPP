#include <SFML/Main.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

int main()
{
	sf::Clock clock;
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
	window.setFramerateLimit(30u);
	sf::Sprite spriteTest;
	sf::Sprite spriteTest2;
	sf::Texture textureTest;
	sf::Vector2f velocity = sf::Vector2f(100.0f, 100.0f);
	if(!textureTest.loadFromFile("data/other_play.png"))
	{
		return EXIT_FAILURE;
	}
	spriteTest.setTexture(textureTest);
	spriteTest2.setTexture(textureTest);
	spriteTest2.setPosition(100, 100);
    // run the program as long as the window is open
    while (window.isOpen())
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

		spriteTest2.setPosition(spriteTest2.getPosition() + velocity*dt.asSeconds());

		window.clear(sf::Color::Black);
		window.draw(spriteTest);
		window.draw(spriteTest2);
		window.display();
    }
    return EXIT_SUCCESS;
}