#include "Map.h"



Map::Map()
{
	if (!texture.loadFromFile("textures/map.png"))
		std::cout << "Eror loading map texture!";
	sprite.setTexture(texture);
	texture.setSmooth(true);
	playerCount = 0;
	playerStartPosition[0].x = 470;
	playerStartPosition[0].y = 75;
	
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
