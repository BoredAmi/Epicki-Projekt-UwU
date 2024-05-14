#include "critter.h"

critter::critter(int x, int y,int hp,tools correct_tool,int reset_time,drop drop_type) : x(x), y(y), hp(hp),correct_tool(correct_tool),reset_time(reset_time),drop_type(drop_type){}
critter::~critter() {
    std::cout << "Animal at (" << x << ", " << y << ") destroyed.\n";
}
int critter::getX() const {
    return x;
}

int critter::getY() const {
    return y;
}

void critter::setPosition(int x, int y) {
    this->x = x;
    this->y = y;
}

cow::cow(int x, int y,int hp,tools correct_tool,int reset_time,drop drop_type) : critter(x, y,20,bucket,5,beef){}
cow::~cow(){}
sheep::sheep(int x, int y,int hp,tools correct_tool,int reset_time,drop drop_type) : critter(x, y,25,sheers,5,lamb){}
sheep::~sheep(){}


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

//Takes damage result depends on if the attack was in range of chosen critter
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

