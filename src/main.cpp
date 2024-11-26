#include <SFML/Graphics.hpp>
#include <filesystem>
#include <iostream>
#include <GameMap.hpp>
double posx(Pacman pacman){
    return pacman.charSprite.getPosition().x;
}
double posy(Pacman pacman){
    return pacman.charSprite.getPosition().y;
}
using namespace std;
const unsigned speed = 88;
char empty(int x, int y, GameMap gameMap){
    x /= 16; y /= 16;
    return gameMap.mapData[y][x] == ' ';
}
double mod(double x){
    return (int)x % 16 + x - (int) x;
}
double align(double x) {
    return round(x / 16.0) * 16.0;
}
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
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            if(empty((int)posx(pacman) + 8,(int)posy(pacman) - (mod(posy(pacman)) == 0 ? 1: 0), gameMap) && abs(align(posx(pacman)) - posx(pacman)) < 2){
                pacman.dir = Pacman::States::UP;
            }
        }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            if(empty((int)posx(pacman) - (mod(posx(pacman)) == 0 ? 1: 0),(int)posy(pacman) + 8, gameMap) && abs(align(posy(pacman)) - posy(pacman)) < 2){
                pacman.dir = Pacman::States::LEFT;
            }
        }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            if(empty((int)posx(pacman) + 8,(int)posy(pacman) + 16 + (mod(posy(pacman)) == 0 ? 1: 0), gameMap) && abs(align(posx(pacman)) - posx(pacman)) < 2){
                pacman.dir = Pacman::States::DOWN;
            }
        }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            if(empty((int)posx(pacman) + 16 + (mod(posx(pacman)) == 0 ? 1: 0),(int)posy(pacman) + 8, gameMap) && abs(align(posy(pacman)) - posy(pacman)) < 2){
                pacman.dir = Pacman::States::RIGHT;
            }
        }
        if (pacman.dir == Pacman::States::RIGHT) {
            std::cout << "Moving right" << std::endl;
} else if (pacman.dir == Pacman::States::LEFT) {
    std::cout << "Moving left" << std::endl;
} else if (pacman.dir == Pacman::States::UP) {
    std::cout << "Moving up" << std::endl;
} else if (pacman.dir == Pacman::States::DOWN) {
    std::cout << "Moving down" << std::endl;
} else if (pacman.dir == Pacman::States::STILL) {
    std::cout << "Not moving (STILL)" << std::endl;
}

        if(pacman.dir == Pacman::States::UP){
            if(empty((int)posx(pacman), (int)(posy(pacman) - deltaTime * speed), gameMap)){
                pacman.charSprite.setPosition(align(posx(pacman)),posy(pacman) - deltaTime * speed);
            }else{
                pacman.charSprite.setPosition(align(posx(pacman)),(int)posy(pacman)/16 * 16);
                pacman.dir = Pacman::States::STILL;
            }
        }else if(pacman.dir == Pacman::States::LEFT){
            if(empty((int)(posx(pacman) - deltaTime * speed),(int)posy(pacman), gameMap)){
                pacman.charSprite.setPosition(posx(pacman) - deltaTime * speed,align(posy(pacman)));
            }else{
                pacman.charSprite.setPosition((int)posx(pacman)/16 * 16, align(posy(pacman)));
                pacman.dir = Pacman::States::STILL;
            }
        }else if(pacman.dir == Pacman::States::DOWN){
            if(empty((int)posx(pacman), (int)(posy(pacman) + 16 + deltaTime * speed), gameMap)){
                pacman.charSprite.setPosition(align(posx(pacman)),posy(pacman) + deltaTime * speed);
            }else{
                pacman.charSprite.setPosition(align(posx(pacman)),align(posy(pacman)));
                pacman.dir = Pacman::States::STILL;
            }
        }else if(pacman.dir == Pacman::States::RIGHT){
            if(empty((int)(posx(pacman) + 16 + deltaTime * speed),(int)posy(pacman), gameMap)){
                pacman.charSprite.setPosition(posx(pacman) + deltaTime * speed,align(posy(pacman)));
            }else{
                pacman.charSprite.setPosition(align(posx(pacman)), align(posy(pacman)));
                pacman.dir = Pacman::States::STILL;
            }
        }
        window.clear();
        gameMap.displayMap(window, pacman);
        window.display();
    }
}