#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <filesystem>
#include <GameMap.hpp>
#include <utility>

using namespace std;

class PelletManager {
    public:
        PelletManager(GameMap gameMap);
        sf::Sprite charSprite;
        sf::Texture charTexture;
        int pelletMap[36][28];
        int score;

};
