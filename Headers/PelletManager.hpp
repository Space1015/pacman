#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <filesystem>
#include <GameMap.hpp>
#include <utility>
#include <SFML/Audio.hpp>

using namespace std;

class PelletManager {
    public:
        PelletManager(GameMap gameMap);
        sf::Sprite charSprite;
        sf::Texture charTexture;
        int pelletMap[36][28];
        int score;
        int addScore(double x, double y);
        

};
