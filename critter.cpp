#include "critter.h"
bool critter::take_dmg(int range, int weapon_range,int dmg)
{
    if(weapon_range>=range)
    {
        hp=hp-dmg;
        return true;
    }
    else
    {
        return false;
    }
}

bool cow::milk(int time_now,tool& current_tool)
{
    if((time_now-last_milk_time>=reset_time)&&(current_tool.type==correct_tool))
    {
        current_tool.durability=current_tool.durability-1;
        last_milk_time=time_now;
        return true;
    }
    else
    {
        return false;
    }
}
bool sheep::trim(int time_now,tool& current_tool)
{
    if((time_now-last_trim_time>=reset_time)&&(current_tool.type==correct_tool))
    {
        current_tool.durability=current_tool.durability-1;
        last_trim_time=time_now;
        return true;
    }
    else
    {
        return false;
    }
}
