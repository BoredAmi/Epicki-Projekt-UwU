#ifndef gathering_h
#define gathering_h
#include "items.h"
#include "plants.h"

class rock:public entity
{
public:
    rock(int x,int y);
    ~rock();
};

class tree:public entity
{
public:
    tree(int x,int y);
    ~tree();
};
#endif
