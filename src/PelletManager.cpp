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
                pelletMap[i][j] = PelletType::NONE;
            }else if(gameMap.mapData[i][j] == ' ' && !(i == 20 && (j == 13 || j == 14))){
                pelletMap[i][j] = PelletType::REGULAR;
            }else{
                pelletMap[i][j] = PelletType::NONE;
            }
        }
    }
}
void PelletManager::displayMap(sf::RenderWindow& window){
    for(int i = 0; i < 36; i++){
        for(int j = 0; j < 36; j++){
            if(pelletMap[i][j] == PelletType::REGULAR){
                charSprite.setPosition(j * 16 + 6, i * 16 + 6);
                window.draw(charSprite);
            }
        }
    }
}
