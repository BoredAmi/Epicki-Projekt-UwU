#include "menu.h"
#include <iostream>
#include <SFML/Audio.hpp>
bool Menu::isStartSelected() {
    return (state == 0 && selectedItemIndex == 0);
}
Menu::Menu(float width, float height) : state(0) {
    if (!font.loadFromFile("../assets/Jacquard12-Regular.ttf")) {
        std::cerr << "Nie można załadować czcionki" << std::endl;
    }

    float menuHeight = height / 4.0f;

    // Inicjalizacja głównego menu
    for (int i = 0; i < 3; ++i) {
        sf::RectangleShape background(sf::Vector2f(width / 3.0f, menuHeight - 20.0f));
        background.setFillColor(sf::Color(245, 245, 220, 200));
        background.setOutlineColor(sf::Color::Black);
        background.setOrigin(background.getSize().x / 2.0f, background.getSize().y / 2.0f);
        background.setPosition(width / 2.0f, menuHeight * (i + 1));
        menuBackgrounds.push_back(background);

        menu[i].setFont(font);
        menu[i].setFillColor(i == 0 ? sf::Color::Black : sf::Color(128, 128, 128));
        menu[i].setCharacterSize(34);
    }

    menu[0].setString("Start");
    menu[1].setString("Options");
    menu[2].setString("Exit");

    for (int i = 0; i < 3; ++i) {
        centerText(menu[i], width, height, i + 1);
    }




    // Inicjalizacja menu opcji
    for (int i = 0; i < 3; ++i) {
        sf::RectangleShape background(sf::Vector2f(width / 3.0f, menuHeight - 20.0f));
        background.setFillColor(sf::Color(245, 245, 220, 200));
        background.setOutlineThickness(2);
        background.setOutlineColor(sf::Color::Black);
        background.setOrigin(background.getSize().x / 2.0f, background.getSize().y / 2.0f);
        background.setPosition(width / 2.0f, menuHeight * (i + 1));
        optionsBackgrounds.push_back(background);

        options[i].setFont(font);
        options[i].setFillColor(i == 0 ? sf::Color::Black : sf::Color(128, 128, 128));
        options[i].setCharacterSize(34);
    }

    options[0].setString("Resolution");
    options[1].setString("Sound");
    options[2].setString("Controls");

    for (int i = 0; i < 3; ++i) {
        centerText(options[i], width, height, i + 1);
    }

    // Inicjalizacja menu rozdzielczości
    std::vector<std::string> resolutionOptions = { "800x600", "1024x768", "1280x720" };
    for (int i = 0; i < 3; ++i) {
        sf::RectangleShape background(sf::Vector2f(width / 3.0f, menuHeight - 20.0f));
        background.setFillColor(sf::Color(245, 245, 220, 200));
        background.setOutlineThickness(2);
        background.setOutlineColor(sf::Color::Black);
        background.setOrigin(background.getSize().x / 2.0f, background.getSize().y / 2.0f);
        background.setPosition(width / 2.0f, menuHeight * (i + 1));
        resolutionBackgrounds.push_back(background);

        resolutions[i].setFont(font);
        resolutions[i].setString(resolutionOptions[i]);
        resolutions[i].setFillColor(i == 0 ? sf::Color::Black : sf::Color(128, 128, 128));
        resolutions[i].setCharacterSize(34);
        centerText(resolutions[i], width, height, i + 1);
    }

    // Inicjalizacja menu controls
    std::vector<std::string> controlOptions = { "Background 1", "Background 2", "Background 3" };
    for (int i = 0; i < 3; ++i) {
        sf::RectangleShape background(sf::Vector2f(width / 3.0f, menuHeight - 20.0f));
        background.setFillColor(sf::Color(245, 245, 220, 200));
        background.setOutlineThickness(2);
        background.setOutlineColor(sf::Color::Black);
        background.setOrigin(background.getSize().x / 2.0f, background.getSize().y / 2.0f);
        background.setPosition(width / 2.0f, menuHeight * (i + 1));
        controlsBackgrounds.push_back(background);

        controls[i].setFont(font);
        controls[i].setString(controlOptions[i]);
        controls[i].setFillColor(i == 0 ? sf::Color::Black : sf::Color(128, 128, 128));
        controls[i].setCharacterSize(34);
        centerText(controls[i], width, height, i + 1);
    }

    std::vector<std::string> volumeOptions = { "Low", "Medium", "High" };
    for (int i = 0; i < 3; ++i) {
        sf::RectangleShape background(sf::Vector2f(width / 3.0f, menuHeight - 20.0f));
        background.setFillColor(sf::Color(245, 245, 220, 200));
        background.setOutlineThickness(2);
        background.setOutlineColor(sf::Color::Black);
        background.setOrigin(background.getSize().x / 2.0f, background.getSize().y / 2.0f);
        background.setPosition(width / 2.0f, menuHeight * (i + 1));
        volumeBackgrounds.push_back(background);

        volumes[i].setFont(font);
        volumes[i].setString(volumeOptions[i]);
        volumes[i].setFillColor(i == 0 ? sf::Color::Red : sf::Color::White);
        volumes[i].setCharacterSize(24);
        centerText(volumes[i], width, height, i + 1);
    }
    muteButton.setSize(sf::Vector2f(50, 50));
    muteButton.setPosition(10, 10);

    if (!muteTextureOn.loadFromFile("../assets/glosnik2.png")) {
        std::cerr << "Nie można załadować pliku sound_on.png" << std::endl;
    }
    if (!muteTextureOff.loadFromFile("../assets/glosnik.png")) {
        std::cerr << "Nie można załadować pliku sound_off.png" << std::endl;
    }

    muteSprite.setTexture(muteTextureOn);
    muteSprite.setPosition(10, 10);
    muteSprite.setScale(0.25f, 0.25f);
    selectedItemIndex = 0;
}

void Menu::draw(sf::RenderWindow& window) {
    window.draw(muteSprite);
    if (state == 0) { // Główne menu

        for (int i = 0; i < 3; ++i) {
            if (i == selectedItemIndex) {
                menuBackgrounds[i].setFillColor(sf::Color(245, 245, 220, 200));
                menuBackgrounds[i].setOutlineColor(sf::Color::Black);
            } else {
                menuBackgrounds[i].setFillColor(sf::Color(255, 253, 208, 200));
                menuBackgrounds[i].setOutlineColor(sf::Color::White);
            }
            window.draw(menuBackgrounds[i]);
            window.draw(menu[i]);
        }
    } else if (state == 1) { // Menu opcji

        for (int i = 0; i < 3; ++i) {
            if (i == selectedItemIndex) {
                optionsBackgrounds[i].setFillColor(sf::Color(245, 245, 220, 200)); // Zmiana koloru tła na złoty
                optionsBackgrounds[i].setOutlineColor(sf::Color::Black); // Zmiana koloru ramki na czerwony
            } else {
                optionsBackgrounds[i].setFillColor(sf::Color(255, 253, 208, 200)); // Kremowy kolor z przezroczystością
                optionsBackgrounds[i].setOutlineColor(sf::Color::White); // Czarny kolor ramki
            }
            window.draw(optionsBackgrounds[i]); // Rysowanie tła dla opcji
            window.draw(options[i]);            // Rysowanie tekstu opcji
        }
    } else if (state == 2) { // Menu rozdzielczości

        for (int i = 0; i < 3; ++i) {
            if (i == selectedItemIndex) {
                resolutionBackgrounds[i].setFillColor(sf::Color(245, 245, 220, 200));
                resolutionBackgrounds[i].setOutlineColor(sf::Color::Black);
            } else {
                resolutionBackgrounds[i].setFillColor(sf::Color(255, 253, 208, 200));
                resolutionBackgrounds[i].setOutlineColor(sf::Color::White);
            window.draw(resolutionBackgrounds[i]);
            window.draw(resolutions[i]);
        }
    }
    } else if (state == 3) { // Menu controls

        for (int i = 0; i < 3; ++i) {
            if (i == selectedItemIndex) {
                controlsBackgrounds[i].setFillColor(sf::Color(245, 245, 220, 200));
                controlsBackgrounds[i].setOutlineColor(sf::Color::Black);
            } else {
                controlsBackgrounds[i].setFillColor(sf::Color(255, 253, 208, 200));
                controlsBackgrounds[i].setOutlineColor(sf::Color::White);
            }
            window.draw(controlsBackgrounds[i]);
            window.draw(controls[i]);
        }
    }else if (state == 4) { // Menu głośności

        for (int i = 0; i < 3; ++i) {
            if (i == selectedItemIndex) {
                volumeBackgrounds[i].setFillColor(sf::Color(255, 215, 0, 200));
                volumeBackgrounds[i].setOutlineColor(sf::Color::Red);
            } else {
                volumeBackgrounds[i].setFillColor(sf::Color(245, 245, 220, 200));
                volumeBackgrounds[i].setOutlineColor(sf::Color::Black);
            }
            window.draw(volumeBackgrounds[i]);
            window.draw(volumes[i]);
        }
    }
      window.draw(muteSprite);
}

void Menu::moveUp() {
    if (state == 0) {
        if (selectedItemIndex - 1 >= 0) {
            menu[selectedItemIndex].setFillColor(sf::Color(128,128,128));
            selectedItemIndex--;
            menu[selectedItemIndex].setFillColor(sf::Color::Black);
        }
    } else if (state == 1) {
        if (selectedItemIndex - 1 >= 0) {
            options[selectedItemIndex].setFillColor(sf::Color(128,128,128));
            selectedItemIndex--;
            options[selectedItemIndex].setFillColor(sf::Color::Black);
        }
    } else if (state == 2) {
        if (selectedItemIndex - 1 >= 0) {
            resolutions[selectedItemIndex].setFillColor(sf::Color(128,128,128));
            selectedItemIndex--;
            resolutions[selectedItemIndex].setFillColor(sf::Color::Black);
        }
    } else if (state == 3) {
        if (selectedItemIndex - 1 >= 0) {
            controls[selectedItemIndex].setFillColor(sf::Color(128,128,128));
            selectedItemIndex--;
            controls[selectedItemIndex].setFillColor(sf::Color::Black);
        }

    }else if (state == 4) {
        if (selectedItemIndex - 1 >= 0) {
            volumes[selectedItemIndex].setFillColor(sf::Color::White);
            selectedItemIndex--;
            volumes[selectedItemIndex].setFillColor(sf::Color::Red);
        }
    }
}

void Menu::moveDown() {
    if (state == 0) {
        if (selectedItemIndex + 1 < 3) {
            menu[selectedItemIndex].setFillColor(sf::Color(128,128,128));
            selectedItemIndex++;
            menu[selectedItemIndex].setFillColor(sf::Color::Black);
        }
    } else if (state == 1) {
        if (selectedItemIndex + 1 < 3) {
            options[selectedItemIndex].setFillColor(sf::Color(128,128,128));
            selectedItemIndex++;
            options[selectedItemIndex].setFillColor(sf::Color::Black);
        }
    } else if (state == 2) {
        if (selectedItemIndex + 1 < 3) {
            resolutions[selectedItemIndex].setFillColor(sf::Color(128,128,128));
            selectedItemIndex++;
            resolutions[selectedItemIndex].setFillColor(sf::Color::Black);
        }
    } else if (state == 3) {
        if (selectedItemIndex + 1 < 3) {
            controls[selectedItemIndex].setFillColor(sf::Color(128,128,128));
            selectedItemIndex++;
            controls[selectedItemIndex].setFillColor(sf::Color::Black);
        }
    }else if (state == 4) {
        if (selectedItemIndex + 1 < 3) {
            volumes[selectedItemIndex].setFillColor(sf::Color::White);
            selectedItemIndex++;
            volumes[selectedItemIndex].setFillColor(sf::Color::Red);
        }
    }
}

void Menu::select(sf::Music& backgroundMusic) {
    if (state == 0) {
        if (selectedItemIndex == 1) { // Options selected
            state = 1;
            selectedItemIndex = 0;
        }
    } else if (state == 1) {
        if (selectedItemIndex == 0) { // Resolution selected
            state = 2;
            selectedItemIndex = 0;
        } else if (selectedItemIndex == 1) { // Sound selected
            state = 4;
            selectedItemIndex = 0;
        } else if (selectedItemIndex == 2) { // Controls selected
            state = 3;
            selectedItemIndex = 0;
        }
    } else if (state == 2) {

        if (selectedItemIndex == 0) {
            // 800x600
        } else if (selectedItemIndex == 1) {
            // 1024x768
        } else if (selectedItemIndex == 2) {
            // 1280x720
        }
    } else if (state == 3) {

        if (selectedItemIndex == 0) {
            if (newBackgroundTexture.loadFromFile("../assets/images.jpg")) {
                setBackgroundTexture(newBackgroundTexture, 800, 600); // Dodaj szerokość i wysokość okna
            }
        } else if (selectedItemIndex == 1) {
            if (newBackgroundTexture.loadFromFile("../assets/istockphoto-1047558154-612x612.jpg")) {
                setBackgroundTexture(newBackgroundTexture, 800, 600); // Dodaj szerokość i wysokość okna
            }
        } else if (selectedItemIndex == 2) {
            if (newBackgroundTexture.loadFromFile("../assets/istockphoto-1317288349-612x612.jpg")) {
                setBackgroundTexture(newBackgroundTexture, 800, 600); // Dodaj szerokość i wysokość okna
            }
        }
    } else if (state == 4) {
        // Zmień głośność
        if (selectedItemIndex == 0) {
            backgroundMusic.setVolume(25); // Low
        } else if (selectedItemIndex == 1) {
            backgroundMusic.setVolume(50); // Medium
        } else if (selectedItemIndex == 2) {
            backgroundMusic.setVolume(75); // High
        }
    }
}
void Menu::back() {
    if (state == 1 || state == 2 || state == 3) { // Jeżeli jesteśmy w menu opcji, menu rozdzielczości lub menu controls
        state = (state == 1) ? 0 : 1; // Powrót do poprzedniego menu (z opcji do głównego, z rozdzielczości lub controls do opcji)
        selectedItemIndex = 0; // Resetowanie zaznaczonej opcji
    }
}

int Menu::getSelectedItemIndex() {
    return selectedItemIndex;
}

int Menu::getState() {
    return state;
}

const sf::Texture& Menu::getBackgroundTexture() const {
    return currentBackgroundTexture;
}

void Menu::setBackgroundTexture(const sf::Texture& texture, float width, float height) {
    currentBackgroundTexture = texture;
    sf::Sprite sprite;
    sprite.setTexture(currentBackgroundTexture);
    sprite.setScale(width / sprite.getGlobalBounds().width, height / sprite.getGlobalBounds().height);
    newBackgroundTexture = currentBackgroundTexture;
}


void Menu::centerText(sf::Text& text, float width, float height, int position) {
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    text.setPosition(sf::Vector2f(width / 2.0f, height / 4.0f * position));
}
void Menu::handleClick(float x, float y, sf::Music& backgroundMusic, bool& isMuted) {
    if (muteButton.getGlobalBounds().contains(x, y)) {
        if (isMuted) {
            backgroundMusic.play();
            isMuted = false;
            muteSprite.setTexture(muteTextureOn); // Zmiana tekstury na włączoną muzykę
        } else {
            backgroundMusic.pause();
            isMuted = true;
            muteSprite.setTexture(muteTextureOff); // Zmiana tekstury na wyciszoną muzykę
        }
    }
}