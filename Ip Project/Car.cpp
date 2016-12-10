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

void Car::setLocation(sf::Vector2f newLocation)
{
	sprite.setPosition(newLocation);
}

void Car::setLocationByAdding_Subs(int x,int y)//Add to the location the new one
{
	sf::Vector2f tempLocation = sprite.getPosition();
	tempLocation.x += x;
	tempLocation.y += y;
	sprite.setPosition(tempLocation);
}

sf::Vector2f Car::getCarLocation()
{
	return sprite.getPosition();
}
