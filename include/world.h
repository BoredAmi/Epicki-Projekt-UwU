#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <memory>
#include "critter.h"

class World {
public:
    World(int width, int height);
    void addAnimal(std::shared_ptr<critter> animal);
    void update();
    void dealDamageToAnimal(int index, int damage);

private:
    int width;
    int height;
    std::vector<std::vector<int>> grid; // 0 for empty, 1 for occupied (could be expanded for more details)
    std::vector<std::shared_ptr<critter>> animals;
};

#endif
