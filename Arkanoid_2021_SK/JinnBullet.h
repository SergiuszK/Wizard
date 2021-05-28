#pragma once
#include "Bullet.h"
class JinnBullet :
    public Bullet
{
private:
    time_t timer;
    double speedX;
    virtual void hit(Wizard* wizard);
public:

    JinnBullet(sf::Vector2f vector, sf::RenderWindow* var);
    
    
};

