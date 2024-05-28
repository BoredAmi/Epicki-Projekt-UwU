#include "items.h"
//eq functions
//change chosen slot to use from eq

//item functions
item::item(int id,int quant):id(id),quant(quant){}
item::~item(){}
//tools functions
tools::tools(int id,int quant):item(id,quant){}
tools::~tools(){}
sheers::sheers(int id,int quant): tools(id,quant){}
sheers::~sheers(){}
bool sheers::cut_wool(sheep& she,Player& player)
{
    if(she.collected_today==false)
    {
        wool* Wool=new wool(1,1);
        player.addItem(Wool);
        durability--;
        return true;
    }
    else
    {
        return false;
    }
}
bucket::bucket(int id,int quant):tools(id,quant){}
bucket::~bucket(){}
bool bucket::milk_cow(cow& muu,Player& player)
{
    if(muu.collected_today==false)
    {
        milk* Milk=new milk(0,1);
        player.addItem(Milk);
        quant--;
        return true;
    }
    else
    {
        return false;
    }
}
scythe::scythe(int id,int quant):tools(id,quant){}
scythe::~scythe(){}
hoe::hoe(int id,int quant):tools(id,quant){}
hoe::~hoe(){}
bool hoe::till(tiles& tile)
{
    if(tile.tile_type==land)
    {
        tile.change_type(plowed);
        durability--;
        return true;
    }
    else
    {
        return false;
    }
}
//food functions
food::food(int id,int quant):item(id,quant){}
food::~food(){}

void food::eat(Player& player)
{
    player.energy+=hunger_restore;
    if(quant=1)
    {
        player.removeItem(id);
    }
    else if(quant>1)
    {
        quant--;
    }
}
milk::milk(int id,int quant):food(id,quant){}
milk::~milk(){}
truffle::truffle(int id,int quant):food(id,quant){}
truffle::~truffle(){}
egg::egg(int id,int quant):food(id,quant){}
egg::~egg(){}
//materials functions
materials::materials(int id,int quant):item(id,quant){}
materials::~materials(){}
wood::wood(int id,int quant):materials(id,quant){}
wood::~wood(){}
wool::wool(int id,int quant):materials(id,quant){}
wool::~wool(){}
stone::stone(int id,int quant):materials(id,quant){}
stone::~stone(){}
