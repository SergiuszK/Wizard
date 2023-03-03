#pragma once
#include "SFML/Graphics.hpp"
#include "Shop.h"
#include "Ranking.h"

class Menu
{
public:
	Menu(float width_, float height_);
	~Menu();
	Shop* ptr_shop;
	Ranking* rank;
	void draw(sf::RenderWindow& window);
	void MoveUp();
	void MoveDown();
	bool game = false;
	bool shopOn = false, rankOn = false;
	bool isTurnOnGame() { return game; }
	void turnOnGame() { game = true; }
	void turnOfGame() { game = false; }
	int getPressedItem() { return selectedItemIndex; }
	void turnOnShop() { shopOn = true; }
	void turnOfShop() { shopOn = false; }
	void turnOnRank() { rankOn = true; }
	void turnOfRank() { rankOn = false; }

private:
	int selectedItemIndex;
	sf::Font font;
	std::vector<sf::Text> menu;
};