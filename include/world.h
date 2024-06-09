#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <memory>
#include "critter.h"
#include "perlin.h"
enum tile_types { land, plowed, water };
class critter;
class tiles {
public:
    tile_types tile_type;
    void change_occupation();
    bool change_type(tile_types type);
    void addEntity(std::unique_ptr<entity> entity);
    tiles(tile_types type);   
    ~tiles();
    bool occupation; // 0 for empty, 1 for occupied 
private:
    
};

class World {
public:
    std::vector<std::vector<tiles>> grid;
    World(int width, int height);
    void addAnimal(std::shared_ptr<critter> animal);
    void update();
    void dealDamageToAnimal(int index, int damage);

protected:
    int width;
    int height;
    
    std::vector<std::shared_ptr<critter>> animals;
};
std::vector<std::vector<tiles>> generateWorld(int width, int height, const PerlinNoise& noise);
#endif
