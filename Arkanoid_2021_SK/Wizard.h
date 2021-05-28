#pragma once
#include "Object.h"


class Wizard :public Object {
private:
	virtual void addToGame();
	virtual void move();
	sf::RectangleShape hpBar;
	sf::Vector2f defaultPosition;
	sf::Texture texture[6];
	int counter = 0;
	sf::Texture texture_die;
	bool stopped = false,reducted = false,slowed=false;
	time_t timerStun,timerReduct,timerSlow;
	int demage = 100;
	void unReduct();
	void unSlow();
	
public:
	Wizard() {};
	Wizard(double speedX_, double speedY_, sf::RenderWindow* var);
	sf::Sprite getSprite() { return sprite; }
	friend class Game;
	friend bool collision(Object* v1, Object* v2);
	~Wizard();
	void hit() { HP -= 10; }
	void moreSpeed() { speedX++; }
	void moreHP() { HP+=10; }
	void moreDemage() { demage+=50; }
	void stop() { stopped = true; timerStun = time(0); sprite.setTexture(texture[5]); };
	void reduct();
	void slow();
};
