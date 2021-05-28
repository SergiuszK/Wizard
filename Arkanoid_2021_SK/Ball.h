#pragma once
#include "Object.h"


class Ball :public Object {
protected:
	sf::Sprite getSprite() { return sprite; }
	virtual void addToGame();
	virtual void move();
	time_t timer = time(0);
public:
	static int number;
	void changeY() {   if (time(0) - timer > 0.01) time_t timer = time(0);speedY *= -1;}
	Ball(sf::Vector2f vector, sf::RenderWindow* var);
	friend class Game;
	bool isAlive();
	bool drawBall = true;
	friend bool collision(Object* v1, Object* v2);
	~Ball();
	
};

