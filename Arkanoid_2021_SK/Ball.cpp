#pragma once
#include "Ball.h"
#include <random>

template<typename T>
T random(T min, T max);
int Ball::number = 0;

Ball::Ball(sf::Vector2f vector, sf::RenderWindow* var) {

	vector.x += 100;
	vector.y -= 100;
	texture.loadFromFile("images/ball.png");
	sprite.setTexture(texture);
	sprite.setPosition(vector);
	speedY = (-1) * abs(((double)(rand() % 10 + 10)));
	speedX = random(-5, 5);
	setWindow(var);
	drawBall = true;
	number++;
}

void Ball::addToGame() {
	window->draw(sprite);
}

void Ball::move() {
	sf::Vector2f vector = sprite.getPosition();
	x = vector.x;
	y = vector.y;
	if (x < 0 or x > window->getSize().x - sprite.getTexture()->getSize().x) {
		speedX = (-1) * speedX;

	}
	if (y + speedY <= 0) {
		speedY = (-1) * speedY;

	}
	if (y > window->getSize().y)
		drawBall = false;
	sprite.move(speedX, speedY);

	vector = sprite.getPosition();
	x = vector.x;
	y = vector.y;
}

bool Ball::isAlive() {
	return this->drawBall;
}

Ball::~Ball() {
	number--;
}