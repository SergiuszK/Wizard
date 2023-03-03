#pragma once
#include "Bullet.h"

class RainbowBullet :
	public Bullet {
private:
	time_t timer;
	double speedX;
	virtual void hit(Wizard* wizard);
public:

	RainbowBullet(sf::Vector2f vector, sf::RenderWindow* var);
	virtual void move();
};

