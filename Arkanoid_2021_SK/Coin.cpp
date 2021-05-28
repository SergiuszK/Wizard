#pragma once
#include "Coin.h"
#include "Game.h"

Coin::Coin(sf::Vector2f vector, sf::RenderWindow* var) :Ball(vector, var) {
    for (int i = 1; i <= numberOfTexture; i++) {
        sf::Texture* temp = new sf::Texture;
        temp->loadFromFile("images/coin/Coin_0"+ std::to_string(i) +".png");
        texture.push_back(temp);
    }
    sprite.setTexture(*texture[0]);
    sprite.setPosition(vector);
    speedY = abs(((double)(rand() % 10 + 10)) / 10);
    speedX = 0;
    setWindow(var);
    drawBall = true;

}

void Coin::move() {

    if (counter < numberOfTexture) {
        sprite.setTexture(*texture[counter]);
        counter++;
    }
    else
        counter = 0;
    Ball::move();
}