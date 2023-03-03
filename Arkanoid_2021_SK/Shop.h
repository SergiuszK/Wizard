#pragma once
#include "SFML/Graphics.hpp"

class Shop {
public:
	Shop(float width, float height);
	~Shop();
	void draw(sf::RenderWindow& window);
	void MoveUp();
	void MoveDown();
	bool game = false;
	bool turnOn() { return game; }
	void turnOnGame() { game = true; }
	void turnOfGame() { game = false; }
	int getPressedItem() { return selectedItemIndex; }
private:
	int selectedItemIndex;
	sf::Font font;
	std::vector<sf::Text> shop;
	friend class Menu;
};

