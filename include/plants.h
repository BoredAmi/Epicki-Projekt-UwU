#ifndef plants_h
#define plants_h
#include "plants.h"
#include "items.h"
#include "gathering.h"
enum growth_stages{freshly_planted,growing,ready};
class plant:public entity
{
public:
    void water();
    plant(int x,int y,int time_now,int growth_length);
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
    pickupable(int x,int y,int time_now,int growth_length);
    virtual ~pickupable();
};

class carrot:public pickupable
{
public:
    carrot(int x,int y,int time_now,int growth_length);
    ~carrot();
};
class potato:public pickupable
{
public:
    potato(int x,int y,int time_now,int growth_length);
    ~potato();
};

class cutable
{
public:
    bool cut_down(tools tool);
    cutable(int x,int y,int time_now,int growth_length);
    virtual~cutable();
};
class wheat
{
public:
    wheat(/* args */);
    ~wheat();
};

class hemp:public cutable
{
public:
    hemp(int x,int y,int time_now,int growth_length);
    ~hemp();
};







#endif