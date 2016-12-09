#include <SFML/Graphics.hpp>
#include <iostream>
#include "UpdateManager.h"

int main()
{
	UpdateManager updateManager;
	sf::Clock clock;
	sf::Time elapsedTime;

	sf::RenderWindow window(sf::VideoMode(500, 500), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		elapsedTime = clock.restart();
		updateManager.TimeManagement(elapsedTime.asSeconds());

		window.clear();
		window.draw(shape);
		window.display();
	}

	return 0;
}