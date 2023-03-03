#pragma once
#include "Enemy.h"

class Rainbow :
	public Enemy {
public:
	Rainbow(sf::Vector2f vector, sf::RenderWindow* var, int);
	void addBullets(std::vector<Bullet*>& bullets);
};