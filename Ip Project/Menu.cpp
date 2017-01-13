#include "Menu.h"
Menu::Menu(bool hasBackgroundImg,std::string background, std::string titleString,unsigned int width, unsigned int heigth)
{
	page = menuPage::principalPage;
	soundsON = musicON = true;
	hasBackground = hasBackgroundImg;
	title=titleString;
	if (hasBackground == true)
	{
		if (!texture.loadFromFile("textures/" + background + ".png"))
			std::cout << "Eror loading map texture!";
		sprite.setTexture(texture);
		texture.setSmooth(true);
	}
	videoMode = sf::VideoMode(width, heigth);
	initialiseTextObjects();
}

Menu::~Menu()
{
}

void Menu::draw()
{
	if(hasBackground==true)
		windowMenu.draw(sprite);
	windowMenu.draw(textMenu);
	for (int i = 0; i < 3; i++)
		windowMenu.draw(buttons[i]);
}

void Menu::start()
{
	windowMenu.create(videoMode, title);
}

int Menu::buttonPressed(int x,int y)//Event for mouse click
{
	sf::Vector2i coord[6];
	coord[0].x = 285; coord[0].y = 180;
	coord[1].x = 798; coord[1].y = 227;
	coord[2].x = 354; coord[2].y = 302;
	coord[3].x = 611; coord[3].y = 347;
	coord[4].x = 343; coord[4].y = 421;
	coord[5].x = 670; coord[5].y = 468;
	for (int i = 0; i < 3; i++)
		if (x >= coord[2 * i].x && x <= coord[2 * i + 1].x && y >= coord[2 * i].y && y <= coord[2 * i + 1].y)
		{///To be modified later
			int x = i + 1 + (page == menuPage::optionsPage) * 3;
			if (x == 4)
			{
				soundsON = !soundsON;
			}
			if (x == 5)
			{
				if (musicON == true)
					music->stop();
				else {
					music->openFromFile("textures/End_of_all_hope_Nightwish.ogg");
					music->play();
				}
				musicON = !musicON;
			}
			return x;
		}
	return 0;
}

void Menu::initialiseTextObjects()
{
	if (page == menuPage::principalPage)
	{
		textColor = sf::Color(254, 248, 0);
		font.loadFromFile("textures/font.ttf");
		textMenu.setFont(font);
		textMenu.setColor(textColor);
		textMenu.setString(title);
		textMenu.setCharacterSize(85);
		textMenu.setPosition(120, 20);
	}
	for (int i = 0; i < 3; i++)
	{
		if (page == menuPage::principalPage)
		{
			buttons[i].setFont(font);
			buttons[i].setColor(textColor);
			buttons[i].setCharacterSize(60);
		}
		switch (i)
		{
		case 0: buttons[i].setString("Start the game");
				if (page == menuPage::principalPage)
					buttons[i].setPosition(videoMode.width / 2 - 230, 45 + 120 * (i + 1));
			break;
		case 1: buttons[i].setString("Options"); 
				buttons[i].setPosition(videoMode.width / 2 - 160, 45 + 120 * (i + 1));
			break;
		case 2: buttons[i].setString("Quit game"); 
				if (page == menuPage::principalPage)
					buttons[i].setPosition(videoMode.width / 2 - 170, 45 + 120 * (i + 1));
			break;
		default:
			break;
		}
		
	}
	page = menuPage::principalPage;
}

bool Menu::isSoundEnabled()
{
	return soundsON;
}

void Menu::initialiseOptionsMenu()
{
	page = menuPage::optionsPage;
	for (int i = 0; i < 3; i++)
	{
		switch (i)
		{
		case 0: buttons[i].setString(soundsON?"Stop sounds":"Start sounds");
			break;
		case 1: buttons[i].setString(musicON?"Stop music":"Start music");
			buttons[i].setPosition(videoMode.width / 2 - 210, 45 + 120 * (i + 1));
			break;
		case 2: buttons[i].setString("Go back");
			break;
		default:
			break;
		}

	}
}
