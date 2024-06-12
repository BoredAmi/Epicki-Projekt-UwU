#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <string>

class Menu {
public:
    Menu(float width, float height);
    void draw(sf::RenderWindow& window);
    void moveUp();
    void moveDown();
     sf::RectangleShape muteButton;
    void select();
    void back();
    void handleClick(float x, float y);
    int getSelectedItemIndex();
    int getState();
   void setBackgroundTexture(const sf::Texture& texture, float width, float height);
    const sf::Texture& getBackgroundTexture() const;
    void handleClick(float x, float y, sf::Music& backgroundMusic, bool& isMuted);
    void select(sf::Music& backgroundMusic);
private:
    void centerText(sf::Text& text, float width, float height, int position);

    int selectedItemIndex;
    int state; // 0: Main Menu, 1: Options, 2: Resolution, 3: Controls, 4: Volume
    sf::Font font;
    sf::Text menu[3];
    sf::Text options[3];
    sf::Text resolutions[3];
    sf::Text controls[3];
    sf::Text volumes[3];
    std::vector<sf::RectangleShape> menuBackgrounds;
    std::vector<sf::RectangleShape> optionsBackgrounds;
    std::vector<sf::RectangleShape> resolutionBackgrounds;
    std::vector<sf::RectangleShape> controlsBackgrounds;
    std::vector<sf::RectangleShape> volumeBackgrounds;
    sf::Texture currentBackgroundTexture;
    sf::Texture newBackgroundTexture;

    sf::Texture mainMenuBackgroundTexture;
    sf::Sprite mainMenuBackgroundSprite;
    sf::Texture optionsMenuBackgroundTexture;
    sf::Sprite optionsMenuBackgroundSprite;
    sf::Texture resolutionMenuBackgroundTexture;
    sf::Sprite resolutionMenuBackgroundSprite;
    sf::Texture controlsMenuBackgroundTexture;
    sf::Sprite controlsMenuBackgroundSprite;
    sf::Texture volumeMenuBackgroundTexture;
    sf::Sprite volumeMenuBackgroundSprite;

    // Tła dla menu Controls
    sf::Texture controlBackgroundTexture1;
    sf::Sprite controlBackgroundSprite1;
    sf::Texture controlBackgroundTexture2;
    sf::Sprite controlBackgroundSprite2;
    sf::Texture controlBackgroundTexture3;
    sf::Sprite controlBackgroundSprite3;

    // Deklaracja przycisku wyciszania
    sf::Texture muteTextureOn;
    sf::Texture muteTextureOff;
    sf::Sprite muteSprite;
};

#endif // MENU_H
