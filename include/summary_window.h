#ifndef SUMMARY_WINDOW_H
#define SUMMARY_WINDOW_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class SummaryWindow {
public:
    SummaryWindow();
    void showSummary(int day, int cowMilk, int sheepWool, int chickenEggs, int pigMeat,int totalCowMilk, int totalSheepWool, int totalChickenEggs, int totalPigMeat);

private:
    sf::RenderWindow window;
    sf::Font font;
    std::vector<sf::Text> texts;

    void createText(const std::string& str, float x, float y);
};

#endif // SUMMARY_WINDOW_H
