#include <SFML/Graphics.hpp>
#include <iostream>
#include "Car.h"
#include "Map.h"
#include "ParticleSystem.h"
#include <fstream>
int main()
{
	Map map("map");
	Car car1("car.png",map.GetPlayerStartPositions());
	sf::Clock clock;
	sf::Time elapsedTime;
	float time = 0;

	sf::RenderWindow window;
	window.create(sf::VideoMode(1024, 767), "Madness drivers!");//Menu
	ParticleSystem particles(1000);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				goto mainGame;
				//goto end;
			}
		}
		sf::Vector2i mouse = sf::Mouse::getPosition(window);
		particles.setEmitter(window.mapPixelToCoords(mouse));

		sf::Time elapsed = clock.restart();
		particles.update(elapsed);


		window.clear();
		window.draw(particles);
		window.display();
	}
	goto end;
	mainGame:
	window.create(sf::VideoMode(1024, 767), "Madness drivers!");
	while (window.isOpen())
	{
		//std::cout << "asd";
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		elapsedTime = clock.restart();
		time += elapsedTime.asSeconds();
		if (time > 0.5)
		{
			time -= 0.5;
			car1.setLocationByAdding_Subs(1, 2);

		}
		window.clear();
		map.draw(window);
		car1.draw(window);
		window.display();
	}
	end:
	return 0;
}