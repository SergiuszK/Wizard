#include "RainbowBullet.h"

template<typename T>
T random(T min, T max);

RainbowBullet::RainbowBullet(sf::Vector2f vector, sf::RenderWindow* var) :Bullet(vector, var) {
	texture.loadFromFile("images/rainbow/bullet.png");
	sprite.setTexture(texture);
    Bullet::speedY = random(100, 200) / 20;
	Bullet::speedX = random(-5, 5);
	timer = time(0);
};

void RainbowBullet::move() {
	if (time(0) - timer > 0.2) {
		timer = time(0);
        Bullet::speedX = random(-5, 5);
	}

	Bullet::move();
}

void RainbowBullet::hit(Wizard* wizard) {
	wizard->reduct();
}