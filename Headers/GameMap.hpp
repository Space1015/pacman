#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <filesystem>
#include <cmath>

using namespace std;
class PelletManager;
class GameMap
{
    public:
        GameMap();
        sf::Sprite mapSprite;
        sf::Texture mapTexture;
        void displayMap(sf::RenderWindow& window, sf::Sprite charSprite, sf::Sprite dupe, sf::Sprite blinky, int pelletMap[36][28], sf::Sprite pSprite);
        vector<string> mapData;
};
