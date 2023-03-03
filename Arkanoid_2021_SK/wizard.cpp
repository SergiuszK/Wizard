#pragma once
#include "Wizard.h"

Wizard::Wizard(double speedX_, double speedY_, sf::RenderWindow* var) {
	texture[0].loadFromFile("images/wizard/3_RUN_000.png");
	texture[1].loadFromFile("images/wizard/3_RUN_001.png");
	texture[2].loadFromFile("images/wizard/3_RUN_002.png");
	texture[3].loadFromFile("images/wizard/3_RUN_003.png");
	texture[4].loadFromFile("images/wizard/3_RUN_004.png");
	texture[5].loadFromFile("images/wizard/stun.png");
	sprite.setTexture(texture[0]);
	speedX = speedX_;
	speedY = speedY_;
	setWindow(var);
	defaultPosition.x = (window->getSize().x / 2);
	defaultPosition.y = (window->getSize().y - sprite.getTexture()->getSize().y * 0.90);
	sprite.setPosition(defaultPosition);
	hpBar.setFillColor(sf::Color(255, 0, 0, 128));
	hpBar.setPosition(window->getSize().x * 0.01, window->getSize().x * 0.01);
	HP = 100;
	demage = 100;
}

void Wizard::addToGame() {
	if (HP == 0) {

		texture_die.loadFromFile("images/wizard/7_DIE_008.png");
		sprite.setTexture(texture_die);
	}
	hpBar.setSize(sf::Vector2f(HP * 4, window->getSize().y * 0.05));
	window->draw(sprite);
	window->draw(hpBar);
	if (time(0) - timerStun > 4) {
		stopped = false;
	}
}

void Wizard::move() {
	if (reducted) {
		unReduct();
	}

	if (slowed) {
		unSlow();
	}

	sf::Vector2f vector = sprite.getPosition();
	x = vector.x;
	y = vector.y;

	if (HP > 0 and !stopped) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			if (counter < 4) {
				counter++;
			}
			else
				counter = 0;
			sprite.setTexture(texture[counter]);

			if (x - speedX > 0) {
				sprite.move(-speedX, 0);

			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			if (counter < 4) {
				counter++;
			}
			else
				counter = 0;
			sprite.setTexture(texture[counter]);

			if (x + speedX < window->getSize().x - sprite.getTexture()->getSize().x) {
				sprite.move(speedX, 0);

			}

		}
	}
	vector = sprite.getPosition();
	x = vector.x;
	y = vector.y;

}

Wizard::~Wizard() {

}

void Wizard::reduct() {

	timerReduct = time(0);

	if (!reducted) {
		reducted = true;
		sprite.setScale(0.5, 0.5);
		speedX /= 10;
		sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y + sprite.getTexture()->getSize().y / 2);
	}
}


void Wizard::unReduct() {
	if (reducted and time(0) - timerReduct > 3) {
		reducted = false;
		sprite.setScale(1, 1);
		speedX *= 10;
		sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y - sprite.getTexture()->getSize().y / 2);
	}
}

void Wizard::slow() {
	HP -= 10;
	if (!slowed) {
		timerSlow = time(0);
		slowed = true;
		speedX /= 10;
	}
}

void Wizard::unSlow() {

	if (slowed and time(0) - timerSlow > 5) {
		slowed = false;
		speedX *= 10;
	}
}