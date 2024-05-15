#include "critter.h"
//critter functions
//set initial values while creating
critter::critter(int x, int y,int hp,int reset_time,drop drop_type) : x(x), y(y), hp(hp),reset_time(reset_time),drop_type(drop_type){}
//announce death
critter::~critter() {
    std::cout << "Animal at (" << x << ", " << y << ") destroyed.\n";
}
//get x coridnate
int critter::getX() const {
    return x;
}
//get y cordinate
int critter::getY() const {
    return y;
}
//set new cordinates
void critter::setPosition(int x, int y) {
    this->x = x;
    this->y = y;
}
//randomly chose the direction and set new cordiantes
void critter::move(int worldWidth, int worldHeight) {
    int direction = std::rand() % 4;
    int newX = x;
    int newY = y;

    switch (direction) {
        case 0: newX = (x + 1) % worldWidth; break; // Move right
        case 1: newX = (x - 1 + worldWidth) % worldWidth; break; // Move left
        case 2: newY = (y + 1) % worldHeight; break; // Move down
        case 3: newY = (y - 1 + worldHeight) % worldHeight; break; // Move up
    }

    x = newX;
    y = newY;
}
//Takes damage returns true when animal dies
bool critter::take_dmg(int dmg)
{
    hp=hp-dmg;
    if(hp<0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
//harv_crit functions
//set initial values for harv_crit
harv_crit::harv_crit(int x, int y,int hp,int reset_time,drop drop_type, tools correct_tool, animal_material harv_mat): critter(x,y,hp,reset_time,drop_type),correct_tool(correct_tool),harv_mat(harv_mat){}
harv_crit::~harv_crit(){};
//harvest from animal return true when action done correct
bool harv_crit::harvest_from_animal(tools current_tool,int now_time)
{
    if(current_tool==correct_tool && now_time-last_time==reset_time)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//set initial values for those animals
cow::cow(int x, int y) : harv_crit(x,y,20,5,beef,bucket,milk){}
cow::~cow(){}
sheep::sheep(int x, int y) : harv_crit(x,y,25,5,lamb,sheers,wool){}
sheep::~sheep(){}
//non_harv_crit functions
//set initial values
non_harv_crit::non_harv_crit(int x, int y,int hp,int reset_time,drop drop_type,spawnable_item item): critter(x,y,hp,reset_time,drop_type),item(item){}
non_harv_crit::~non_harv_crit(){};
//spawning returns true when its possible
bool non_harv_crit::spawn_item(int time_now)
{
    if(time_now-last_time>reset_time)
    {
        return true;
    }
    else
    {
        return false;
    }
}
chicken::chicken(int x,int y):non_harv_crit(x,y,15,7,chicken_m,egg){}
chicken::~chicken(){}
pig::pig(int x,int y):non_harv_crit(x,y,25,10,pork,truffle){}
pig::~pig(){}