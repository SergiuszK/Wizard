#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Object {
protected:
	sf::Texture texture;
	sf::Sprite sprite;
	virtual void addToGame() = 0;
	sf::RenderWindow* window;
	virtual void move() = 0;
	double speedY;
	double speedX;
	float x, y;
	virtual void setWindow(sf::RenderWindow* var);
	friend bool collision(Object* v1, Object* v2);
	int HP = 100;
	void hit(int demage = 25) { HP -= demage; }
	int demage = 25;
};