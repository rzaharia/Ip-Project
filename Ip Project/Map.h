#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
class Map
{
public:
	Map(std::string path);
	~Map();
	struct mapData
	{
		short int numberOfRoads;
		short int numberOfPointPerRoad[10];
		sf::Vector2f roadPoints[10][100];
	};
	void draw(sf::RenderWindow &window);
	void setNumberofPlayers(short int numberOfPlayers);
	short int getNumberOfPlayers();
	sf::Vector2f GetPlayerStartPositions();
	mapData GetBoundaryPoints();
	sf::Vector2f finishLocation[2];
	
private:
	void Initialise(std::string path);
	short int playerCount;//Used by get location
	short int numberOfPlayers;
	mapData data;//Information about road limiters(points)
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2f playerStartPosition[10];
};

