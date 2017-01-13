#include "Scores.h"



void Scores::CreateNewText(int i,std::string username, int score, int time,int noOfPlayers)
{
	sf::Text *newText = new sf::Text();
	if (score < minScore)
		minScore = score;
	newText->setFont((*font));
	newText->setColor((*textColor));
	newText->setCharacterSize(40);
	newText->setPosition(1067 / 2 - 340, 90 + 540 / noOfPlayers * (i + 1));
	newText->setString(username + " " + std::to_string(score) + " " + std::to_string(time));
	allScores.push_back(newText);
}

void Scores::Swap(Player *& player1, Player *& player2)
{
	Player *aux = player1;
	player1 = player2;
	player2 = aux;
}

void Scores::Swap(int x, int y)
{
	int aux = x;
	x = y;
	y = aux;
}

void Scores::Divide(int left, int right, int & m)
{
	int i = left, j = right, pi = 0, pj = 1;
	while (i < j)
	{
		if (players[i]->score < players[j]->score)
		{
			Swap(pi, pj);
			Swap(players[i], players[j]);
		}
		i += pi;
		j -= pj;
	}
	m = i;
}

void Scores::QuiqSort(int left, int right)
{
	if (left < right)
	{
		int m = 0;
		Divide(left, right, m);
		QuiqSort(left, m);
		QuiqSort(m + 1, right);
	}
}

void Scores::SaveToFile()
{
	std::ofstream g("textures/scores.txt");
	g << players.size()<<"\n";
	for (int i = 0; i < players.size(); i++)
		g << players[i]->name << " " << players[i]->score << " " << players[i]->time<<"\n";
	g.close();
}

Scores::Scores()
{
	texture = new sf::Texture();
	textColor = new sf::Color(254, 248, 0);
	font = new sf::Font();
	sprite = new sf::Sprite();
	textMenu = new sf::Text();
	texture->loadFromFile("textures/menu_background.png");
	sprite->setTexture((*texture));
	texture->setSmooth(true);
	font->loadFromFile("textures/font.ttf");
	textMenu->setFont((*font));
	textMenu->setColor((*textColor));
	textMenu->setString("Scoruri");
	textMenu->setCharacterSize(85);
	textMenu->setPosition(400, 20);
	addText = new sf::Text();
	textAdded = new sf::Text();
	addText->setFont((*font));
	addText->setColor((*textColor));
	addText->setString("Nume utilizator :");
	addText->setCharacterSize(40);
	addText->setPosition(200, 200);
	textAdded->setFont((*font));
	textAdded->setColor((*textColor));
	textAdded->setString("");
	textAdded->setCharacterSize(40);
	textAdded->setPosition(600, 200);
	std::ifstream f("textures/scores.txt");
	int temp;
	f >> temp;
	std::string playerName; int tempScore, tempTime;
	for (short int i = 0; i < temp; i++)
	{
		f >> playerName >> tempScore >> tempTime;
		Player *playerNew = new Player();
		sf::Text *newText = new sf::Text();
		if (tempScore < minScore)
			minScore = tempScore;
		playerNew->name = playerName;
		playerNew->score = tempScore;
		playerNew->time = tempTime;
		newText->setFont((*font));
		newText->setColor((*textColor));
		newText->setCharacterSize(40);
		newText->setPosition(1067 / 2 - 340, 90 + 540 / temp * (i + 1));
		newText->setString(playerName + " " + std::to_string(tempScore) + " " + std::to_string(tempTime));
		allScores.push_back(newText);
		players.push_back(playerNew);
	}
	f.close();
}


Scores::~Scores()
{
	delete(textColor);
	delete(font);
	delete(texture);
	delete(sprite);
	delete(textMenu);
	delete(textAdded);
	delete(textAdded);
	int temp = allScores.size();
	for (int i = temp - 1; i >= 0; i--)
	{
		delete(allScores[i]);
		delete(players[i]);
	}
}

void Scores::Draw(sf::RenderWindow & window)
{
	window.draw((*sprite));
	window.draw((*textMenu));
	if (scoreMode == ScoreMode::view)
	{
		int temp = allScores.size();
		for (int i = 0; i < temp; i++)
			window.draw((*allScores[i]));
	}
	else
	{
		window.draw((*addText));
		window.draw((*textAdded));
	}
}

void Scores::SetView(bool isView, int score, int time)
{
	if (isView == true)
		scoreMode = ScoreMode::view;
	else
	{
		scoreMode = ScoreMode::add;
		localScore = score;
		localTIme = time;
	}
}

bool Scores::GetView()
{
	return scoreMode == ScoreMode::view;
}

void Scores::Keybord(int key)
{
	std::string textString = textAdded->getString();
	if (key == 59)
	{
		if (textString.size() > 0)
			textString = textString.substr(0, textString.size() - 1);
		if (textString == "")
			textString = "-";
		textAdded->setString(textString);
	}
	else if (key == 58)
	{
		if (textString == "")
			textString = "-";
		AddScore(textAdded->getString(), localScore, localTIme);
		SetView(true,0,0);
	}
	else
	{
		std::string textString = textAdded->getString();
		if (textString.length() < 10)
		{
			textString += (char)(key + (int)'a');
			textAdded->setString(textString);
		}
	}
}

void Scores::AddScore(std::string username, int score, int time)
{
	if (score > minScore)
	{
		minScore = 150000;
		Player *newPlayer = new Player();
		newPlayer->name = username;
		newPlayer->score = score;
		newPlayer->time = time;
		players.push_back(newPlayer);
		int temp = allScores.size();
		for (int i = temp - 1; i >= 0; i--)
			delete(allScores[i]);
		allScores.clear();
		QuiqSort(0,players.size()-1);
		while(players.size() > maxNrOfScores)
		{
			Player *pl = players[players.size() - 1];
			delete(pl);
			players.erase(players.begin() + 10);
		}
		temp = players.size();
		for (int i = 0; i < temp; i++)
			CreateNewText(i, players[i]->name, players[i]->score, players[i]->time, temp);
		SaveToFile();
	}
}
