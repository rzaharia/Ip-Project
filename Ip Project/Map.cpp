#include "Map.h"



Map::Map()
{
	if (!texture.loadFromFile("textures/map.png"))
		std::cout << "Eror loading map texture!";
	sprite.setTexture(texture);
	texture.setSmooth(true);
	playerCount = 0;
	Initialise();
}

void Map::Initialise()
{
	std::ifstream f("textures/map.txt");
	int n;
	for (int i = 0; i < 2; i++)
	{
		f >> finishLocation[i].x;
		f >> finishLocation[i].y;
	}
	f >> n;
	for (int i = 0; i < 2*n; i++)
	{
		f >> playerStartPosition[i].x;
		f >> playerStartPosition[i].y;
	}
}



Map::~Map()
{
}

void Map::draw(sf::RenderWindow &window)
{
	window.draw(sprite);
}

sf::Vector2f Map::GetPlaterStartPositions()
{
	return playerStartPosition[playerCount++];
}