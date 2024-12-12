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
        enum class State{// make this a static var
            NORMAL,
            SCATTER,
            FRIGHTENED
        };
        enum class Dir{
            UP,
            DOWN,
            LEFT,
            RIGHT,
            STILL
        };
        State state;
        Ghost(sf::Texture &texture, Type type);
        sf::Sprite charSprite;
        sf::Texture charTexture;
        Type type;
        int speed;
        double timer;
        pair<int, int> gTC(GameMap gameMap, double x, double y);
        void move(GameMap gameMap, pair<int, int> s, double deltaTime);
};