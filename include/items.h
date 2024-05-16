#ifndef items_h
#define items_h

//replace all enums with classes
#include <iostream>
#include <vector>
#include "critter.h"
#include "plants.h"

class eq
{
public:
    void change_item(int slot);
    bool addItem(item* Item);
    bool removeItem(int chosen_item);

    eq();
    ~eq();
private:
    std::vector<item*> items;
    int chosen_item;
    int max_capacity;
};
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
};
class sheers:public tools
{
public:
    bool cut_wool(sheep she);
    sheers(int id,int quant=1);
    ~sheers();
};

class bucket:public tools
{
public:
    bool milk_cow(cow muu);
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
    milk(int id,int quant);
    ~milk();
};
class truffle:public food
{
public:
    truffle(int id,int quant);
    ~truffle();
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
