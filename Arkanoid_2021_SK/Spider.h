#pragma once
#include "Enemy.h"
#include "SpiderWeb.h"


class Spider : public Enemy {
public:
	Spider(sf::Vector2f vector, sf::RenderWindow* var, int);
	virtual void addBullets(std::vector<Bullet*>& bullets);
};

