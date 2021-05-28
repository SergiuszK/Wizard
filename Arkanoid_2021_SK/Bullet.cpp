#pragma once
#include "Bullet.h"
#include "Game.h"


Bullet::Bullet(sf::Vector2f vector, sf::RenderWindow* var) {
    vector.y = vector.y + vector.y*0.4;
    sprite.setPosition(vector);
    setWindow(var);
    draw = true;

}

void Bullet::addToGame() {
    window->draw(sprite);
}

void Bullet::move() {
    sf::Vector2f vector = sprite.getPosition();
    x = vector.x;
    y = vector.y;
    if (x <= 0 or x >= window->getSize().x - sprite.getTexture()->getSize().x) {
        speedX = (-1) * speedX;

    }
    if (y + speedY <= 0) {
        speedY = (-1) * speedY;

    }
    if (y > window->getSize().y)
        draw = false;
    sprite.move(speedX, speedY);

    vector = sprite.getPosition();
    x = vector.x;
    y = vector.y;
}

bool Bullet::isAlive() {
    return this->draw;
}

