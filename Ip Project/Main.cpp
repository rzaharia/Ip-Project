#include <SFML/Graphics.hpp>
#include <Box2D.h>
#include <iostream>
#include "box.h"
#include "Map.h"
#include "ParticleSystem.h"
#include "Menu.h"
#include <fstream>
#include "Car.h"
#include "DestructionListener.h"
#include "Input.h"
#include "Level.h"
const float SCALE = 30.f;
#define INITIAL_SCORE 12000.f
//#include "Get.cpp"
int main()
{
	Level *levelsManager = new Level;
	levelsManager->LoadLevel();

	sf::Text scoreText;
	sf::Text timeText;
	sf::Font font;
	font.loadFromFile("textures/font.ttf");
	timeText.setFont(font);
	timeText.setColor(sf::Color::Red);
	timeText.setCharacterSize(15);
	timeText.setPosition(levelsManager->currentMap->finishLocation[1]);
	scoreText.setFont(font);
	scoreText.setColor(sf::Color::Red);
	scoreText.setCharacterSize(19);
	scoreText.setPosition(levelsManager->currentMap->finishLocation[0]);

	//sf::Vector2f playerStartPositions = levelsManager->currentMap->GetPlayerStartPositions();
	//game->car->SetTransform(playerStartPositions.x/SCALE, playerStartPositions.y/SCALE);
	float time = 0, timerTime = 0, scoreValue = INITIAL_SCORE;
	levelsManager->InitialiseCarLocation();

	Menu menu(true, "menu_background", "Madness drivers!", 1024, 600);
	sf::Clock clock;
	sf::Time elapsedTime;

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
	window.setFramerateLimit(60);
	while (window.isOpen())
	{
		sf::Event event;
		//sf::Vector2i mouse = sf::Mouse::getPosition(window);
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::KeyPressed)
			{
				levelsManager->game->Keyboard((char)(event.key.code + (int)'a'));
				if(event.key.code==sf::Keyboard::Space)
					levelsManager->TriggerEvent(levelsManager->game->car);
			}
			else if (event.type == sf::Event::KeyReleased)
			{
				levelsManager->game->KeyboardUp((char)(event.key.code + (int)'a'));
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
		timerTime += elapsedTime.asSeconds();
		time += elapsedTime.asSeconds();
		timeText.setString(std::to_string(((int)timerTime * 100) / 100));
		scoreText.setString(std::to_string(((int)scoreValue*100)/100));
		if (time > 0.5)
		{
			time -= 0.5;
			scoreValue -= 3;
		}
		levelsManager->game->World->Step(1 / 60.f, 8, 3);
		window.clear();

		levelsManager->Draw(window);
		levelsManager->game->car->Draw(window);
		levelsManager->Update(scoreValue, timerTime);
		window.draw(timeText);
		window.draw(scoreText);
		window.display();
	}
end:
	return 0;
}
