#include <iostream>
#include "items.h"
enum drop{poultery,beef,lamb};
class critter
{
public:
    int hp,reset_time;
    bool take_dmg(int range,int weapon_range,int dmg);
    critter(/* args */);
    ~critter();
};

class cow:critter
{
public:
    int last_milk_time;
    tools correct_tool=bucket;
    bool milk(int time_now, tool& current_tool);
    cow(/* args */);
    ~cow();
};

class sheep:critter
{
public:
    int last_trim_time;
    tools correct_tool=sheers;
    bool trim(int time_now, tool& current_tool);
    sheep(/* args */);
    ~sheep();
};

class chicken:critter
{
public:
    chicken(/* args */);
    ~chicken();
};