#include <SFML/Graphics.hpp>
#include "world.h"
#include "critter.h"
#include "items.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Window");

    while (window.isOpen()) {   
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Red);
        // Draw something here
        window.display();
    }

    return 0;
}
