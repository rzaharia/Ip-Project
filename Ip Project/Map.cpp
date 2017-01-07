#include "Map.h"


Map::Map(std::string path)
{
	if (!texture.loadFromFile("textures/"+path+".png"))
		std::cout << "Eror loading map texture!";
	sprite.setTexture(texture);
	texture.setSmooth(true);
	playerCount = 0;
	Initialise(path);
}

void Map::Initialise(std::string path)
{
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
