#ifndef gathering_h
#define gathering_h
#include "items.h"
#include "world.h"
#include "player.h"
class entity
{
public:
    int getX() const;
    int getY() const;
    void setPosition(int x, int y);
    entity(int x, int y,int hp);
    virtual ~entity();
protected:
    int x;
    int y;
    int hp;
};

class rock:public entity
{
public:
    rock(int x,int y);
    ~rock();
};

class tree:public entity
{
public:
    tree(int x,int y);
    ~tree();
};
#endif
