#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
class Map
{
public:
	Map();
	~Map();
	void draw(sf::RenderWindow &window);
	sf::Vector2f GetPlaterStartPositions();
private:
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2f playerStartPosition[6];
	sf::Vector2f finishLocation;
	short int playerCount;
};

