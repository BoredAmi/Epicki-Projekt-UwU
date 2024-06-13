#include <iostream>
#include <vector>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <random>
#include <algorithm>
#include "world.h"
#include "player.h"
#include <SFML/Audio.hpp>
#include "critter.h"

// Simplex Noise implementation
class SimplexNoise1 {
private:
    std::vector<int> p;
    std::vector<int> permutation;

    double fade(double t) {
        return t * t * t * (t * (t * 6 - 15) + 10);
    }

    double lerp(double t, double a, double b) {
        return a + t * (b - a);
    }

    double grad(int hash, double x, double y) {
        int h = hash & 7;
        double u = h < 4 ? x : y;
        double v = h < 4 ? y : x;
        return ((h & 1) ? -u : u) + ((h & 2) ? -2.0 * v : 2.0 * v);
    }

public:
    SimplexNoise1(unsigned int seed = std::random_device{}()) {
        p = {151, 160, 137, 91, 90, 15, 131, 13, 201, 95, 96, 53, 194, 233, 7, 225, 140, 36, 103, 30, 69, 142, 8, 99, 37, 240, 21, 10, 23, 190, 6, 148, 247, 120, 234, 75, 0, 26, 197, 62, 94, 252, 219, 203, 117, 35, 11, 32, 57, 177, 33, 88, 237, 149, 56, 87, 174, 20, 125, 136, 171, 168, 68, 175, 74, 165, 71, 134, 139, 48, 27, 166, 77, 146, 158, 231, 83, 111, 229, 122, 60, 211, 133, 230, 220, 105, 92, 41, 55, 46, 245, 40, 244, 102, 143, 54, 65, 25, 63, 161, 1, 216, 80, 73, 209, 76, 132, 187, 208, 89, 18, 169, 200, 196, 135, 130, 116, 188, 159, 86, 164, 100, 109, 198, 173, 186, 3, 64, 52, 217, 226, 250, 124, 123, 5, 202, 38, 147, 118, 126, 255, 82, 85, 212, 207, 206, 59, 227, 47, 16, 58, 17, 182, 189, 28, 42, 223, 183, 170, 213, 119, 248, 152, 2, 44, 154, 163, 70, 221, 153, 101, 155, 167, 43, 172, 9, 129, 22, 39, 253, 19, 98, 108, 110, 79, 113, 224, 232, 178, 185, 112, 104, 218, 246, 97, 228, 251, 34, 242, 193, 238, 210, 144, 12, 191, 179, 162, 241, 81, 51, 145, 235, 249, 14, 239, 107, 49, 192, 214, 31, 181, 199, 106, 157, 184, 84, 204, 176, 115, 121, 50, 45, 127, 4, 150, 254, 138, 236, 205, 93, 222, 114, 67, 29, 24, 72, 243, 141, 128, 195, 78, 66, 215, 61, 156, 180};
        std::mt19937 engine(seed); // Mersenne twister engine
        std::shuffle(p.begin(), p.end(), engine);

        permutation.insert(permutation.end(), p.begin(), p.end());
        permutation.insert(permutation.end(), p.begin(), p.end());
    }

    double noise(double x, double y) {
        double F2 = 0.5 * (sqrt(3.0) - 1.0);
        double G2 = (3.0 - sqrt(3.0)) / 6.0;

        double s = (x + y) * F2;
        int i = floor(x + s);
        int j = floor(y + s);

        double t = (i + j) * G2;
        double X0 = i - t;
        double Y0 = j - t;
        double x0 = x - X0;
        double y0 = y - Y0;

        int i1, j1;
        if (x0 > y0) {
            i1 = 1;
            j1 = 0;
        } else {
            i1 = 0;
            j1 = 1;
        }

        double x1 = x0 - i1 + G2;
        double y1 = y0 - j1 + G2;
        double x2 = x0 - 1.0 + 2.0 * G2;
        double y2 = y0 - 1.0 + 2.0 * G2;

        int ii = i & 255;
        int jj = j & 255;
        int gi0 = permutation[ii + permutation[jj]] % 12;
        int gi1 = permutation[ii + i1 + permutation[jj + j1]] % 12;
        int gi2 = permutation[ii + 1 + permutation[jj + 1]] % 12;

        double n0, n1, n2;

        double t0 = 0.5 - x0 * x0 - y0 * y0;
        if (t0 < 0) {
            n0 = 0.0;
        } else {
            t0 *= t0;
            n0 = t0 * t0 * grad(gi0, x0, y0);
        }

        double t1 = 0.5 - x1 * x1 - y1 * y1;
        if (t1 < 0) {
            n1 = 0.0;
        } else {
            t1 *= t1;
            n1 = t1 * t1 * grad(gi1, x1, y1);
        }

        double t2 = 0.5 - x2 * x2 - y2 * y2;
        if (t2 < 0) {
            n2 = 0.0;
        } else {
            t2 *= t2;
            n2 = t2 * t2 * grad(gi2, x2, y2);
        }

        return 70.0 * (n0 + n1 + n2);
    }
};

int game_window(sf::Music& backgroundMusic, bool& isMuted) {
    const int width = 100;
    const int height = 100;

    SimplexNoise1 noise(122);

    // Generate water values
    std::vector<std::vector<double>> waterGrid(width, std::vector<double>(height));
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            double nx = static_cast<double>(x) / width - 0.5;
            double ny = static_cast<double>(y) / height - 0.5;
            waterGrid[x][y] = noise.noise(8 * nx, 8 * ny);
        }
    }

    // Generate land values
    std::vector<std::vector<double>> landGrid(width, std::vector<double>(height));
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            double nx = static_cast<double>(x) / width - 0.5;
            double ny = static_cast<double>(y) / height - 0.5;
            landGrid[x][y] = noise.noise(8 * nx, 8 * ny);
        }
    }

    // Display water and land values using SFML
    sf::RenderWindow window(sf::VideoMode(800, 600), "Simplex Noise");

    // Define the player's position and shape
    sf::Vector2f playerPosition(width * 4, height * 4);

    sf::Texture playerTexture;
    if (!playerTexture.loadFromFile("../assets/player.png")) {
        std::cerr << "Error loading player texture" << std::endl;
        return -1;
    }

    sf::Sprite player(playerTexture);
    player.setOrigin(playerTexture.getSize().x / 2.0f, playerTexture.getSize().y / 2.0f);
    player.setPosition(playerPosition);

    // Load textures for land and water
    sf::Texture landTexture;
    if (!landTexture.loadFromFile("../assets/grass.jpg")) {
        std::cerr << "Error loading land texture" << std::endl;
        return -1;
    }

    sf::Texture waterTexture;
    if (!waterTexture.loadFromFile("../assets/water.jpeg")) {
        std::cerr << "Error loading water texture" << std::endl;
        return -1;
    }

    // Create animal instances
    std::vector<std::shared_ptr<critter>> animals;
animals.push_back(std::make_shared<cow>(10, 10));
animals.push_back(std::make_shared<chicken>(20, 20));
animals.push_back(std::make_shared<pig>(30, 30));
animals.push_back(std::make_shared<sheep>(40, 40));
animals.push_back(std::make_shared<cow>(50, 50));
animals.push_back(std::make_shared<chicken>(60, 60));
animals.push_back(std::make_shared<pig>(70, 70));
animals.push_back(std::make_shared<sheep>(80, 80));
    // Create a view centered around the player
    sf::View view(sf::FloatRect(0, 0, 100, 100));
    view.setCenter(playerPosition);
    window.setView(view);

while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        // Handle player movement
        if (event.type == sf::Event::KeyPressed) {
            sf::Vector2f newPosition = playerPosition;
            if (event.key.code == sf::Keyboard::Up) {
                newPosition.y -= 8;
            }
            if (event.key.code == sf::Keyboard::Down) {
                newPosition.y += 8;
            }
            if (event.key.code == sf::Keyboard::Left) {
                newPosition.x -= 8;
            }
            if (event.key.code == sf::Keyboard::Right) {
                newPosition.x += 8;
            }

            // Wrap around the map
            if (newPosition.x < 0) newPosition.x += width * 8;
            if (newPosition.x >= width * 8) newPosition.x -= width * 8;
            if (newPosition.y < 0) newPosition.y += height * 8;
            if (newPosition.y >= height * 8) newPosition.y -= height * 8;

            // Check if the new position is on water
            int gridX = static_cast<int>(newPosition.x) / 8;
            int gridY = static_cast<int>(newPosition.y) / 8;
            if (waterGrid[gridX][gridY] >= 0) {
                playerPosition = newPosition; // Update player position only if not on water
            }
            player.setPosition(playerPosition); // Update player position
        }
    }

    // Update the view center to match the player's position
    view.setCenter(playerPosition);
    window.setView(view);

    window.clear();

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            sf::Sprite tileSprite;
            tileSprite.setPosition(x * 8, y * 8);  // Adjust position to scale up the world
            if (waterGrid[x][y] < 0) {
                tileSprite.setTexture(waterTexture);
            } else {
                tileSprite.setTexture(landTexture);
            }
            window.draw(tileSprite);
        }
    }

    // Update and draw the animals
    for (auto& animal : animals) {
        animal->randomMove(0.1f); // Example deltaTime, adjust as needed
        animal->draw(window);
    }

    // Draw the player
    window.draw(player);

    window.display();
}

    return 0;
}