#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <filesystem>

using namespace std;
class GameMap
{
    public:
        GameMap();
        void displayMap(sf::RenderWindow& window);
    private:
        vector<string> mapData;
};
