#include "entity.h"
int entity::getX() const {
    return x;
}
int entity::getY() const {
    return y;
}
int entity::getHp() const {
    return hp;
}
void entity::setPosition(int x, int y) {
    this->x = x;
    this->y = y;
}
entity::entity(int x, int y,int hp):x(x),y(y),hp(hp){}
entity::~entity(){}