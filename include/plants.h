#ifndef plants_h
#define plants_h
#include "items.h"
#include "entity.h"
enum growth_stages{freshly_planted,growing,ready};
class entity;
class plant:public entity
{
public:
    void water();
    plant(int x,int y);
    virtual ~plant();
protected:
    growth_stages current_stage;
    bool watered;
    int growth_start;
    int growth_length;
};
class pickupable:public plant
{
public:
    bool pickup();
    pickupable(int x,int y);
    virtual ~pickupable();
};

class carrot:public pickupable
{
public:
    carrot(int x,int y);
    ~carrot();
};
class potato:public pickupable
{
public:
    potato(int x,int y);
    ~potato();
};

class cutable:public plant
{
public:
    cutable(int x,int y);
    virtual~cutable();
};
class wheat
{
public:
    wheat(/* args */);
    ~wheat();
};



#endif