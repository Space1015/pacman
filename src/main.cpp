#include <SFML/Graphics.hpp>
#include <filesystem>
#include <iostream>
#include <GameMap.hpp>
using namespace std;
GameMap gameMap;
Pacman pacman;
const unsigned speed = 176;
char emptyOrNot(int x, int y){
    x /= 32; y /= 32;
    return gameMap.mapData[x][y];
}
int main()
{
    auto window = sf::RenderWindow({896u, 1152u}, "Pacman");
    window.setFramerateLimit(60);
    sf::Clock clock;
    sf::Time elapsed;
    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();
        for (auto event = sf::Event(); window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            if(!(emptyOrNot(pacman.charSprite.getPosition().x, pacman.charSprite.getPosition().y - 32) == '#' && ((int)pacman.charSprite.getPosition().y % 32 == 0))){
                pacman.dir = Pacman::States::UP;
            }
        }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            if(!(emptyOrNot(pacman.charSprite.getPosition().x - 32, pacman.charSprite.getPosition().y) == '#' && ((int)pacman.charSprite.getPosition().x % 32 == 0))){
                pacman.dir = Pacman::States::LEFT;
            }
        }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            if(!(emptyOrNot(pacman.charSprite.getPosition().x, pacman.charSprite.getPosition().y + 32) == '#' && ((int)pacman.charSprite.getPosition().y % 32 == 0))){
                pacman.dir = Pacman::States::DOWN;
            }
        }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            if(!(emptyOrNot(pacman.charSprite.getPosition().x + 32, pacman.charSprite.getPosition().y) == '#' && ((int)pacman.charSprite.getPosition().x % 32 == 0))){
                pacman.dir = Pacman::States::RIGHT;
            }
        }
        if(pacman.dir == Pacman::States::UP){
            if(emptyOrNot(pacman.charSprite.getPosition().x, pacman.charSprite.getPosition().y - 32) == '#'){
                if(pacman.charSprite.getPosition().y - ((int)pacman.charSprite.getPosition().y/32) * 32 >= speed * deltaTime){
                    pacman.charSprite.move(0, speed * deltaTime * -1);
                }else{
                    pacman.charSprite.setPosition(pacman.charSprite.getPosition().x, (int)pacman.charSprite.getPosition().y / 32 * 32);
                    pacman.dir = Pacman::States::STILL;
                }
            }else if((int)pacman.charSprite.getPosition().x % 32 < 2){
                pacman.charSprite.setPosition(((int)pacman.charSprite.getPosition().x/32) * 32,pacman.charSprite.getPosition().y + speed * deltaTime * -1);
            }else if((int)pacman.charSprite.getPosition().x % 32 > 29){
                pacman.charSprite.setPosition(((int)pacman.charSprite.getPosition().x/32) * 32 +  32,pacman.charSprite.getPosition().y + speed * deltaTime * -1);
            }
        }else if(pacman.dir == Pacman::States::DOWN){
            if(emptyOrNot(pacman.charSprite.getPosition().x, pacman.charSprite.getPosition().y + 32) == '#'){
                if(32 - pacman.charSprite.getPosition().y + ((int)pacman.charSprite.getPosition().y/32) * 32 >= speed * deltaTime){
                    pacman.charSprite.move(0, speed * deltaTime);
                }else{
                    pacman.charSprite.setPosition(pacman.charSprite.getPosition().x, (int)pacman.charSprite.getPosition().y / 32 * 32 + 32);
                    pacman.dir = Pacman::States::STILL;
                }
            }else if((int)pacman.charSprite.getPosition().x % 32 < 2){
                pacman.charSprite.setPosition(((int)pacman.charSprite.getPosition().x/32) * 32,pacman.charSprite.getPosition().y + speed * deltaTime);
            }else if((int)pacman.charSprite.getPosition().x % 32 > 29){
                pacman.charSprite.setPosition(((int)pacman.charSprite.getPosition().x/32) * 32 +  32,pacman.charSprite.getPosition().y + speed * deltaTime);
            }
        }else if (pacman.dir == Pacman::States::LEFT) {
            if (emptyOrNot(pacman.charSprite.getPosition().x - 32, pacman.charSprite.getPosition().y) == '#') {
                if (pacman.charSprite.getPosition().x - ((int)pacman.charSprite.getPosition().x / 32) * 32 >= speed * deltaTime) {
                    pacman.charSprite.move(speed * deltaTime * -1, 0);
                } else {
                    pacman.charSprite.setPosition((int)pacman.charSprite.getPosition().x / 32 * 32, pacman.charSprite.getPosition().y);
                    pacman.dir = Pacman::States::STILL;
                }
            } else if((int)pacman.charSprite.getPosition().y % 32 < 2){
                pacman.charSprite.setPosition(pacman.charSprite.getPosition().x + speed * deltaTime * -1,((int)pacman.charSprite.getPosition().y/32) * 32);
            }else if((int)pacman.charSprite.getPosition().y % 32 > 29){
                pacman.charSprite.setPosition(pacman.charSprite.getPosition().x + speed * deltaTime * -1, ((int)pacman.charSprite.getPosition().y/32) * 32 +  32);
            }
        } else if (pacman.dir == Pacman::States::RIGHT) {
            if (emptyOrNot(pacman.charSprite.getPosition().x + 32, pacman.charSprite.getPosition().y) == '#') {
                if (32 - pacman.charSprite.getPosition().x + ((int)pacman.charSprite.getPosition().x / 32) * 32 >= speed * deltaTime) {
                    pacman.charSprite.move(speed * deltaTime, 0);
                } else {
                    pacman.charSprite.setPosition((int)pacman.charSprite.getPosition().x / 32 * 32 + 32, pacman.charSprite.getPosition().y);
                    pacman.dir = Pacman::States::STILL;
                }
            } else if((int)pacman.charSprite.getPosition().y % 32 < 2){
                pacman.charSprite.setPosition(pacman.charSprite.getPosition().x + speed * deltaTime,((int)pacman.charSprite.getPosition().y/32) * 32);
            }else if((int)pacman.charSprite.getPosition().y % 32 > 29){
                pacman.charSprite.setPosition(pacman.charSprite.getPosition().x + speed * deltaTime, ((int)pacman.charSprite.getPosition().y/32) * 32 +  32);
            }
        }
        window.clear();
        gameMap.displayMap(window, pacman);
        window.display();
    }
}
