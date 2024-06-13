#ifndef CRITTER_H
#define CRITTER_H

#include <iostream>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <vector>
#include <initializer_list>
#include "entity.h"

class critter : public entity {
public:
    critter(int x, int y, int hp, const std::initializer_list<std::string>& textureFiles);
    virtual ~critter();

    void move(int worldWidth, int worldHeight);
    bool take_dmg(int dmg);
    void draw(sf::RenderWindow &window);

protected:
    std::vector<sf::Texture> textures;
    sf::Sprite sprite;
    size_t currentTextureIndex;
};

class harv_crit : public critter {
public:
    harv_crit(int x, int y, int hp, const std::initializer_list<std::string>& textureFiles);
    virtual ~harv_crit();

    bool harvest();
    int getHarvestCount() const;
    void resetDailyState();

    bool if_collected_today();

    void set_collected_today(bool a);

protected:
    bool collected_today;
    int harvest_count;
};

class cow : public harv_crit {
public:
    cow(int x, int y);
    virtual ~cow();

    void loadAnimation(const std::string& file, int frameWidth, int frameHeight);
    void updateAnimation();
    void move(float offsetX, float offsetY);
    void randomMove(float deltaTime);

private:
    std::vector<sf::IntRect> animationFrames;
    size_t currentFrame;
    sf::Clock animationClock;

    int direction;  // 0: right, 1: left, 2: down, 3: up
    float moveDuration;
    float moveTime;
};

class sheep : public harv_crit {
public:
    sheep(int x, int y);
    virtual ~sheep();
    void loadAnimation(const std::string& file, int frameWidth, int frameHeight);
    void updateAnimation();
    void move(float offsetX, float offsetY);
    void randomMove(float deltaTime);
private:
    std::vector<sf::IntRect> animationFrames;
    size_t currentFrame;
    sf::Clock animationClock;

    int direction;  // 0: right, 1: left, 2: down, 3: up
    float moveDuration;
    float moveTime;
};

class non_harv_crit : public critter {
public:
    non_harv_crit(int x, int y, int hp, const std::initializer_list<std::string>& textureFiles);
    virtual ~non_harv_crit();
    bool harvest();
    int getHarvestCount() const;
    void resetDailyState();
    bool if_collected_today();
    void set_collected_today(bool state);
protected:
    bool collected_today;
    int harvest_count;
};

class chicken : public non_harv_crit {
public:
    chicken(int x, int y);
    virtual ~chicken();

    void loadAnimation(const std::string& file, int frameWidth, int frameHeight);
    void updateAnimation();
    void move(float offsetX, float offsetY);
    void randomMove(float deltaTime);

private:
    std::vector<sf::IntRect> animationFrames;
    size_t currentFrame;
    sf::Clock animationClock;

    int direction;  // 0: right, 1: left, 2: down, 3: up
    float moveDuration;
    float moveTime;
};

class pig : public non_harv_crit {
public:
    pig(int x, int y);
    virtual ~pig();

    void loadAnimation(const std::string& file, int frameWidth, int frameHeight);
    void updateAnimation();
    void move(float offsetX, float offsetY);
    void randomMove(float deltaTime);
private:
    std::vector<sf::IntRect> animationFrames;
    size_t currentFrame;
    sf::Clock animationClock;

    int direction;  // 0: right, 1: left, 2: down, 3: up
    float moveDuration;
    float moveTime;
};

#endif // CRITTER_H
