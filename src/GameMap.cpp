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
int GameMap::displayMap(sf::RenderWindow& window, sf::Sprite charSprite, sf::Sprite dupe, sf::Sprite blinky, int pelletMap[36][28], sf::Sprite pSprite, sf::Text text)
{ 
    int pCount = 0;
    window.draw(mapSprite);
    for(int i = 0; i < 36; i++){
        for(int j = 0; j < 36; j++){
            if(pelletMap[i][j] == 1){
                pSprite.setPosition(j * 16 + 6, i * 16 + 6);
                window.draw(pSprite);
                pCount++;
            }
        }
    }
    window.draw(charSprite);
    dupe.setTexture(*charSprite.getTexture());
    window.draw(dupe);
    window.draw(blinky);
    window.draw(text);
    return pCount;
}
