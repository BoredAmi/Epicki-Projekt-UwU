#include "critter.h"
//critter functions
//set initial values while creating
critter::critter(int x, int y,int hp) : entity(x,y,hp){}
//announce death
critter::~critter() {
    std::cout << "Animal at (" << x << ", " << y << ") destroyed.\n";
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
harv_crit::harv_crit(int x, int y,int hp): critter(x,y,hp),collected_today(false){}
harv_crit::~harv_crit(){};


//set initial values for those animals
cow::cow(int x, int y) : harv_crit(x,y,20){}
cow::~cow(){}
sheep::sheep(int x, int y) : harv_crit(x,y,25){}
sheep::~sheep(){}
//non_harv_crit functions
//set initial values
non_harv_crit::non_harv_crit(int x, int y,int hp): critter(x,y,hp){}
non_harv_crit::~non_harv_crit(){};
chicken::chicken(int x,int y):non_harv_crit(x,y,15){}
chicken::~chicken(){}
pig::pig(int x,int y):non_harv_crit(x,y,25){}
pig::~pig(){}