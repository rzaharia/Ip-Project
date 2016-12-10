#include <SFML/Graphics.hpp>
#include <iostream>
#include "UpdateManager.h"
#include "Car.h"
#include "Map.h"
#include <fstream>
int main()
{
	UpdateManager updateManager;
	Map map;
	Car car("car.png",map.GetPlaterStartPositions());
	sf::Clock clock;
	sf::Time elapsedTime;

	sf::RenderWindow window(sf::VideoMode(1024, 767), "IpProject!");

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
		map.draw(window);
		car.draw(window);
		window.display();
	}

	return 0;
}