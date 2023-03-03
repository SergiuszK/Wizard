#include "Rainbow.h"
#include "RainbowBullet.h"

template<typename T>
T random(T min, T max);

Rainbow::Rainbow(sf::Vector2f vector, sf::RenderWindow* var,int level) :Enemy(vector, var,level) {
    numberOfTexture = 5;
    for (int i = 1; i <= numberOfTexture; i++) {
        sf::Texture* temp = new sf::Texture;
        temp->loadFromFile("images/rainbow/Rainbow_" + std::to_string(i) + ".png");
        texture.push_back(temp);
    }

    sprite.setTexture(*texture[0]);
    sprite.setPosition(vector);
}

void Rainbow::addBullets(std::vector<Bullet*>& bullets) {
    if (random(1, int(CLOCKS_PER_SEC) * 8) == 5) {
        bullets.push_back(new RainbowBullet(this->sprite.getPosition(), window));
    }
}