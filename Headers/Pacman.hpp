#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <filesystem>

using namespace std;
class Pacman
{
    public:
        Pacman();
        sf::Sprite charSprite;
        sf::Texture charTexture;
        enum class States{
            STILL,
            UP,
            DOWN,
            LEFT,
            RIGHT
        };
        States dir;
};
