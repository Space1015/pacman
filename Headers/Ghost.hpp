#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <filesystem>
#include <Pacman.hpp>
#include <Global.hpp>
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
            RIGHT,
            STILL
        };
        enum class State{
            NORMAL,
            SCATTER,
            FRIGHTENED
        };
        Direction dir;
        Ghost(sf::Texture &texture, Type type);
        sf::Sprite charSprite;
        sf::Texture charTexture;
        Type type;
        int speed;
        void followPath(GameMap gameMap, double x, double px, double y, double py, double deltaTime);
        pair<int, int> goToCoords(GameMap gameMap, double x, double y);
        void move(GameMap gameMap, pair<int, int> s, double deltaTime);
};