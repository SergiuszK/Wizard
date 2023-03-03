#pragma once
#include "Ball.h"

class Coin :
	public Ball
{
public:
	std::vector<sf::Texture*> texture;
	int numberOfTexture = 6;
	Coin(sf::Vector2f vector, sf::RenderWindow* var);
	friend class Game;
	friend bool collision(Object* v1, Object* v2);
	virtual void move();
	int counter = 0;
};

