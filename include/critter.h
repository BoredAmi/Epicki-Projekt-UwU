#ifndef critter_h
#define critter_h

#include <iostream>
#include "items.h"
#include "gathering.h"

class critter:public entity
{
public:
    int getX() const;
    int getY() const;

    bool take_dmg(int dmg);
    void move(int worldWidth, int worldHeight);
    void setPosition(int x, int y);
    critter(int x, int y,int hp);
    virtual ~critter();
protected:

};
class harv_crit:public critter
{
public:
    bool harvest_from_animal(tools current_tool,int now_time);
    harv_crit(int x, int y,int hp);
    virtual~harv_crit();
    bool collected_today;
protected:
    
};
class cow:public harv_crit
{
public:
    cow(int x, int y);
    ~cow();
};

class sheep:public harv_crit
{
public:
    sheep(int x, int y);
    ~sheep();
};
class non_harv_crit:public critter
{
public:
    //spawnable item as item in imtems.h must be changed!!!!
    non_harv_crit(int x, int y,int hp);
    ~non_harv_crit();
protected:
    food* item;
};
class chicken:public non_harv_crit
{

public:
    chicken(int x, int y);
    ~chicken();
};
class pig:public non_harv_crit
{
public:
    pig(int x, int y);
    ~pig();
};



#endif