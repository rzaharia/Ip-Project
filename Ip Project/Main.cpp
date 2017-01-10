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
	//SomeFunctions  someFunctions;
	//someFunctions.initialise(map);
	//currentMap = map;

	/*
	Car *car;
	b2Vec2 Gravity(0.f, 0.f);
	b2World *World = new b2World(Gravity);
	DestructionListener destructionListener;
	World->SetDestructionListener(&destructionListener);
	car = new Car(World);
	*/
	Input *game;
	game = new Input();
	//To update the view of the car: game->Car->Update(controlState);

	sf::Texture CarTexture;
	sf::Sprite Sprite;
	CarTexture.loadFromFile("textures/car.png");

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
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			game->Keyboard('w');
		else
			game->KeyboardUp('w');
		game->car->Update(game->controlState);
		sf::Event event;
		//sf::Vector2i mouse = sf::Mouse::getPosition(window);
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
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
		for (b2Body* BodyIterator = game->World->GetBodyList(); BodyIterator != 0; BodyIterator = BodyIterator->GetNext())
		{
			if (BodyIterator->GetType() == b2_dynamicBody)
			{
				Sprite.setTexture(CarTexture);
				Sprite.setOrigin(SCALE * BodyIterator->GetPosition().x, SCALE * BodyIterator->GetPosition().y);
				Sprite.setPosition(SCALE * BodyIterator->GetPosition().x, SCALE * BodyIterator->GetPosition().y);
				Sprite.setRotation(BodyIterator->GetAngle() * 180 / b2_pi);
				window.draw(Sprite);
			}
		}
		//car1.draw(window);
		window.display();
	}
end:
	return 0;
}
