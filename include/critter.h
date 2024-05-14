#ifndef critter_h
#define critter_h

#include <iostream>
#include "items.h"
enum drop{beef,lamb};

class critter
{
public:
    int getX() const;
    int getY() const;

    bool take_dmg(int dmg);
    void move(int worldWidth, int worldHeight);
    void setPosition(int x, int y);
    critter(int x, int y,int hp,tools correct_tool,int reset_time,drop drop_type);
    virtual ~critter();
protected:
    int x;
    int y;
    int hp;
    int reset_time;
    int last_time;
    tools correct_tool;
    drop drop_type;
};

class cow:critter
{
public:
    int last_milk_time;
    cow(int x, int y,int hp, tools correct_tool,int reset_time,drop drop_type);
    ~cow();
};

class sheep:critter
{
public:
    int last_trim_time;
    sheep(int x, int y,int hp,tools correct_tool,int reset_time,drop drop_type);
    ~sheep();
};

#endif