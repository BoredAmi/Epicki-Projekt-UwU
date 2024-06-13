#include "critter.h"

// critter functions

critter::critter(int x, int y, int hp, const std::vector<std::string>& textureFiles)
    : entity(x, y, hp), currentTextureIndex(0) {
    for (const auto& file : textureFiles) {
        sf::Texture texture;
        if (!texture.loadFromFile(file)) {
            std::cerr << "Error loading texture from file: " << file << std::endl;
        }
        textures.push_back(texture);
    }
    sprite.setTexture(textures[currentTextureIndex]);
    sprite.setPosition(static_cast<float>(x), static_cast<float>(y));
}

critter::~critter() {
    std::cout << "Animal at (" << x << ", " << y << ") destroyed.\n";
}

void critter::move(int worldWidth, int worldHeight) {
    int direction = std::rand() % 4;
    int newX = x;
    int newY = y;

    switch (direction) {
    case 0: newX = (x + 1) % worldWidth; break;
    case 1: newX = (x - 1 + worldWidth) % worldWidth; break;
    case 2: newY = (y + 1) % worldHeight; break;
    case 3: newY = (y - 1 + worldHeight) % worldHeight; break;
    }

    x = newX;
    y = newY;
    sprite.setPosition(static_cast<float>(x), static_cast<float>(y));

    currentTextureIndex = (currentTextureIndex + 1) % textures.size();
    sprite.setTexture(textures[currentTextureIndex]);
}

bool critter::take_dmg(int dmg) {
    hp -= dmg;
    return hp < 0;
}

void critter::draw(sf::RenderWindow &window) {
    window.draw(sprite);
}

// harv_crit functions

harv_crit::harv_crit(int x, int y, int hp, const std::vector<std::string>& textureFiles)
    : critter(x, y, hp, textureFiles), collected_today(false), harvest_count(0) {}

harv_crit::~harv_crit() {}

bool harv_crit::harvest() {
    if (!collected_today) {
        collected_today = true;
        ++harvest_count;
        return true;
    }
    return false;
}

int harv_crit::getHarvestCount() const {
    return harvest_count;
}

void harv_crit::resetDailyState() {
    collected_today = false;
}

cow::cow(int x, int y) : harv_crit(x, y, 20, {"path/to/cow_texture1.png", "path/to/cow_texture2.png"}) {}

cow::~cow() {}

sheep::sheep(int x, int y) : harv_crit(x, y, 25, {"path/to/sheep_texture1.png", "path/to/sheep_texture2.png"}) {}

sheep::~sheep() {}

// non_harv_crit functions

non_harv_crit::non_harv_crit(int x, int y, int hp, const std::vector<std::string>& textureFiles)  // Poprawiona definicja
    : critter(x, y, hp, textureFiles), collected_today(false), harvest_count(0) {}

non_harv_crit::~non_harv_crit() {}

bool non_harv_crit::harvest() {
    if (!collected_today) {
        collected_today = true;
        ++harvest_count;
        return true;
    }
    return false;
}

int non_harv_crit::getHarvestCount() const {
    return harvest_count;
}

void non_harv_crit::resetDailyState() {
    collected_today = false;
}

chicken::chicken(int x, int y)
    : non_harv_crit(x, y, 15, {"nienazwane2/grafika_zwierzeta/chicken_walk.png"}), currentFrame(0) {
    loadAnimation("nienazwane2/grafika_zwierzeta/chicken_walk.png", 32, 32);
}

chicken::~chicken() {}

void chicken::loadAnimation(const std::string& file, int frameWidth, int frameHeight) {
    sf::Texture texture;
    if (!texture.loadFromFile(file)) {
        std::cerr << "Error loading texture from file: " << file << std::endl;
    }
    textures.push_back(texture);
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            animationFrames.emplace_back(j * frameWidth, i * frameHeight, frameWidth, frameHeight);
        }
    }
    sprite.setTexture(textures[0]);
    sprite.setTextureRect(animationFrames[0]);
}

void chicken::updateAnimation() {
    if (animationClock.getElapsedTime().asSeconds() > 0.1f) {
        currentFrame = (currentFrame + 1) % animationFrames.size();
        sprite.setTextureRect(animationFrames[currentFrame]);
        animationClock.restart();
    }
}


pig::pig(int x, int y) : non_harv_crit(x, y, 25, {"path/to/pig_texture1.png", "path/to/pig_texture2.png"}) {}

pig::~pig() {}
