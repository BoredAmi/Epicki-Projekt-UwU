#ifndef items_h
#define items_h


#include <iostream>
enum tools{pickaxe,sheers,bucket,shovel};
enum material{copper,iron,diamond};
enum animal_material{milk,wool};
class item
{
public:
    item(/* args */);
    ~item();
};
class tool:item
{
public:
    tools type;
    material current_material;
    int durability;
    tool(/* args */);
    ~tool();
};
#endif
