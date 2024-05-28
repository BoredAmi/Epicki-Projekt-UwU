#include "gathering.h"
    int entity::getX() const{
        return x;
    }
    int entity::getY() const{
        return y;
    }
    void entity::setPosition(int x, int y){
        this->x=x;
        this->y=y;
    }
    entity::entity(int x, int y,int hp):x(x),y(y),hp(hp){}
    entity::~entity(){}
    rock::rock(int x,int y):entity(x,y,5){}
    rock::~rock(){}
    tree::tree(int x,int y):entity(x,y,5){}
    tree::~tree(){}