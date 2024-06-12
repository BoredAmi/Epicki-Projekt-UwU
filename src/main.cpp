#include <SFML/Graphics.hpp>
#include <iostream>
#include <windows.h>
#include "menu.h"

#include <SFML/Audio.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Menu Gry");
    window.setFramerateLimit(60);

    Menu menu(window.getSize().x, window.getSize().y);

    // Wczytaj teksturę tła
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("C:/Users/pwsmi/OneDrive/Pulpit/nienazwane2/8546617.jpg")) {
        std::cerr<<"Nie można załadować pliku background.png";
        return -1;
    }

    // Utwórz sprite tła
    sf::Sprite backgroundSprite;
    backgroundSprite.setTexture(backgroundTexture);
    menu.setBackgroundTexture(backgroundTexture, window.getSize().x, window.getSize().y);
    // Wczytaj muzykę
    sf::Music backgroundMusic;
    if (!backgroundMusic.openFromFile("C:/Users/pwsmi/OneDrive/Pulpit/nienazwane2/In the Forest - Ambient Acoustic Guitar Instrumental BAckground Music.ogg")) {
        std::cerr<<"Nie można załadować pliku background.ogg";
        return -1;
    }
    backgroundMusic.setLoop(true); // Muzyka będzie odtwarzana w pętli
    backgroundMusic.play(); // Rozpocznij odtwarzanie muzyki

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
                    menu.select(backgroundMusic); // Wywołanie metody select() po naciśnięciu Enter
                }
                if (event.key.code == sf::Keyboard::BackSpace) {
                    menu.back(); // Wywołanie metody back() po naciśnięciu Backspace
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
       // Ustawienie aktualnej tekstury tła
        window.draw(backgroundSprite); // Rysowanie tła
        menu.draw(window);            // Rysowanie menu
        window.display();
    }



    return 0;


}

