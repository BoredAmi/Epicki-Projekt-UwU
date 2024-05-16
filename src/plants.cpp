//plant functions
#include "plants.h"
void plant::water()
{
    watered=true;
}
plant::plant(int x,int y,int time_now,int growth_length) : x(x),y(y),growth_start(time_now),growth_length(growth_length){current_stage=freshly_planted;watered=false;}
plant::~plant(){}
//pickupable and its derivatives funtions
bool pickupable::pickup()
{
    if(current_stage==ready)
    {
        return true;
    }
    else
    {
        return false;
    }
}
pickupable::pickupable(int x,int y,int time_now,int growth_length):plant(x,y,time_now,growth_length){}
pickupable::~pickupable(){}

carrot::carrot(int x,int y,int time_now,int growth_length):pickupable(x,y,time_now,growth_length){}
carrot::~carrot(){}

potato::potato(int x,int y,int time_now,int growth_length):pickupable(x,y,time_now,growth_length){}
potato::~potato(){};
//cutable and its derivatives functions
