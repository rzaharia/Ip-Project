#pragma once
#ifndef TUTORIAL_H
#define TUTORIAL_H
#include <SFML/Graphics.hpp>
class Tutorial
{
	sf::Sprite *backgroundImage;
	sf::Texture *imageTexture;
public:
	Tutorial(std::string fileName);
	~Tutorial();
	void Draw(sf::RenderWindow & window);
};
#endif // !TUTORIAL_H
