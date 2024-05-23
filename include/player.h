#ifndef player_h
#define player_h
#include <SFML/Graphics.hpp>
#include "items.h"

class Player {
public:
    sf::Vector2f position;
    float speed;
    Player(float startX, float startY, float moveSpeed);
    
    void move(float dx, float dy);
protected:
    int energy;
    int hp;
};

#endif