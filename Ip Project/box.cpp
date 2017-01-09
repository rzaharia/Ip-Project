#include "box.h"

box::box(std::string texturePath, sf::Vector2f startPosition)
{
	if (!texture.loadFromFile("textures/" + texturePath))
		std::cout << "Eror loading car texture!";
	sprite.setTexture(texture);
	sprite.setPosition(startPosition);
	texture.setSmooth(true);
}


box::~box(){
}

void box::draw(sf::RenderWindow & window){
	window.draw(sprite);
}

void box::setLocation(sf::Vector2f newLocation){
	sprite.setPosition(newLocation);
}

void box::setLocationByAdding_Subs(int x, int y){
	sf::Vector2f tempLocation = sprite.getPosition();
	tempLocation.x += x;
	tempLocation.y += y;
	sprite.setPosition(tempLocation);
}

sf::Vector2f box::getboxLocation(){
	return sprite.getPosition();
}