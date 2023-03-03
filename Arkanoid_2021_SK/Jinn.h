#pragma once
#include "Enemy.h"
class Jinn :
	public Enemy
{
public:
	Jinn(sf::Vector2f vector, sf::RenderWindow* var, int);
	virtual void addBullets(std::vector<Bullet*>& bullets);
};