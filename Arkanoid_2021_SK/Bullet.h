#pragma once
#include "Object.h"
#include "Wizard.h"

class Bullet : public Object
{
protected:
	sf::Sprite getSprite() { return sprite; }
	virtual void addToGame();
	virtual void move();
	bool draw = true;
	bool isAlive();
	virtual void hit(Wizard* wizard) = 0;
	std::string name;
public:
	Bullet(sf::Vector2f vector, sf::RenderWindow* var);
	friend class Game;
	friend bool collision(Object* v1, Object* v2);
};