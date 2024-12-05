#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <filesystem>
#include <Pacman.hpp>
#include <GameMap.hpp>
using namespace std;
class Ghost
{
    public:
        enum class Type{
            BLINKY,
            INKY,
            PINKY,
            CLYDE
        };
        enum class Direction{
            UP,
            DOWN,
            LEFT,
            RIGHT
        };
        Direction dir;
        Ghost(sf::Texture &texture, Type type);
        sf::Sprite charSprite;
        sf::Texture charTexture;
        Type type;
        int speed;
        void followPath(double x, double y);
        double align(double x);
};
