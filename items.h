#include <iostream>
enum tools{pickaxe,sheers,bucket,shovel};
enum material{copper,iron,diamond};
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

