#include "world.h"
#include "gathering.h"
#include <random>

std::vector<std::vector<tiles>> generateWorld(int width, int height, SimplexNoise& noise) {
    std::vector<std::vector<tiles>> world(width, std::vector<tiles>(height, tiles(tile_types::land)));
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 100);

    // Generate water values
    std::vector<std::vector<double>> waterGrid(width, std::vector<double>(height));
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            double nx = static_cast<double>(x) / width - 0.5;
            double ny = static_cast<double>(y) / height - 0.5;
            waterGrid[x][y] = noise.noise(nx, ny);
        }
    }
    // Generate land values
    std::vector<std::vector<double>> landGrid(width, std::vector<double>(height));
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            double nx = static_cast<double>(x) / width - 0.5;
            double ny = static_cast<double>(y) / height - 0.5;
            landGrid[x][y] = noise.noise(nx, ny);
        }
    }
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) 
        {
            if (waterGrid[x][y] < 0) {
                world[x][y].change_type(tile_types::water);
                
            } else {
                world[x][y].change_type(tile_types::land);
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
void tiles::change_occupation() {
    occupation = !occupation;
}
void tiles::addEntity(std::unique_ptr<entity> entity) {
    ;
}
World::World(int width, int height) : width(width), height(height) {
    SimplexNoise noise;
    grid = generateWorld(width, height, noise);}

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
