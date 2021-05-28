#pragma once
#include "Game.h"
#include <string>
#include <iostream>
#include <random>
#include <map>



thread_local std::mt19937 gen{ std::random_device{}() };

template<typename T>
T random(T min, T max) {
    return std::uniform_int_distribution<T>{min, max}(gen);
}


int Game::level = 1;

bool collision(Object *v1,Object *v2) {
    if (v1->sprite.getGlobalBounds().intersects(v2->sprite.getGlobalBounds())) {
        return true;
    }
    return false;
}

Game::Game():window(sf::VideoMode(width, height), "Arkanoid", sf::Style::Fullscreen) {
    window.setFramerateLimit(0);
    window.setVerticalSyncEnabled(true);
    setSettings();
}

void Game::setMusic() {
    //Background
    musics["menu"].openFromFile("music/music.wav");
    musics["menu"].setLoop(true);
    musics["menu"].setVolume(2.f);
    //coins
    musics["coins"].openFromFile("music/coins.ogg");
    musics["coins"].setVolume(2.f);
    //hit
    musics["hit"].openFromFile("music/splat.wav");
    musics["hit"].setVolume(2.f);
}

void Game::setSettings() {
    srand(time(0));
    setMusic();
    
    texture.loadFromFile("images/menu.png");
   
    background.setScale(window.getSize().x / texture.getSize().x, window.getSize().y/ texture.getSize().y);
    background.setTexture(texture);
   
    musics["menu"].play();
    level_to_show = 1;
    level = 1;
    score = 0;
    
    wizard = new Wizard(20, 20, &window);
   
    balls.clear();
    coins.clear();
    bullets.clear();
    enemies.clear();
    balls.push_back(new Ball(wizard->sprite.getPosition(), &window));
    addEnemies();
    gold = 0;
    menu = new Menu(width, height);
    font.loadFromFile("Almendra-BoldItalic.otf");
    gold_text.setFont(font);
    gold_text.setFillColor(sf::Color::Red);
    gold_text.setString("Gold: " + std::to_string(gold));
    gold_text.setPosition(window.getSize().x * 0.90, window.getSize().y * 0.01);
    score_text.setFont(font);
    score_text.setFillColor(sf::Color::Red);
    score_text.setString("Score: "+ std::to_string(score));
    score_text.setPosition(window.getSize().x * 0.90, window.getSize().y * 0.05);
    level_text.setFont(font);
    level_text.setFillColor(sf::Color::Red);
    level_text.setString("Level: " + std::to_string(level_to_show));
    level_text.setPosition(window.getSize().x * 0.90, window.getSize().y * 0.09);
    first = true;
}

void Game::showMenu() {
    window.clear();
    window.draw(background);
    window.draw(gold_text);
    window.draw(score_text);
    window.draw(level_text);

    first = false;

    sf::Event eventMenu;
    while (window.pollEvent(eventMenu)) {

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            menu->MoveUp();

        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            menu->MoveDown();
        }

        if (menu->shopOn == false and menu->rankOn == false and !change) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                switch(menu->getPressedItem()){
                case 0:
                    menu->turnOnGame();
                    texture.loadFromFile("images/level_" + std::to_string(level) + "/background.png");
                    break;
                case 1:
                    menu->turnOnShop();
                    change = true;
                    break;
                case 2:
                    menu->turnOnRank();
                    change = true;
                    break;
                case 3: 
                    window.close();
                    break;
                }
            }
        }
        else if (menu->shopOn and !change) {

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                switch (menu->ptr_shop->getPressedItem()) {
                case 0:
                    if (gold >= 5) {
                        wizard->moreSpeed();
                        gold -= 5;
                        musics["coins"].play();
                        change = true;
                    }
                    break;
                case 1:
                    if (gold >= 20 and wizard->HP < 100) {
                        wizard->moreHP();
                        gold -= 20;
                        musics["coins"].play();
                        change = true;
                    }
                    break;
                case 2:
                    if (gold >= 20) {
                        wizard->moreDemage();
                        gold -= 20;
                        musics["coins"].play();
                        change = true;
                    }
                    break;
                case 3:
                    menu->turnOfShop();
                    change = true;
                    break;
                }
            }
        }
            else if (menu->rankOn and !change) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) or
                    (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)and menu->rank->rankingText[menu->rank->selectedItemIndex].getString() == "Wyjdz" ) ) {
                    menu->turnOfRank();
                    change = true;
                    break;
                }

        }
        else change = false;
    }
    gold_text.setString("Gold: " + std::to_string(gold));

    menu->draw(window);
    window.display();


}

void Game::run(){

    while (window.isOpen()){
        if (menu->isTurnOnGame() == false ) {
            showMenu();
        }
        else{
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) and wizard->HP <= 0) {
                menu->turnOfGame();
                savePoints();
                setSettings();
                
            }
            processEvents();
            update();
            render();
        }
    }
}

void Game::processEvents(){
    sf::Event event;
   
    while (window.pollEvent(event)){
        if (event.type == sf::Event::Closed)
            window.close();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            menu->turnOfGame();
            texture.loadFromFile("images/menu.png");
        }
        wizard->move();
        
    }

}

void Game::render(){
    
   
    showElements();
    window.display();
}

void Game::showElements() {
    window.draw(background);
    
    window.draw(gold_text);
    window.draw(score_text);
    window.draw(level_text);
    for (auto ball : balls) {
        ball->addToGame();
    }
    for (auto enemy : enemies) {
        enemy->addToGame();
    }
    for (auto bullet : bullets) {
        bullet->addToGame();
    }
    for (auto coin : coins) {
        coin->addToGame();
    }

    wizard->addToGame();

}

void Game::update(){

    if (balls.size() < numberOfBall and wizard->HP > 0)
        addNewBall();

    for (auto ball : balls) {
        for (auto enemy : enemies) {
            if (collision(ball, enemy)) {
                musics["hit"].openFromFile("music/splat.wav");
                musics["hit"].play();
                ball->changeY();
                enemy->hit(wizard->demage);
                if (enemy->HP <= 0)
                    enemy->isAlive = false;
                
                
            }
        }
    }


    int i = 0;
    for (auto ball : balls) {
        if (collision(ball, wizard)) {

            delete ball;
            balls.erase(balls.begin() + i);
            wizard->hit();
            
            addNewBall();
        }
        else {
            ball->move();
        }
       
        i++;
    }

    for (auto enemy : enemies) {
        for (auto enemy2 : enemies) {
            if (enemy == enemy2)continue;
            if (collision(enemy, enemy2)) {

                enemy->changeX();

                //enemy2->changeX();
                enemy->changeY();
                //enemy2->changeY();

                break;
            }
        }

    }

    i = 0;
    
    for (auto enemy : enemies) {
        if (enemy->getAlive() != true) {
            if (random(1, 100) < 15)
            coins.push_back(new Coin(enemy->sprite.getPosition(), &window));
            delete enemy;
            score++;
            enemies.erase(enemies.begin() + i);
            break;
        }
        else {
            enemy->move();
               
            enemy->addBullets(bullets);
        }

        i++;
    }

    
    

    
    score_text.setString("Score: "+std::to_string(score));
    gold_text.setString("Gold: " + std::to_string(gold));
     i = 0;
    for (auto ball : balls) {
        if (ball->isAlive() != true) {
            delete ball;
            balls.erase(balls.begin() + i);
            addNewBall();
            break;
        }
        i++;
    }
     
    
  

    if (enemies.empty())
        nextLevel();


    i = 0;
    for (auto bullet : bullets) {
        if (collision(bullet, wizard)) {
            bullet->hit(wizard);
            delete bullet;
            bullets.erase(bullets.begin() + i);
           

        }else if (bullet->isAlive() != true) {
            delete bullet;
            bullets.erase(bullets.begin() + i);
            break;
        }else {
            bullet->move();
        }
        i++;
    }

  

    i = 0;
    for (auto coin : coins) {
        if (collision(coin, wizard)) {
            delete coin;
            coins.erase(coins.begin() + i);
            gold += random(10,50);

        }
        else if (coin->isAlive() != true) {
            delete coin;
            coins.erase(coins.begin() + i);
            break;
        }
        else {
            coin->move();
        }
        i++;
    }


    if (wizard->HP == 0)
        balls.clear();
}

void Game::addNewBall() {
    balls.push_back(new Ball(wizard->sprite.getPosition(), &window));
}

Game::~Game() {
    delete wizard;
    for (auto ball : balls) {
        delete ball;
    }
    for (auto enemy : enemies) {
        delete enemy;
    }
    for (auto bullet : bullets) {
        delete bullet;
    }
    for (auto coin : coins) {
        delete coin;
    }
    delete menu;
}

void Game::addEnemies() {
    sf::Vector2f vector; vector.x = 50; vector.y =70;
    Jinn jinn = Jinn(vector, &window, level);
    int k = window.getSize().x / (jinn.sprite.getTexture()->getSize().x*2);
    int n = window.getSize().y / (jinn.sprite.getTexture()->getSize().y*2);
    for (int i = 0; i < k -2; i++) {
        for (int j = 0; j < n / 4 ; j++) {
            if (level == 1)
                enemies.push_back(new Spider(vector, &window,level));
            else if (level == 2)
                enemies.push_back(new Rainbow(vector, &window, level));
            else if (level == 3) {
                enemies.push_back(new Jinn(vector, &window, level));
            }
            vector.y += (jinn.sprite.getTexture()->getSize().y*2);
        }
        vector.y = 70;
        vector.x += (jinn.sprite.getTexture()->getSize().x * 2);
        
    }

  
}


void Game::showLevel() {
    sf::Text temp;
    font.loadFromFile("Almendra-BoldItalic.otf");
    temp.setFont(font);
    temp.setFillColor(sf::Color::Red);
    temp.setCharacterSize(70.0f);
    temp.setString("Poziom: " + std::to_string(level_to_show));
    temp.setPosition(window.getSize().x * 0.45, window.getSize().y * 0.45);

    window.draw(temp);
    window.display();

    bool keyPressed = false;
    while (keyPressed == false)
    {

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
        {
            keyPressed = true;

        }
    }
}

void Game::nextLevel() {
    bullets.clear();
    balls.clear();
    
    if (level < 3)
        level++;
    else
       level = 1;

    level_text.setString("Level: " + std::to_string(++level_to_show));
    texture.loadFromFile("images/level_" + std::to_string(level) + "/background.png");
    background.setScale(window.getSize().x / texture.getSize().x, window.getSize().y / texture.getSize().y);
    showLevel();


    sf::Vector2f vector; vector.x = 10; vector.y = 10;
    Spider spider = Spider(vector, &window,level);
    spider.nextLevel();
    addEnemies();

}




void Game::savePoints() {

    sf::String userInput;
    sf::Event event;
    sf::Text temp;
    font.loadFromFile("Almendra-BoldItalic.otf");
    temp.setFont(font);
    temp.setFillColor(sf::Color::Red);
    temp.setCharacterSize(70.0f);
    temp.setPosition(window.getSize().x * 0.40, window.getSize().y * 0.45);

    bool keyPressed = false;
   

    

    while (window.isOpen() and !keyPressed) {
        sf::Event event;
        
        while (window.pollEvent(event))
        {
            window.draw(background);
            if (event.type == sf::Event::TextEntered)
            {
   
                if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                userInput.insert(userInput.getSize(), event.text.unicode);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) 
            {
                userInput.erase(userInput.getSize() - 1);
                
            }

            temp.setString("Zapisz sie: " + userInput);
            window.draw(temp);
            window.display();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
            {
                keyPressed = true;

            }
        }
    }
    std::ofstream outfile;

    std::string name;
    for (int i = 0; i < userInput.getSize(); i++) {
        if (userInput[i] >= 'a' and userInput[i] <= 'z' or userInput[i] >= 'A' and userInput[i] <= 'Z' or userInput[i] >= '0' and userInput[i] <= '9')
            name += userInput[i];
    }

    outfile.open("results.txt", std::ios_base::app); // append instead of overwrite
    outfile <<"name: " << name << " score: " << score <<std::endl;

    outfile.close();
    menu->rank->refresh(width,height);
}