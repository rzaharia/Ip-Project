#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
class Map
{
public:
	Map();
	~Map();
	void draw(sf::RenderWindow &window);
	sf::Vector2f GetPlaterStartPositions();
private:
	void Initialise();
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2f playerStartPosition[6];
	sf::Vector2f finishLocation[2];
	short int playerCount;
};

