#ifndef CYCLE_DAY_H
#define CYCLE_DAY_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "critter.h"
#include "summary_window.h"

class CycleDay {
public:
    CycleDay();
    void run();

private:
    void processEvents();
    void update(sf::Time deltaTime);
    void render();
    void endOfDaySummary();
    void resetDailyState();

    sf::RenderWindow window;
    sf::Time timePerDay;
    sf::Clock clock;
    sf::Time elapsedTime;
    int dayCounter;
    std::vector<harv_crit*> harvestCritters;
    std::vector<non_harv_crit*> nonHarvestCritters;

    int totalCowMilk;
    int totalSheepWool;
    int totalChickenEggs;
    int totalPigMeat;

    SummaryWindow summaryWindow;
};

#endif // CYCLE_DAY_H
