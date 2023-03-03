#include "SpiderWeb.h"

template<typename T>
T random(T min, T max);

SpiderWeb::SpiderWeb(sf::Vector2f vector, sf::RenderWindow* var) :Bullet(vector, var) {
	texture.loadFromFile("images/spider/bullet.png");
	sprite.setTexture(texture);

	speedY = random(5, 10);
	speedX = random(-1, 1);

};

void SpiderWeb::hit(Wizard* wizard) {
	wizard->stop();
}