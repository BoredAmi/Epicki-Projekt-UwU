#include <SFML/Graphics.hpp>
#include "world.h"
#include "player.h"

const int WIDTH = 800;
const int HEIGHT = 600;
const int TILE_SIZE = 10;

void drawMap(sf::RenderWindow& window, const std::vector<std::vector<tiles>>& world, const sf::View& camera);

int main() {
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Open World Game");
    window.setFramerateLimit(60);

    Player player(WIDTH / 2, HEIGHT / 2, 0.1f);
    sf::View camera;
    camera.setSize(WIDTH, HEIGHT);
    camera.setCenter(player.position);

    World world(100, 100); // Example world size

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Handle player movement
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) player.move(0, -1);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) player.move(0, 1);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) player.move(-1, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) player.move(1, 0);

        camera.setCenter(player.position);

        window.clear();
        window.setView(camera);
        drawMap(window, world.grid, camera);
        window.display();
    }

    return 0;
}

void drawMap(sf::RenderWindow& window, const std::vector<std::vector<tiles>>& world, const sf::View& camera) {
    sf::FloatRect viewBounds(
        camera.getCenter().x - camera.getSize().x / 2,
        camera.getCenter().y - camera.getSize().y / 2,
        camera.getSize().x,
        camera.getSize().y);

    int startX = std::max(0, static_cast<int>(viewBounds.left / TILE_SIZE));
    int startY = std::max(0, static_cast<int>(viewBounds.top / TILE_SIZE));
    int endX = std::min(static_cast<int>(world.size()), startX + static_cast<int>(viewBounds.width / TILE_SIZE) + 1);
    int endY = std::min(static_cast<int>(world[0].size()), startY + static_cast<int>(viewBounds.height / TILE_SIZE) + 1);

    for (int x = startX; x < endX; ++x) {
        for (int y = startY; y < endY; ++y) {
            sf::RectangleShape tileShape(sf::Vector2f(TILE_SIZE, TILE_SIZE));
            tileShape.setPosition(x * TILE_SIZE, y * TILE_SIZE);

            switch (world[x][y].tile_type) {
                case land:
                    tileShape.setFillColor(sf::Color::Green);
                    break;
                case plowed:
                    tileShape.setFillColor(sf::Color(139, 69, 19)); // Brown color
                    break;
                case water:
                    tileShape.setFillColor(sf::Color::Blue);
                    break;
            }

            window.draw(tileShape);
        }
    }
}
void hpBar(sf::RenderWindow& window, Player& player) {
    //draw hp bar
    sf::RectangleShape hpBar;
    hpBar.setSize(sf::Vector2f(player.getHp(), 10));
    hpBar.setFillColor(sf::Color::Red);
    hpBar.setPosition(10, 10);
    window.draw(hpBar);
}
void energyBar(sf::RenderWindow& window, Player& player) {
    //draw energy bar
    sf::RectangleShape energyBar;
    energyBar.setSize(sf::Vector2f(player.getEnergy(), 10));
    energyBar.setFillColor(sf::Color::Yellow);
    energyBar.setPosition(10, 30);
    window.draw(energyBar);
}
void saveToFile() {
    //save all data to a file

}
void loadFromFile() {
    //load all data from a file

}
