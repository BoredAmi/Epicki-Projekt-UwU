//plant functions
#include "plants.h"
void plant::water()
{
    watered=true;
}
plant::plant(int x,int y) : entity(x,y,1) {current_stage=freshly_planted;watered=false;}
plant::~plant() {} 
pickupable::pickupable(int x,int y):plant(x,y){}
pickupable::~pickupable(){}

carrot::carrot(int x,int y):pickupable(x,y){}
carrot::~carrot(){}

potato::potato(int x,int y):pickupable(x,y){}
potato::~potato(){};
//cutable functions
cutable::cutable(int x,int y):plant(x,y){}
cutable::~cutable(){}
//wheat functions
wheat::wheat(/* args */)
{
}
wheat::~wheat()
{
}