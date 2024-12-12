#include "PelletManager.hpp"

using namespace std;
PelletManager::PelletManager(GameMap gameMap) {
    charTexture.loadFromFile("Resources/pellet.png");
    charSprite.setTexture(charTexture);
    charSprite.setTextureRect(sf::IntRect(6, 6, 4, 4));
    score = 0;
    for(int i = 0; i < 36; i++){
        for(int j = 0; j < 28; j++){
            if(i < 3 || i > 32){
                pelletMap[i][j] = 0;
            }else if(gameMap.mapData[i][j] == ' ' && !(i == 20 && (j == 13 || j == 14))){
                pelletMap[i][j] = 1;
            }else{
                pelletMap[i][j] = 0;
            }
        }
    }
}

int PelletManager::addScore(double x, double y){
    int ret = 0;
    if(fmod(x, 16) == 0 && fmod(y, 16) == 0){
        if(pelletMap[(int)y/16][(int)x/16] != 0){
            ret += 10;
            pelletMap[(int)y/16][(int)x/16] = 0;
        }
    }else if(fmod(x,16 == 0)){
        if(pelletMap[(int)y/16][(int)x/16] != 0 && (int)y/16 * 16 + 10 > y){// make sure the pellet intersects with pacman
            ret += 10;
            pelletMap[(int)y/16][(int)x/16] = 0;
        }
        if(pelletMap[(int)y/16 + 1][(int)x/16] != 0 && (int)y/16 * 16 + 6 < y){
            ret += 10;
            pelletMap[(int)y/16 + 1][(int)x/16] = 0;
        }
    }else {
        if(pelletMap[(int)y/16][(int)x/16] != 0 && (int)x/16 * 16 + 10 > x){
            ret += 10;
            pelletMap[(int)y/16][(int)x/16] = 0;
        }
        if(pelletMap[(int)y/16][(int)x/16 + 1] != 0 && (int)x/16 * 16 + 6 < x){
            ret += 10;
            pelletMap[(int)y/16][(int)x/16 + 1] = 0;
        }
    }
    return ret;
}

