#include "Map.h"


Map::Map()
{
}

void Map::Initialise(std::string path)
{
	if (!texture.loadFromFile("textures/" + path + ".png"))
		std::cout << "Eror loading map texture!";
	sprite.setTexture(texture);
	texture.setSmooth(true);
	playerCount = 0;
	data.numberOfRoads = 0;
	std::ifstream f("textures/"+path+".txt");
	int n, n1;
	for (int i = 0; i < 2; i++)
	{
		f >> finishLocation[i].x;
		f >> finishLocation[i].y;
	}
	f >> n;
	numberOfPlayers = n;
	for (int i = 0; i < n; i++)
	{
		f >> playerStartPosition[i].x;
		f >> playerStartPosition[i].y;
	}
	f >> n;
	data.numberOfRoads = n;
	for (int i = 0; i < n; i++)
	{
		f >> n1;
		data.numberOfPointPerRoad[i] = n1;
		for (int j = 0; j < n1; j++)
		{
			f >> data.roadPoints[i][j].x;
			f >> data.roadPoints[i][j].y;
		}
	}
	f >> n;
	data.numberOfRectangles = n;
	for (int i = 0; i < n; i++)
	{
		f >> data.rectangles[i].firstPoint.x;
		f >> data.rectangles[i].firstPoint.y;
		f >> data.rectangles[i].secondPoint.x;
		f >> data.rectangles[i].secondPoint.y;
	}/*
	std::cout << data.rectangles[0].firstPoint.x << " " << data.rectangles[0].firstPoint.y <<
		data.rectangles[0].secondPoint.x << " " << data.rectangles[0].secondPoint.y << "\n";
	std::cout << data.rectangles[1].firstPoint.x << " " << data.rectangles[1].firstPoint.y <<
		data.rectangles[1].secondPoint.x << " " << data.rectangles[1].secondPoint.y << "\n";
	data.rectangles[0] = data.rectangles[0] - data.rectangles[1];
	std::cout << data.rectangles[0].firstPoint.x << " " << data.rectangles[0].firstPoint.y <<
		data.rectangles[0].secondPoint.x << " " << data.rectangles[0].secondPoint.y << "\n";*/
}



Map::~Map()
{
}

void Map::draw(sf::RenderWindow &window)
{
	window.draw(sprite);
}

void Map::setNumberofPlayers(short int numberPlayers)
{
	numberOfPlayers = numberPlayers;
}

short int Map::getNumberOfPlayers()
{
	return numberOfPlayers;
}

sf::Vector2f Map::GetPlayerStartPositions()
{
	return playerStartPosition[playerCount++];
}

Map::mapData Map::GetBoundaryPoints()
{
	return data;
}

bool Map::isIn(sf::Vector2i pos)
{
	for (int i = 0; i < data.numberOfRectangles; i++)
		if (pos.x >= data.rectangles[i].firstPoint.x && pos.x <= data.rectangles[i].secondPoint.x && 
			pos.y >= data.rectangles[i].firstPoint.y && pos.y <= data.rectangles[i].secondPoint.y)
			return true;
	return false;
}
