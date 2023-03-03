#pragma once
#include "Menu.h"

Menu::Menu(float width, float height) {

	ptr_shop = new Shop(width, height);
	rank = new Ranking(width, height);
	if (!font.loadFromFile("Almendra-BoldItalic.otf"))
	{
		//handle error
	}

	sf::Text temp;

	temp.setFont(font);
	temp.setFillColor(sf::Color::Red);
	temp.setString("Graj");
	temp.setPosition(sf::Vector2f(width / 2, height / 5 * 1));
	menu.push_back(temp);

	temp.setFillColor(sf::Color::White);
	temp.setString("Sklep");
	temp.setPosition(sf::Vector2f(width / 2, height / 5 * 2));
	menu.push_back(temp);

	temp.setString("Ranking");
	temp.setPosition(sf::Vector2f(width / 2, height / 5 * 3));
	menu.push_back(temp);

	temp.setString("Wyjdz");
	temp.setPosition(sf::Vector2f(width / 2, height / 5 * 4));
	menu.push_back(temp);

	selectedItemIndex = 0;
}

Menu::~Menu() {
	delete ptr_shop;

}

void Menu::draw(sf::RenderWindow& window) {

	if (!shopOn and !rankOn) {
		ptr_shop->shop[ptr_shop->selectedItemIndex].setFillColor(sf::Color::White);
		ptr_shop->selectedItemIndex = 0;
		ptr_shop->shop[ptr_shop->selectedItemIndex].setFillColor(sf::Color::Red);
		for (int i = 0; i < menu.size(); i++) {
			window.draw(menu[i]);
		}
	}
	else if (shopOn)
	{
		for (int i = 0; i < ptr_shop->shop.size(); i++) {
			window.draw(ptr_shop->shop[i]);
		}
	}
	else if (rankOn) {
		for (int i = 0; i < rank->rankingText.size(); i++) {
			window.draw(rank->rankingText[i]);
		}
	}

}

void Menu::MoveUp() {
	if (selectedItemIndex - 1 >= 0 and !shopOn and !rankOn) {
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex--;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
	else if (shopOn) {
		ptr_shop->MoveUp();
	}
	else if (rankOn) {
		rank->MoveUp();
	}
}

void Menu::MoveDown() {
	if (selectedItemIndex + 1 < menu.size() and !shopOn and !rankOn) {
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex++;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
	else if (shopOn) {
		ptr_shop->MoveDown();
	}
	else if (rankOn) {
		rank->MoveDown();
	}
}