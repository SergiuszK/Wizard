#pragma once
#include "Object.h"
#include "Bullet.h"

class Enemy :public Object
{
protected:
	bool isAlive = true;
	virtual void addToGame();
public:
	static int number;
	static int level;
	int numberOfTexture = 12;
	Enemy(sf::Vector2f vector, sf::RenderWindow* var, int);
	friend class Game;
	bool getAlive() { return isAlive; }
	friend bool collision(Object* v1, Object* v2);
	virtual void move();
	void changeX();
	void changeY();
	~Enemy();
	std::vector<sf::Texture*> texture;
	int counter = 1;
	void nextLevel();
	virtual void addBullets(std::vector<Bullet*>& bullets) = 0;
};