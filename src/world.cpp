#include "world.h"
#include <cstdlib>
#include <ctime>

World::World(int width, int height) : width(width), height(height) {
    grid.resize(height, std::vector<int>(width, 0));
    std::srand(static_cast<unsigned>(std::time(0)));
}

void World::addAnimal(std::shared_ptr<critter> animal) {
    animals.push_back(animal);
    grid[animal->getY()][animal->getX()] = 1;
}

void World::update() {
    for (auto& animal : animals) {
        int oldX = animal->getX();
        int oldY = animal->getY();

        animal->move(width, height);

        int newX = animal->getX();
        int newY = animal->getY();

        if (grid[newY][newX] == 0) { // Move only if the new cell is empty
            grid[oldY][oldX] = 0;
            grid[newY][newX] = 1;
        } else {
            animal->setPosition(oldX, oldY); // Revert move if new position is occupied
        }
    }
}

void World::dealDamageToAnimal(int index, int damage) {
    if (index < 0 || index >= animals.size()) return;

    if (animals[index]->take_dmg(damage)) {
        // Remove animal from the grid and the vector
        grid[animals[index]->getY()][animals[index]->getX()] = 0;
        animals.erase(animals.begin() + index);
    }
}