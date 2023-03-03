#include "JinnBullet.h"

template<typename T>
T random(T min, T max);

JinnBullet::JinnBullet(sf::Vector2f vector, sf::RenderWindow* var) :Bullet(vector, var) {
	texture.loadFromFile("images/jinn/bullet.png");
	sprite.setTexture(texture);
	Bullet::speedY = random(1, 3);
	Bullet::speedX = random(-1, 1);

};

void JinnBullet::hit(Wizard* wizard) {
	wizard->slow();
}