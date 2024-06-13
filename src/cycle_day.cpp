#include "cycle_day.h"
#include <iostream>

CycleDay::CycleDay()
    : window(sf::VideoMode(800, 600), "SFML Window"),
    timePerDay(sf::seconds(16 * 60)),
    elapsedTime(sf::Time::Zero),
    dayCounter(0),
    totalCowMilk(0),
    totalSheepWool(0),
    totalChickenEggs(0),
    totalPigMeat(0) {

    // Create animals
    harvestCritters.push_back(new cow(0, 0));
    harvestCritters.push_back(new sheep(100, 100));
    nonHarvestCritters.push_back(new chicken(200, 200));
    nonHarvestCritters.push_back(new pig(300, 300));
}

void CycleDay::run() {
    while (window.isOpen()) {
        processEvents();
        sf::Time deltaTime = clock.restart();
        update(deltaTime);
        render();
    }
}

void CycleDay::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
    }
}

void CycleDay::update(sf::Time deltaTime) {
    elapsedTime += deltaTime;
    if (elapsedTime >= timePerDay) {
        elapsedTime -= timePerDay;
        dayCounter++;
        endOfDaySummary();
        resetDailyState();
    }

    for (auto& critter : harvestCritters) {
        critter->move(window.getSize().x, window.getSize().y);
    }
    for (auto& critter : nonHarvestCritters) {
        critter->move(window.getSize().x, window.getSize().y);
    }
}

void CycleDay::render() {
    window.clear();
    for (auto& critter : harvestCritters) {
        critter->draw(window);
    }
    for (auto& critter : nonHarvestCritters) {
        critter->draw(window);
    }
    window.display();
}

void CycleDay::endOfDaySummary() {
    int cowMilk = 0;
    int sheepWool = 0;
    int chickenEggs = 0;
    int pigMeat = 0;

    for (auto& critter : harvestCritters) {
        cow* c = dynamic_cast<cow*>(critter);
        if (c && c->harvest()) {
            cowMilk++;
        }
        sheep* s = dynamic_cast<sheep*>(critter);
        if (s && s->harvest()) {
            sheepWool++;
        }
    }
    for (auto& critter : nonHarvestCritters) {
        chicken* ch = dynamic_cast<chicken*>(critter);
        if (ch && ch->harvest()) {
            chickenEggs++;
        }
        pig* p = dynamic_cast<pig*>(critter);
        if (p && p->harvest()) {
            pigMeat++;
        }
    }

    totalCowMilk += cowMilk;
    totalSheepWool += sheepWool;
    totalChickenEggs += chickenEggs;
    totalPigMeat += pigMeat;

    summaryWindow.showSummary(dayCounter, cowMilk, sheepWool, chickenEggs, pigMeat,totalCowMilk, totalSheepWool, totalChickenEggs, totalPigMeat);
}

void CycleDay::resetDailyState() {
    for (auto& critter : harvestCritters) {
        critter->resetDailyState();
    }
    for (auto& critter : nonHarvestCritters) {
        critter->resetDailyState();
    }
}
