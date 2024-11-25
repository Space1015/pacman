#include <SFML/Graphics.hpp>
#include <filesystem>
#include <iostream>
#include <GameMap.hpp>
using namespace std;
const unsigned speed = 88;
// char emptyOrNot(int x, int y){
//     x /= 32; y /= 32;
//     return gameMap.mapData[x][y];
// }
int main()
{
    auto window = sf::RenderWindow({448u, 576u}, "Pacman");
    window.setFramerateLimit(60);
    GameMap gameMap;
    Pacman pacman;
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
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
            pacman.dir = Pacman::States::UP;
        }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
            pacman.dir = Pacman::States::LEFT;
        }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
            pacman.dir = Pacman::States::DOWN;
        }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
            pacman.dir = Pacman::States::RIGHT;
        }
        if(pacman.dir == Pacman::States::UP){
            pacman.charSprite.move(0, speed * deltaTime * -1);
        }else if(pacman.dir == Pacman::States::DOWN){
            pacman.charSprite.move(0, speed * deltaTime);
        }else if(pacman.dir == Pacman::States::LEFT){
            pacman.charSprite.move(speed * deltaTime * -1, 0);
        }else if(pacman.dir == Pacman::States::RIGHT){
            pacman.charSprite.move(speed * deltaTime, 0);
        }
        window.clear();
        gameMap.displayMap(window, pacman);
        window.display();
    }
}