#include "summary_window.h"

SummaryWindow::SummaryWindow() : window(sf::VideoMode(400, 400), "End of Day Summary") {
    if (!font.loadFromFile("C:/Users/pwsmi/OneDrive/Pulpit/nienazwane2/Jacquard_12/Jacquard12-Regular.ttf")) {
        // Handle error
    }
}

void SummaryWindow::showSummary(int day, int cowMilk, int sheepWool, int chickenEggs, int pigMeat,int totalCowMilk, int totalSheepWool, int totalChickenEggs, int totalPigMeat) {

    texts.clear();
    createText("Day " + std::to_string(day) + " Summary:", 20, 20);
    createText("Cow Milk: " + std::to_string(cowMilk), 20, 60);
    createText("Sheep Wool: " + std::to_string(sheepWool), 20, 100);
    createText("Chicken Eggs: " + std::to_string(chickenEggs), 20, 140);
    createText("Pig Meat: " + std::to_string(pigMeat), 20, 180);
    createText("Total Cow Milk: " + std::to_string(totalCowMilk), 20, 220);
    createText("Total Sheep Wool: " + std::to_string(totalSheepWool), 20, 260);
    createText("Total Chicken Eggs: " + std::to_string(totalChickenEggs), 20, 300);
    createText("Total Pig Meat: " + std::to_string(totalPigMeat), 20, 340);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();
        for (const auto& text : texts) {
            window.draw(text);
        }
        window.display();
    }
}

void SummaryWindow::createText(const std::string& str, float x, float y) {
    sf::Text text;
    text.setFont(font);
    text.setString(str);
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::White);
    text.setPosition(x, y);
    texts.push_back(text);
}
