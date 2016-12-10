#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
class Car
{
public:
	Car(std::string texturePath,sf::Vector2f startPosition);
	~Car();
	void draw(sf::RenderWindow &window);
private:
	sf::Texture texture;
	sf::Sprite sprite;
	int lives;// etc....
};

