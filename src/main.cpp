#include <SFML/Graphics.hpp>
#include <iostream>
#include "menu.h"
#include "world.h"
#include "player.h"
#include <SFML/Audio.hpp>

// Forward declaration of the game_window function
int game_window(sf::Music& backgroundMusic, bool& isMuted);

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Menu Gry");
    window.setFramerateLimit(60);

    Menu menu(window.getSize().x, window.getSize().y);

    // Load background texture
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("../assets/8546617.jpg")) {
        std::cerr << "Nie można załadować pliku background.png";
        return -1;
    }
    sf::Sprite backgroundSprite;
    backgroundSprite.setTexture(backgroundTexture);
    menu.setBackgroundTexture(backgroundTexture, window.getSize().x, window.getSize().y);

    // Load background music
    sf::Music backgroundMusic;
    if (!backgroundMusic.openFromFile("../assets/In the Forest - Ambient Acoustic Guitar Instrumental BAckground Music.ogg")) {
        std::cerr << "Nie można załadować pliku background.ogg";
        return -1;
    }
    backgroundMusic.setLoop(true);
    backgroundMusic.play();

    bool isMuted = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up) {
                    menu.moveUp();
                }
                if (event.key.code == sf::Keyboard::Down) {
                    menu.moveDown();
                }
                if (event.key.code == sf::Keyboard::Return) {
                    if (menu.isStartSelected()) {
                        window.close();  // Close the menu window
                        return game_window(backgroundMusic, isMuted);  // Start the game
                    }
                    menu.select(backgroundMusic);
                }
                if (event.key.code == sf::Keyboard::BackSpace) {
                    menu.back();
                }
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    float x = static_cast<float>(event.mouseButton.x);
                    float y = static_cast<float>(event.mouseButton.y);
                    menu.handleClick(x, y, backgroundMusic, isMuted);
                }
            }
        }

        window.clear();
        window.draw(backgroundSprite);
        menu.draw(window);
        window.display();
    }

    return 0;
}

