#ifndef PELLET_H
#define PELLET_H

#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <filesystem>
#include <GameMap.hpp>
#include <utility>

using namespace std;

enum class PelletType {
    REGULAR,
    POWER
};

class Pellet {
private:
    pair<int, int> position;
    PelletType type;
    bool isEaten;

public:
    Pellet(sf::Texture &texture);
        sf::Sprite charSprite;
        sf::Texture charTexture;
   
    Pellet(int x, int y, PelletType type = PelletType::REGULAR);
    pair<int, int> getPosition() const;
    PelletType getType() const;
    bool getIsEaten() const;

    void setPosition(int x, int y); // i need to figure out how to make copies of the pellets and set at diff positions
    void setType(PelletType type);

    void eat();
};

#endif // PELLET_H
