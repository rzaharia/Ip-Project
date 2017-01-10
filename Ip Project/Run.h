#pragma once
#ifndef Run_H
#define Run_H
#include <SFML/Graphics.hpp>
#include<cmath>
#include<cstdlib>
#include<ctime>
#include "Map.h"
class Run
{
public:
	
	Run();
	~Run();
	//Run(const Run&) = default;
	//Run& operator=(const Run&) = default;
	void initialise(Map theMap);
	bool haveAttempts();
	sf::Vector2f translate(sf::Vector2f p, double angle, double distance);
	double min(double x, double y);
	double Get(sf::Vector2f pos, double angle);
	sf::Vector2f Start();
	double dist(sf::Vector2f a, sf::Vector2f b);
	bool onSegment(sf::Vector2f a, sf::Vector2f c, sf::Vector2f b);
	double crossProduct(sf::Vector2f a, sf::Vector2f c, sf::Vector2f b);
	bool intersects(sf::Vector2f a, sf::Vector2f b, sf::Vector2f c, sf::Vector2f d);
	bool Move(sf::Vector2f myPos, sf::Vector2f newPos);
	void doMove(sf::Vector2f, sf::Vector2f);
private:
	Map currentMap;
	long double pi = acos(-1);
	double eps = 0.000000001;
	int numberOfTries, maximumNumberOfTries = 500;
};

#endif // !Run.h
