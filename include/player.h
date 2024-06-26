#ifndef player_h
#define player_h
#include <SFML/Graphics.hpp>
#include "items.h"
enum direction {UP, DOWN, LEFT, RIGHT};
class item;
class Player {
public:
    void change_item(int slot);
    bool addItem(item* Item);
    bool removeItem(int chosen_item);
    int getEnergy();
    int getHp();
    sf::Vector2f position;
    float speed;
    Player(float startX, float startY, float moveSpeed);
    
    void move(float dx, float dy);
    ~Player();
sf::Sprite sprite;
protected:
    direction dir;
    
    std::vector<item*> items;
    int chosen_item;
    int max_capacity;    
    int energy;
    int hp;
};

#endif