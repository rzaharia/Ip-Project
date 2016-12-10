#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
class Car
{
public:
	Car(std::string texturePath,sf::Vector2f startPosition);
	~Car();
	void draw(sf::RenderWindow &window);
	void setLocation(sf::Vector2f newLocation);
	void setLocationByAdding_Subs(int x,int y);//Add to the location the new one
	sf::Vector2f getCarLocation();
private:
	sf::Texture texture;
	sf::Sprite sprite;
	int lives;// etc....
};

