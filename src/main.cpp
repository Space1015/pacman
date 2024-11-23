#include <SFML/Graphics.hpp>
#include <filesystem>
#include <iostream>
#include <GameMap.hpp>
using namespace std;
const unsigned speed = 88;
int main()
{
    auto window = sf::RenderWindow({896u, 1152u}, "Pacman");
    window.setFramerateLimit(144);
    GameMap gameMap;
    Pacman pacman;
    sf::Clock clock;
    sf::Time elapsed;
    while (window.isOpen())
    {
        for (auto event = sf::Event(); window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        float deltaTime = clock.restart().asSeconds();
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
            pacman.charSprite.setPosition(pacman.charSprite.getPosition().x, pacman.charSprite.getPosition().y - speed * deltaTime);
        }else if(pacman.dir == Pacman::States::DOWN){
            pacman.charSprite.setPosition(pacman.charSprite.getPosition().x, pacman.charSprite.getPosition().y + speed * deltaTime);
        }else if(pacman.dir == Pacman::States::LEFT){
            pacman.charSprite.setPosition(pacman.charSprite.getPosition().x - speed * deltaTime, pacman.charSprite.getPosition().y);
        }else if(pacman.dir == Pacman::States::RIGHT){
            pacman.charSprite.setPosition(pacman.charSprite.getPosition().x + speed * deltaTime, pacman.charSprite.getPosition().y);
        }
        window.clear();
        gameMap.displayMap(window, pacman);
        window.display();
    }
}
