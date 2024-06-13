#include "player.h"
Player::Player(float startX, float startY, float moveSpeed) : position(startX, startY), speed(moveSpeed) {
    hp = 100;
    energy = 100;
    max_capacity = 10;
    chosen_item = 0;
    sf::Texture texture; // Declare the texture variable
    //load player sprite
    if (!texture.loadFromFile("../assets/player.png")) {
        throw std::runtime_error("Cannot load player texture");
    }
    sprite.setTexture(texture);
    sprite.setPosition(position);
}

void Player::move(float dx, float dy) {
    position.x += dx * speed;
    position.y += dy * speed;
}
void Player::change_item(int slot)
{
    chosen_item=slot;
}
//add item to the vector
bool Player::addItem(item* Item)
{
    if(items.size()>max_capacity)
    {
        items.push_back( Item);
        return true;
    }
    else
    {
        return false;
    }
}
//removes item from vector
bool Player::removeItem(int chosen_item)
{
    for(auto it =items.begin();it != items.end();++it)
    {
        if((*it)->getId()==chosen_item)
        {
            delete *it;
            items.erase(it);
            return true;
        }
    }
    return false;
}
int Player::getEnergy()
{
    return energy;
}
int Player::getHp()
{
    return hp;
}
Player::~Player() {
    for (auto item : items) {
        delete item;
    }
}
