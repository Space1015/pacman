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
        int speed;
        int move(GameMap GameMap, double deltaTime, int current_frame, vector<bool> direction);
        double posx();
        double posy();
        double align(double x);
        double mod(double x);
        bool empty(int x, int y, GameMap gameMap);
};
