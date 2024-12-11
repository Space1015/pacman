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

