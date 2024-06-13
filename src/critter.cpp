#include "critter.h"

// critter functions

critter::critter(int x, int y, int hp, const std::initializer_list<std::string>& textureFiles)
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
    if (worldWidth > 0 && worldHeight > 0) {
    switch (direction) {
    case 0: newX = (x + 1) % worldWidth; break;
    case 1: newX = (x - 1 + worldWidth) % worldWidth; break;
    case 2: newY = (y + 1) % worldHeight; break;
    case 3: newY = (y - 1 + worldHeight) % worldHeight; break;
    }
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

harv_crit::harv_crit(int x, int y, int hp, const std::initializer_list<std::string>& textureFiles)
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
bool harv_crit::if_collected_today()
{
    return collected_today;
}
void harv_crit::set_collected_today(bool a)
{
    collected_today=a;
}

cow::cow(int x, int y)
    : harv_crit(x, y, 20, {"../assets/grafika_zwierzeta/cow_walk.png"}) {
    loadAnimation("../assets/grafika_zwierzeta/cow_walk.png", 15,15); // Ustaw odpowiednią ścieżkę do pliku
}

cow::~cow() {}



void cow::loadAnimation(const std::string& file, int frameWidth, int frameHeight) {
    sf::Texture texture;
    if (!texture.loadFromFile(file)) {
        std::cerr << "Error loading texture from file: " << file << std::endl;
        return;  // Dodajemy return, aby uniknąć dalszego przetwarzania w przypadku błędu
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

void cow::updateAnimation() {
    if (animationClock.getElapsedTime().asSeconds() > 0.1f) {
        currentFrame = (currentFrame + 1) % 4 + direction * 4;
        sprite.setTextureRect(animationFrames[currentFrame]);
        animationClock.restart();
    }
}

void cow::move(float offsetX, float offsetY) {
    sprite.move(offsetX, offsetY);
    updateAnimation();
}

void critter::randomMove(float deltaTime) {
    float speed = 100.0f; // Example speed
    if (moveTime <= 0) {
        direction = std::rand() % 4;
        moveDuration = (std::rand() % 3) + 1; // Move for 1 to 3 seconds
        moveTime = moveDuration;
    }

    float moveX = 0, moveY = 0;

    switch (direction) {
    case 0: moveX = speed * deltaTime; break; // Move right
    case 1: moveX = -speed * deltaTime; break; // Move left
    case 2: moveY = speed * deltaTime; break; // Move down
    case 3: moveY = -speed * deltaTime; break; // Move up
    }

    sf::Vector2f position = sprite.getPosition();

    if (position.x + moveX < 0 || position.x + moveX > 800 - sprite.getGlobalBounds().width) {
        moveX = -moveX; // Reverse direction if hitting the left or right edge
        direction = (direction == 0) ? 1 : (direction == 1) ? 0 : direction;
    }
    if (position.y + moveY < 0 || position.y + moveY > 600 - sprite.getGlobalBounds().height) {
        moveY = -moveY; // Reverse direction if hitting the top or bottom edge
        direction = (direction == 2) ? 3 : (direction == 3) ? 2 : direction;
    }

    move(moveX, moveY);

    moveTime -= deltaTime;
}

sheep::sheep(int x, int y) : harv_crit(x, y, 25, {"../assets/grafika_zwierzeta/sheep_walk.png"}) {
    loadAnimation("../assets/grafika_zwierzeta/sheep_walk.png", 15, 15); // Ustaw odpowiednią ścieżkę do pliku
}

sheep::~sheep() {}

void sheep::loadAnimation(const std::string& file, int frameWidth, int frameHeight) {
    sf::Texture texture;
    if (!texture.loadFromFile(file)) {
        std::cerr << "Error loading texture from file: " << file << std::endl;
        return;  // Dodajemy return, aby uniknąć dalszego przetwarzania w przypadku błędu
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

void sheep::updateAnimation() {
    if (animationClock.getElapsedTime().asSeconds() > 0.1f) {
        currentFrame = (currentFrame + 1) % 4 + direction * 4;
        sprite.setTextureRect(animationFrames[currentFrame]);
        animationClock.restart();
    }
}

void sheep::move(float offsetX, float offsetY) {
    sprite.move(offsetX, offsetY);
    updateAnimation();
}


// non_harv_crit functions

non_harv_crit::non_harv_crit(int x, int y, int hp, const std::initializer_list<std::string>& textureFiles)
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
    : non_harv_crit(x, y, 25, {"../assets/grafika_zwierzeta/chicken_walk.png"}) {
    loadAnimation("../assets/grafika_zwierzeta/chicken_walk.png", 18, 18); // Ustaw odpowiednią ścieżkę do pliku
}

chicken::~chicken() {}

void chicken::loadAnimation(const std::string& file, int frameWidth, int frameHeight) {
    sf::Texture texture;
    if (!texture.loadFromFile(file)) {
        std::cerr << "Error loading texture from file: " << file << std::endl;
        return;  // Dodajemy return, aby uniknąć dalszego przetwarzania w przypadku błędu
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
        currentFrame = (currentFrame + 1) % 4 + direction * 4;
        sprite.setTextureRect(animationFrames[currentFrame]);
        animationClock.restart();
    }
}

void chicken::move(float offsetX, float offsetY) {
    sprite.move(offsetX, offsetY);
    updateAnimation();
}





pig::pig(int x, int y) : non_harv_crit(x, y, 25, {"../assets/grafika_zwierzeta/pig_walk.png"}) {
    loadAnimation("../assets/grafika_zwierzeta/pig_walk.png", 15, 15); // Ustaw odpowiednią ścieżkę do pliku
}

pig::~pig() {}

void pig::loadAnimation(const std::string& file, int frameWidth, int frameHeight) {
    sf::Texture texture;
    if (!texture.loadFromFile(file)) {
        std::cerr << "Error loading texture from file: " << file << std::endl;
        return;  // Dodajemy return, aby uniknąć dalszego przetwarzania w przypadku błędu
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

void pig::updateAnimation() {
    if (animationClock.getElapsedTime().asSeconds() > 0.1f) {
        currentFrame = (currentFrame + 1) % 4 + direction * 4;
        sprite.setTextureRect(animationFrames[currentFrame]);
        animationClock.restart();
    }
}

void pig::move(float offsetX, float offsetY) {
    sprite.move(offsetX, offsetY);
    updateAnimation();
}

