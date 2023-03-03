#pragma once
#include "Enemy.h"

int Enemy::number = 0;
int Enemy::level = 1;

template<typename T>
T random(T min, T max);

void Enemy::addToGame() {
	window->draw(sprite);
}

Enemy::Enemy(sf::Vector2f vector, sf::RenderWindow* var, int level) {

	speedY = 0;
	speedX = 0;
	setWindow(var);
	addToGame();
	HP = 100 * level;
	while (speedY == 0)
		speedY = random(-1, 1);
	while (speedX == 0)
		speedX = random(-1, 1);
}

void Enemy::move() {

	if (counter < numberOfTexture - 1) {
		counter++;
	}
	else
		counter = 0;
	sprite.setTexture(*texture[counter]);
	sf::Vector2f vector = sprite.getPosition();
	x = vector.x;
	y = vector.y;
	if (x <= 0 or x >= window->getSize().x - sprite.getTexture()->getSize().x * 2) {
		speedX = (-1) * speedX;

	}
	if (y >= window->getSize().y / 4 or y + speedY <= 0) {
		speedY = (-1) * speedY;

	}

	sprite.move(speedX, speedY);

	vector = sprite.getPosition();
	x = vector.x;
	y = vector.y;
}

Enemy::~Enemy() {
	number--;
}

void Enemy::nextLevel() {
	HP += 50;
}

void  Enemy::changeX() {
	speedX = speedX * -1;
}

void  Enemy::changeY() {
	speedY = speedY * -1;
}