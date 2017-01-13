#pragma once
#ifndef LEVEL_H
#define LEVEL_H
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>
#include <fstream>
#include "Map.h"
#include "Car.h"
#include "Input.h"
class Level
{
	enum currenViewForDraw {
		gameView, scoreMenuView, tutorialView
	};
	currenViewForDraw currentView;
	bool adminOn = false;
	const float SCALE = 30.f;
	short int noOfLevels;
	short int currentLevel = -1;
	//short int noOfFinishLocations = 0;
	short int noOfTeleports;
	short int currentRectangle = 0;
	short int pointOfNoReturn = 0;
	short int noOfPoints = 0;//For taking back the player
	short int noOfObstacles = 0;
	sf::Vector2i pointOfReturn[10];
	Map::Rectangle newObstacles[20];
	Map::Rectangle finishLocations[10];
	bool IsInCurrentRectangle(sf::Vector2i carPosition);
	void Initialise();
	bool Collision(sf::Vector2i carPosition);
	/*void CreateBox(float x, float y,float width, float height);
	std::vector<b2BodyDef*> bodiesDef;
	std::vector<b2Body*> bodies;
	std::vector<b2PolygonShape*> polygonShapes;
	std::vector<b2FixtureDef*> fixtureDefs;
	std::vector<sf::Sprite*> theSPrites;*/
public:
	Input *game;
	short int index = 0;
	Map *currentMap = new Map();
	struct levelInfo {
		std::string levelName;
		short int levelType;
	}levels[10];
	Level();
	~Level();
	void LoadLevel();
	void UnloadLevel();
	void Draw(sf::RenderWindow &window);
	void TriggerEvent(Car *&car);
	void InitialiseCarLocation();
	void Update(float &scoreValue, float &timerTime);
};
#endif
