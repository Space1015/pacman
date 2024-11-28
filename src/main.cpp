#include <SFML/Graphics.hpp>
#include <filesystem>
#include <iostream>
#include <GameMap.hpp>
#include <Pacman.hpp>
#include <Ghost.hpp>
using namespace std;
const unsigned speed = 88;
// hi let's move these functions to pacman.cpp and pacman.hpp? also duplicate it for ghost class
double posx(Pacman pacman){
    return pacman.charSprite.getPosition().x;
}
double posy(Pacman pacman){
    return pacman.charSprite.getPosition().y;
}
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

    sf::Texture clydeTexture;
    clydeTexture.loadFromFile("Resources/clyde.png");
    if (!clydeTexture.loadFromFile("Resources/clyde.png")) {
        return -1;
    }
    sf::Texture pinkyTexture;
    pinkyTexture.loadFromFile("Resources/pinky.png");
    if (!pinkyTexture.loadFromFile("Resources/pinky.png")) {
        return -1;
    }
    sf::Texture inkyTexture;
    inkyTexture.loadFromFile("Resources/inky.png");
    if (!inkyTexture.loadFromFile("Resources/inky.png")) {
        return -1;
    }
    sf::Texture blinkyTexture;
    blinkyTexture.loadFromFile("Resources/blinky.png");
    if (!blinkyTexture.loadFromFile("Resources/blinky.png")) {
        return -1;
    }

    GameMap gameMap;
    Pacman pacman;
    Ghost blinky(blinkyTexture);
    Ghost pinky(pinkyTexture);
    Ghost inky(inkyTexture);
    Ghost clyde(clydeTexture);
    const float ANIMATION_FRAME_DURATION = 0.1f;

    sf::Clock clock;
    sf::Time elapsed;

    float animation_timer = 0.0f;
    int current_frame = 0;
    const int TOTAL_FRAMES = 8;
    
    while (window.isOpen())
    {
        //pacman animation
        pacman.dupe.setPosition(-100,-100);
        float deltaTime = clock.restart().asSeconds();
        animation_timer += deltaTime;
        if (animation_timer >= ANIMATION_FRAME_DURATION) {
            animation_timer = 0.0f;
            current_frame += (current_frame % 2) * -2 + 1;
            sf::IntRect pacmanTextureRect(current_frame * 16, 0, 16, 16);
            pacman.charSprite.setTextureRect(pacmanTextureRect);
            pacman.dupe.setTextureRect(pacmanTextureRect);
        }
        //check for game end
        for (auto event = sf::Event(); window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        //pacman keyboard control movement and animation
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            if(empty((int)posx(pacman) + 8,(int)posy(pacman) - (mod(posy(pacman)) == 0 ? 1: 0), gameMap) && abs(align(posx(pacman)) - posx(pacman)) < 2){
                pacman.dir = Pacman::States::UP;
                if(current_frame != 3) current_frame = 2;
            }
        }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            if((int)posx(pacman) == 0){
                pacman.dir = Pacman::States::LEFT;
                if(current_frame != 1) current_frame = 0;
            }if(empty((int)posx(pacman) - (mod(posx(pacman)) == 0 ? 1: 0),(int)posy(pacman) + 8, gameMap) && abs(align(posy(pacman)) - posy(pacman)) < 2){
                pacman.dir = Pacman::States::LEFT;
                if(current_frame != 1) current_frame = 0;
            }
        }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            if(empty((int)posx(pacman) + 8,(int)posy(pacman) + 16 + (mod(posy(pacman)) == 0 ? 1: 0), gameMap) && abs(align(posx(pacman)) - posx(pacman)) < 2){
                pacman.dir = Pacman::States::DOWN;
                if(current_frame != 7)current_frame = 6;
            }
        }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            if(posx(pacman) - 27 * 16 > 0){
                pacman.dir = Pacman::States::RIGHT;
                if(current_frame != 5) current_frame = 4;
            }else if(empty((int)posx(pacman) + 16 + (mod(posx(pacman)) == 0 ? 1: 0),(int)posy(pacman) + 8, gameMap) && abs(align(posy(pacman)) - posy(pacman)) < 2){
                pacman.dir = Pacman::States::RIGHT;
                if(current_frame != 5) current_frame = 4;
            }
        }
        pacman.move(gameMap, deltaTime, speed, current_frame);
        window.clear();
        gameMap.displayMap(window, pacman.charSprite, pacman.dupe);
        window.display();
    }
}