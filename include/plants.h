#ifndef PLANT_H
#define PLANT_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Plant {
public:
    Plant(int x, int y, const std::string& textureFile);
    virtual ~Plant();
    void update(int dayCounter);
    void draw(sf::RenderWindow& window);
    bool isReadyForHarvest() const;
    bool harvest();

protected:
    int x, y;
    int currentDay;
    int growthStage;
    bool readyForHarvest;
    std::vector<sf::Texture> textures;
    sf::Sprite sprite;
    void loadTextures(const std::string& textureFile);
};

class Carrot : public Plant {
public:
    Carrot(int x, int y);
    ~Carrot();
};

class Potato : public Plant {
public:
    Potato(int x, int y);
    ~Potato();
};

#endif // PLANT_H
