#include "world.h"
std::vector<std::vector<tiles>> generateWorld(int width, int height, const PerlinNoise& noise) {
    std::vector<std::vector<tiles>> world(width, std::vector<tiles>(height, tiles(tile_types::land)));
    double scale = 100.0; // Adjust scale for different terrain features

    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            double nx = static_cast<double>(x) / scale;
            double ny = static_cast<double>(y) / scale;
            double elevation = noise.noise(nx, ny);

            if (elevation < 0.5) {
                world[x][y] = tiles(tile_types::water);
            } else {
                world[x][y] = tiles(tile_types::land);
            }
        }
    }
    return world;
}

tiles::tiles(tile_types type) : tile_type(type), occupation(false) {}

tiles::~tiles() {}

bool tiles::change_type(tile_types type) {
    tile_type = type;
    return true;
}

World::World(int width, int height) : width(width), height(height), grid(generateWorld(width, height, PerlinNoise())) {}

void World::addAnimal(std::shared_ptr<critter> animal) {
    animals.push_back(animal);
    grid[animal->getY()][animal->getX()].occupation = 1;
}

void World::update() {
    for (auto& animal : animals) {
        int oldX = animal->getX();
        int oldY = animal->getY();

        animal->move(width, height);

        int newX = animal->getX();
        int newY = animal->getY();

        if (grid[newY][newX].occupation == 0) { // Move only if the new cell is empty
            grid[oldY][oldX].occupation = 0;
            grid[newY][newX].occupation = 1;
        } else {
            animal->setPosition(oldX, oldY); // Revert move if new position is occupied
        }
    }
}

void World::dealDamageToAnimal(int index, int damage) {
    if (index < 0 || index >= animals.size()) return;

    if (animals[index]->take_dmg(damage)) {
        // Remove animal from the grid and the vector
        grid[animals[index]->getY()][animals[index]->getX()].occupation = 0;
        animals.erase(animals.begin() + index);
    }
}
