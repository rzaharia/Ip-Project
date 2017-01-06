#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
class box
{
public:
	box(std::string texturePath, sf::Vector2f startPosition);
	~box();
	void draw(sf::RenderWindow &window);
	void setLocation(sf::Vector2f newLocation);
	void setLocationByAdding_Subs(int x, int y);
	sf::Vector2f getboxLocation();
private:
	sf::Texture texture;
	sf::Sprite sprite;
	int lives;
};
