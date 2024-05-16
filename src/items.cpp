#include "items.h"
//eq functions
//change chosen slot to use from eq
void eq::change_item(int slot)
{
    chosen_item=slot;
}
//add item to the vector
bool eq::addItem(item* Item)
{
    if(items.size()>max_capacity)
    {
        items.push_back( Item);
        return true;
    }
    else
    {
        return false;
    }
}
//removes item from vector
bool eq::removeItem(int chosen_item)
{
    for(auto it =items.begin();it != items.end();++it)
    {
        if((*it)->getId()==chosen_item)
        {
            delete *it;
            items.erase(it);
            return true;
        }
    }
    return false;
}
eq::~eq() {
    for (auto item : items) {
        delete item;
    }
}
//item functions
item::item(int id,int quant):id(id),quant(quant){}
item::~item(){}
//tools functions
tools::tools(int id,int quant):item(id,quant){}
tools::~tools(){}
sheers::sheers(int id,int quant): tools(id,quant){}
sheers::~sheers(){}
bucket::bucket(int id,int quant):tools(id,quant){}
bucket::~bucket(){}
scythe::scythe(int id,int quant):tools(id,quant){}
scythe::~scythe(){}
food::food(int id,int quant):item(id,quant){}
food::~food(){}
milk::milk(int id,int quant):food(id,quant){}
milk::~milk(){}
truffle::truffle(int id,int quant):food(id,quant){}
truffle::~truffle(){}
egg::egg(int id,int quant):food(id,quant){}
egg::~egg(){}
materials::materials(int id,int quant):item(id,quant){}
materials::~materials(){}
wood::wood(int id,int quant):materials(id,quant){}
wood::~wood(){}
wool::wool(int id,int quant):materials(id,quant){}
wool::~wool(){}
stone::stone(int id,int quant):materials(id,quant){}
stone::~stone(){}
