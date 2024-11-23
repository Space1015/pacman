#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <filesystem>
#include <Pacman.hpp>

using namespace std;
class GameMap
{
    public:
        GameMap();
        sf::Sprite mapSprite;
        sf::Texture mapTexture;
        void displayMap(sf::RenderWindow& window, Pacman pacman);
        vector<string> mapData;
};
