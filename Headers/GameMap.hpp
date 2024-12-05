#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <filesystem>

using namespace std;
class GameMap
{
    public:
        GameMap();
        sf::Sprite mapSprite;
        sf::Texture mapTexture;
        void displayMap(sf::RenderWindow& window, sf::Sprite charSprite, sf::Sprite dupe, sf::Sprite blinky);
        vector<string> mapData;
};
