#ifndef critter_h
#define critter_h

#include <iostream>
#include "items.h"
enum drop{beef,lamb,pork,chicken_m};

class critter
{
public:
    int getX() const;
    int getY() const;

    bool take_dmg(int dmg);
    void move(int worldWidth, int worldHeight);
    void setPosition(int x, int y);
    critter(int x, int y,int hp,int reset_time,drop drop_type);
    virtual ~critter();
protected:
    int x;
    int y;
    int hp;
    int reset_time;
    int last_time;
    drop drop_type;
};
class harv_crit:public critter
{
public:
    bool harvest_from_animal(tools current_tool,int now_time);
    harv_crit(int x, int y,int hp,int reset_time,drop drop_type, tools correct_tool, animal_material harv_mat);
    virtual~harv_crit();
protected:
    animal_material harv_mat;
    tools correct_tool;
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
    bool spawn_item(int time_now);
    non_harv_crit(int x, int y,int hp,int reset_time,drop drop_type,spawnable_item item);
    ~non_harv_crit();
protected:
    spawnable_item item;
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