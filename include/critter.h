#ifndef critter_h
#define critter_h
#include <iostream>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <vector>
#include "entity.h"
class entity;
class critter:public entity
{
public:
    bool take_dmg(int dmg);
    void move(int worldWidth, int worldHeight);
    critter(int x, int y, int hp, const std::vector<std::string>& textureFiles);
    ~critter();
      void draw(sf::RenderWindow &window);
protected:
      std::vector<sf::Texture> textures;
      sf::Sprite sprite;
      size_t currentTextureIndex;
};
class harv_crit : public critter {
public:
    harv_crit(int x, int y, int hp, const std::vector<std::string>& textureFiles);
    virtual ~harv_crit();

    bool harvest();
    int getHarvestCount() const;
 bool collected_today;
    void resetDailyState();
protected:

    int harvest_count;  // Licznik

};
class cow:public harv_crit
{
public:
    cow(int x, int y);
    ~cow();
};

class sheep:public harv_crit
{
public:
    sheep(int x, int y) ;

  ~sheep();
};
class non_harv_crit:public critter
{
public:
    void resetDailyState();
    //spawnable item as item in imtems.h must be changed!!!!
   non_harv_crit(int x, int y, int hp, const std::vector<std::string>& textureFiles);
    ~non_harv_crit();
    bool harvest();  // Nowa metoda
    int getHarvestCount() const;  // Nowa metoda
protected:
    bool collected_today;
    int harvest_count;
};
class chicken : public non_harv_crit {
public:
    chicken(int x, int y);
    virtual ~chicken();

    void loadAnimation(const std::string& file, int frameWidth, int frameHeight);
    void updateAnimation();

private:
    std::vector<sf::IntRect> animationFrames;
    size_t currentFrame;
    sf::Clock animationClock;
};
class pig:public non_harv_crit
{
public:
    pig(int x, int y);
    ~pig();
};



#endif


