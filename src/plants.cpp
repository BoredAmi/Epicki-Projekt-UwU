#include "plants.h"

#include <iostream>

Plant::Plant(int x, int y, const std::string& textureFile)
    : x(x), y(y), currentDay(0), growthStage(0), readyForHarvest(false) {
    loadTextures(textureFile);
    sprite.setTexture(this->textures[0]);
    sprite.setPosition(static_cast<float>(x), static_cast<float>(y));
}

Plant::~Plant() {}

void Plant::update(int dayCounter) {
    if (dayCounter - currentDay >= 2) {
        currentDay = dayCounter;
        growthStage++;
        if (growthStage < textures.size()) {
            sprite.setTexture(textures[growthStage]);
        }
        if (growthStage >= 4) {
            readyForHarvest = true;
        }
    }
}

void Plant::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

bool Plant::isReadyForHarvest() const {
    return readyForHarvest;
}

bool Plant::harvest() {
    if (readyForHarvest) {

        growthStage = 0;
        readyForHarvest = false;
        sprite.setTexture(textures[growthStage]);
        return true;
    }
    return false;
}

void Plant::loadTextures(const std::string& textureFile) {
    sf::Image image;
    if (!image.loadFromFile(textureFile)) {
        std::cerr << "Error loading texture from file: " << textureFile << std::endl;
        return;
    }

    int width = 16;
    int height = 16;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 3; ++j) {
            sf::Texture texture;
            texture.loadFromImage(image, sf::IntRect(j * width, i * height, width, height));
            textures.push_back(texture);
        }
    }
}

Carrot::Carrot(int x, int y)
    : Plant(x, y, "pa2.png") {}

Carrot::~Carrot() {}

Potato::Potato(int x, int y)
    : Plant(x, y, "pa2.png") {}

Potato::~Potato() {}
