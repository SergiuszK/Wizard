#pragma once
#include "Bullet.h"

class SpiderWeb : public Bullet {
private:
	virtual void hit(Wizard* wizard);
public:
	SpiderWeb(sf::Vector2f vector, sf::RenderWindow* var);

};

