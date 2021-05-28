#include "Jinn.h"
#include "JinnBullet.h"


template<typename T>
T random(T min, T max);

Jinn::Jinn(sf::Vector2f vector, sf::RenderWindow* var,int level) :Enemy(vector, var,level) {
    numberOfTexture = 11;
    for (int i = 1; i <= numberOfTexture; i++) {
        sf::Texture* temp = new sf::Texture;
        temp->loadFromFile("images/jinn/Jinn_" + std::to_string(i) + ".png");
        texture.push_back(temp);
    }
 
    sprite.setTexture(*texture[0]);
    sprite.setPosition(vector);
    Enemy::HP = 6000;
}



void Jinn::addBullets(std::vector<Bullet*>& bullets) {
    if (random(1, int(CLOCKS_PER_SEC) * 8) == 5) {
        bullets.push_back(new JinnBullet(this->sprite.getPosition(), window));

    }
}


