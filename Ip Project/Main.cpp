#include <SFML/Graphics.hpp>
#include <Box2D.h>
#include <iostream>
#include "box.h"
#include "Map.h"
#include "ParticleSystem.h"
#include "Menu.h"
#include "Run.h"
#include "user.h"
#include <fstream>
#include "Car.h"
#include "DestructionListener.h"
#include "Input.h"
const float SCALE = 30.f;
//#include "Get.cpp"
int main()
{
	Map map;
	map.Initialise("map");
	sf::Vector2f carStartLocation = map.GetPlayerStartPositions();
	Input *game;
	game = new Input();
	//To update the view of the car: game->Car->Update(controlState);
	game->car->SetTextures("textures/car.png", "textures/wheel.png");
	game->car->Initialise(map);
	Run().initialise(map);
	//box car1("car.png", map.GetPlayerStartPositions());
	Menu menu(true, "menu_background", "Madness drivers!", 1024, 600);
	sf::Clock clock;
	sf::Time elapsedTime;
	float time = 0;

	///Menu Window
	menu.start();
	sf::RenderWindow window;
	ParticleSystem particles(1000);
	while (menu.windowMenu.isOpen())
	{
		sf::Event event;
		sf::Vector2i mouse = sf::Mouse::getPosition(menu.windowMenu);
		while (menu.windowMenu.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				menu.windowMenu.close();
				goto end;
				//goto mainGame;
			}
			if (event.type == sf::Event::MouseButtonPressed)
			{
				//std::cout << menu.buttonPressed(mouse.x, mouse.y);
				short x = menu.buttonPressed(mouse.x, mouse.y);
				switch (x)
				{
				case 1: menu.windowMenu.close();
					goto mainGame;
					break;
				case 2:menu.initialiseOptionsMenu();
					break;
				case 3:menu.windowMenu.close();
					goto end;
					break;
				case 4: menu.initialiseOptionsMenu();
					break;
				case 5: menu.initialiseOptionsMenu();
					break;
				case 6: menu.initialiseTextObjects();
					break;
				default:
					break;
				}
			}
		}
		particles.setEmitter(menu.windowMenu.mapPixelToCoords(mouse));

		sf::Time elapsed = clock.restart();
		particles.update(elapsed);


		menu.windowMenu.clear();
		menu.draw();
		menu.windowMenu.draw(particles);
		menu.windowMenu.display();
	}

	///Game window
	goto end;
mainGame:
	window.create(sf::VideoMode(1024, 767), "Madness drivers!", sf::Style::Titlebar | sf::Style::Close);
	while (window.isOpen())
	{
		sf::Event event;
		//sf::Vector2i mouse = sf::Mouse::getPosition(window);
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::KeyPressed)
			{
				game->Keyboard((char)(event.key.code + (int)'a'));
			}
			else if (event.type == sf::Event::KeyReleased)
			{
				game->KeyboardUp((char)(event.key.code + (int)'a'));
			}
			else if (event.type == sf::Event::Closed)
				window.close();
			/*if (event.type == sf::Event::MouseButtonPressed)
			{
				std::cout << mouse.x << "," << mouse.y << "\n";
				std::cout << map.isIn(mouse.x, mouse.y)<<"\n";
			}*/
		}

		elapsedTime = clock.restart();
		time += elapsedTime.asSeconds();
		if (time > 0.5)
		{
			time -= 0.5;
			//car1.setLocationByAdding_Subs(1, 2);
		}
		game->World->Step(1 / 60.f, 8, 3);
		window.clear();

		map.draw(window);
		game->car->Draw(window);

		window.display();
	}
end:
	return 0;
}
