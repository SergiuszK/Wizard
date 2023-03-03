#pragma once
#include "Shop.h"

Shop::Shop(float width, float height) {
	if (!font.loadFromFile("Almendra-BoldItalic.otf"))
	{
		//handle error
	}

	sf::Text temp;

	temp.setFont(font);
	temp.setFillColor(sf::Color::Red);
	temp.setString("Predkosc - 5 Gold");
	temp.setPosition(sf::Vector2f(width / 2, height / 5 * 1));
	shop.push_back(temp);

	temp.setFillColor(sf::Color::White);
	temp.setString("Zycie - 20 Gold");
	temp.setPosition(sf::Vector2f(width / 2, height / 5 * 2));
	shop.push_back(temp);



	temp.setString("Wieksze obrazenia - 20 Gold");
	temp.setPosition(sf::Vector2f(width / 2, height / 5 * 3));
	shop.push_back(temp);


	temp.setString("Wyjdz");
	temp.setPosition(sf::Vector2f(width / 2, height / 5 * 4));
	shop.push_back(temp);

	selectedItemIndex = 0;
}

Shop::~Shop() {

}

void Shop::draw(sf::RenderWindow& window) {
	for (int i = 0; i < shop.size(); i++) {
		window.draw(shop[i]);
	}
}

void Shop::MoveUp() {
	if (selectedItemIndex - 1 >= 0) {
		shop[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex--;
		shop[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

void Shop::MoveDown() {
	if (selectedItemIndex + 1 < shop.size()) {
		shop[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex++;
		shop[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}