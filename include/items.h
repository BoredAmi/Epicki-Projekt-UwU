#ifndef items_h
#define items_h

//replace all enums with classes
#include <iostream>
#include <vector>
#include "critter.h"
#include "plants.h"
#include "world.h"
#include "player.h"
class Player;
class sheep;
class cow;
class tiles;

class item
{
public:
    int getId();
    item(int id,int quant);
    virtual ~item();
protected:
    int value;
    int id;
    int quant;
};
//tools
class tools:public item
{
public:
    tools(int id,int quant);
    virtual ~tools();
    int durability;
};
class sheers:public tools
{
public:
    bool cut_wool(sheep& she,Player& player);
    sheers(int id,int quant=1);
    ~sheers();
};

class bucket:public tools
{
public:
    bool milk_cow(cow& muu,Player& player);
    bucket(int id,int quant=1);
    ~bucket();
};
class scythe:public tools
{
public:
    int cut();
    scythe(int id,int quant=1);
    ~scythe();
protected:
    int range;
};
class hoe:public tools
{
public:
    bool till(tiles& tile);
    hoe(int id,int quant=1);
    ~hoe();
};
//food items
class food:public item
{
public:
    food(int id,int quant);
    virtual ~food();
protected:
    int hunger_restore;
};
class milk:public food
{
public:
    milk(int id,int quant);
    ~milk();
};
class egg:public food
{
public:
    egg(int id,int quant);
    ~egg();
};

//materials
class materials:public item
{

public:
    materials(int id,int quant);
    ~materials();
};
class wood:public materials
{
public:
    wood(int id,int quant);
    ~wood();
};

class wool:public materials
{
public:
    wool(int id,int quant);
    ~wool();
};
class stone:public materials
{
public:
    stone(int id,int quant);
    ~stone();
};
#endif
