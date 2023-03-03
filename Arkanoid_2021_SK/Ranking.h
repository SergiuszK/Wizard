#pragma once
#include <map>
#include <string>
#include <fstream>
#include <regex>
#include <iostream>
#include "SFML/Graphics.hpp"

class Ranking {
private:
	sf::Font font;
	sf::Text text;
	std::vector<std::pair<int, std::string>> sorted;
	int max = 10; int current = 0;
	std::string path = "results.txt";
	std::vector<sf::Text> rankingText;
	void MoveUp();
	void MoveDown();
public:
	Ranking(float width, float height);
	void upload();
	void print();
	friend class Menu;
	int selectedItemIndex;
	void refresh(float width, float height);
	friend class Game;
};