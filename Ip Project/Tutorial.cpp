#include "Tutorial.h"



Tutorial::Tutorial(std::string fileName)
{
	backgroundImage = new sf::Sprite();
	imageTexture = new sf::Texture();
	imageTexture->loadFromFile("textures/" + fileName + "Tutorial.png");
	imageTexture->setSmooth(true);
	backgroundImage->setTexture((*imageTexture));
}


Tutorial::~Tutorial()
{
	delete(backgroundImage);
	delete(imageTexture);
}

void Tutorial::Draw(sf::RenderWindow & window)
{
	window.draw((*backgroundImage));
}
