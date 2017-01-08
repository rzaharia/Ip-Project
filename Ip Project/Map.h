#pragma once
#ifndef Map_H
#define Map_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
class Map
{
public:
	Map();
	~Map();
	struct Rectangle
	{
		sf::Vector2i firstPoint, secondPoint;
		Rectangle operator -(const Rectangle& newRectangle)
		{
			Rectangle r;
			r.firstPoint = firstPoint - newRectangle.firstPoint;
			r.secondPoint = secondPoint - newRectangle.secondPoint;
			return r;
		}
	};
	struct mapData
	{
		short int numberOfRoads;
		short int numberOfPointPerRoad[10];
		sf::Vector2f roadPoints[10][100];
		short int numberOfRectangles;
		Rectangle rectangles[100];

	};
	void draw(sf::RenderWindow &window);
	void setNumberofPlayers(short int numberOfPlayers);
	short int getNumberOfPlayers();
	sf::Vector2f GetPlayerStartPositions();
	mapData GetBoundaryPoints();
	sf::Vector2f finishLocation[2];
	bool isIn(sf::Vector2f pos);
	void Initialise(std::string path);
	
private:
	short int playerCount;//Used by get location
	short int numberOfPlayers;
	mapData data;//Information about road limiters(points)
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2f playerStartPosition[10];
};
#endif
