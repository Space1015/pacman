#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <filesystem>
#include <GameMap.hpp>
using namespace std;
class Pacman
{
    public:
        Pacman();
        sf::Sprite charSprite;
        sf::Sprite dupe;
        sf::Texture charTexture;
        enum class States{
            STILL,
            UP,
            DOWN,
            LEFT,
            RIGHT
        };
        States dir;
        void move(GameMap GameMap, double deltaTime, int speed, int current_frame);
        double posx();
        double posy();
        double align(double x);
        double mod(double x);
        char empty(int x, int y, GameMap gameMap);
};
