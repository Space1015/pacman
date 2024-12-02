#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <filesystem>

using namespace std;
class Ghost
{
    public:
        Ghost(sf::Texture &texture);
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
