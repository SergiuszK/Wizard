#pragma once
#include "Menu.h"
#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Bullet.h"
#include "Wizard.h"
#include "Ball.h"
#include "Enemy.h"
#include "Coin.h"
#include "Spider.h"
#include "Rainbow.h"
#include "SpiderWeb.h"
#include "RainbowBullet.h"
#include "JinnBullet.h"
#include "Jinn.h"
#include <fstream>
#include <String>


class Game{
private:
    bool first = true;
    int numberOfBall = 3;
    int height = 1080;
    int width = 1920;
    int gold = 0;
    int score = 0;
    static int level;
    int level_to_show=1;
    Wizard* wizard;
    Ball* ball;
    std::vector<Ball*> balls;
    std::vector<Enemy*> enemies;
    std::vector<Bullet*> bullets;
    std::vector<Coin*> coins;
    sf::RenderWindow window;
    Menu* menu;
    sf::Sprite background;
    sf::Texture texture;
    sf::Font font;
    sf::Text score_text;
    sf::Text level_text;
    sf::Text gold_text;
    void processEvents();
    void update();
    void render();
    void showElements();
    void addNewBall();
    void addEnemies();
    void setSettings();
    void setMusic();
    //sf::Music music;
    sf::Music sound;
    bool change = false;
    void showLevel();
    void showMenu();
    std::map<std::string,sf::Music > musics;
    void savePoints();
public:
    Game();
    void run();
    ~Game();
    friend class Wizard;
    friend class Bullet;
    void nextLevel();
};

