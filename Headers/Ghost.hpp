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
        void followPath(GameMap gameMap, double x, double y, float deltaTime);
        double align(double x);
        double posx();
        double posy();
        double mod(double x);
        char empty(int x, int y, GameMap gameMap);
        void randomMove(GameMap gameMap);
};
