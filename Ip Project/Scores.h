#pragma once
#ifndef SCORES_H
#define SCORES_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#define maxNrOfScores 10
class Scores
{
	enum ScoreMode {
		view, add
	};
	int minScore = 0, localScore = 0, localTIme = 0;
	sf::Color *textColor;
	sf::Font *font;
	sf::Texture *texture;
	sf::Sprite *sprite;
	sf::Text *textMenu;
	sf::Text *addText, *textAdded;
	std::vector<sf::Text*> allScores;
	ScoreMode scoreMode = ScoreMode::view;
	struct Player {
		std::string name;
		int time, score;
	};
	std::vector<Player*> players;
	void CreateNewText(int i, std::string username, int score, int time, int noOfPlayers);
	void Swap(Player *&player1, Player *&player2);
	void Swap(int x, int y);
	void Divide(int left, int right, int &m);
	void QuiqSort(int left,int right);
	void SaveToFile();
	void AddScore(std::string username, int score, int time);
public:
	Scores();
	~Scores();
	void Draw(sf::RenderWindow & window);
	void SetView(bool isView, int score, int time);
	bool GetView();
	void Keybord(int key);
};
#endif
