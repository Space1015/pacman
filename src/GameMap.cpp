#include "GameMap.hpp"
GameMap::GameMap()
{
    mapData = {
    "                            ",
    "                            ",
    "                            ",
    "############################",
    "#            ##            #",
    "# #### ##### ## ##### #### #",
    "# #### ##### ## ##### #### #",
    "# #### ##### ## ##### #### #",
    "#                          #",
    "# #### ## ######## ## #### #",
    "# #### ## ######## ## #### #",
    "#      ##    ##    ##      #",
    "###### ##### ## ##### ######",
    "###### ##### ## ##### ######",
    "###### ##          ## ######",
    "###### ## ######## ## ######",
    "###### ## ######## ## ######",
    "          ########          ",
    "###### ## ######## ## ######",
    "###### ## ######## ## ######",
    "###### ##          ## ######",
    "###### ## ######## ## ######",
    "###### ## ######## ## ######",
    "#            ##            #",
    "# #### ##### ## ##### #### #",
    "# #### ##### ## ##### #### #",
    "#   ##                ##   #",
    "### ## ## ######## ## ## ###",
    "### ## ## ######## ## ## ###",
    "#      ##    ##    ##      #",
    "# ########## ## ########## #",
    "# ########## ## ########## #",
    "#                          #",
    "############################",
    "                            ",
    "                            ",
    };
    mapTexture.loadFromFile("Resources/gamemap.png");
    mapSprite.setTexture(mapTexture);
}
void GameMap::displayMap(sf::RenderWindow& window, sf::Sprite charSprite, sf::Sprite dupe, sf::Sprite blinky, int pelletMap[36][28], sf::Sprite pSprite, sf::Text text)
{ 
    window.draw(mapSprite);
    for(int i = 0; i < 36; i++){
        for(int j = 0; j < 36; j++){
            if(pelletMap[i][j] == 1){
                pSprite.setPosition(j * 16 + 6, i * 16 + 6);
                window.draw(pSprite);
            }
        }
    }
    window.draw(charSprite);
    dupe.setTexture(*charSprite.getTexture());
    window.draw(dupe);
    window.draw(blinky);
    window.draw(text);
}
