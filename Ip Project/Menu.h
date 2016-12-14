#include <SFML/Graphics.hpp>
#include <iostream>
#pragma once
class Menu
{
public:
	Menu(bool hasBackgroundImg,std::string background,std::string titleString, unsigned int width, unsigned int heigth);
	~Menu();
	void draw();
	void start();
	int buttonPressed(int x,int y);
	sf::RenderWindow windowMenu;
	void initialiseOptionsMenu();
	void initialiseTextObjects();
private:
	enum menuPage { principalPage, optionsPage };
	menuPage page;
	bool hasBackground;
	sf::Color textColor;
	sf::Font font;
	std::string title;
	sf::Texture texture;
	sf::Sprite sprite;
	sf::VideoMode videoMode;
	sf::Text textMenu;
	sf::Text buttons[3];
	bool soundsON, musicON;
};