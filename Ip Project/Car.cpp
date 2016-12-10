#include "Car.h"

Car::Car(std::string texturePath,sf::Vector2f startPosition)
{
	if (!texture.loadFromFile("textures/"+texturePath))
		std::cout << "Eror loading car texture!";
	sprite.setTexture(texture);
	sprite.setPosition(startPosition);
	texture.setSmooth(true);
}


Car::~Car()
{
}

void Car::draw(sf::RenderWindow & window)
{
	window.draw(sprite);
}
