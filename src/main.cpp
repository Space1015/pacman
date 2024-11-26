#include <SFML/Graphics.hpp>
#include <filesystem>
#include <iostream>
#include <GameMap.hpp> //implicitly includes Pacman.hpp
#include <Ghost.hpp>

// hi let's move these functions to pacman.cpp and pacman.hpp? also duplicate it for ghost class
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
        float deltaTime = clock.restart().asSeconds();
        animation_timer += deltaTime;
        if (animation_timer >= ANIMATION_FRAME_DURATION) {
            animation_timer = 0.0f;
            if (current_frame%2==0) {
                current_frame = current_frame + 1;
                sf::IntRect pacmanTextureRect(current_frame * 16, 0, 16, 16);
                pacman.charSprite.setTextureRect(pacmanTextureRect);
            } else {
                current_frame = current_frame - 1;
                sf::IntRect pacmanTextureRect(current_frame * 16, 0, 16, 16);
                pacman.charSprite.setTextureRect(pacmanTextureRect);
            }
        }

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
            current_frame = 2;
            sf::IntRect pacmanTextureRect(current_frame * 16, 0, 16, 16);
            pacman.charSprite.setTextureRect(pacmanTextureRect);
        }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            if(empty((int)posx(pacman) - (mod(posx(pacman)) == 0 ? 1: 0),(int)posy(pacman) + 8, gameMap) && abs(align(posy(pacman)) - posy(pacman)) < 2){
                pacman.dir = Pacman::States::LEFT;
            }
            current_frame = 0;
            sf::IntRect pacmanTextureRect(current_frame * 16, 0, 16, 16);
            pacman.charSprite.setTextureRect(pacmanTextureRect);
        }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            if(empty((int)posx(pacman) + 8,(int)posy(pacman) + 16 + (mod(posy(pacman)) == 0 ? 1: 0), gameMap) && abs(align(posx(pacman)) - posx(pacman)) < 2){
                pacman.dir = Pacman::States::DOWN;
            }
            current_frame = 6;
            sf::IntRect pacmanTextureRect(current_frame * 16, 0, 16, 16);
            pacman.charSprite.setTextureRect(pacmanTextureRect);
        }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            if(empty((int)posx(pacman) + 16 + (mod(posx(pacman)) == 0 ? 1: 0),(int)posy(pacman) + 8, gameMap) && abs(align(posy(pacman)) - posy(pacman)) < 2){
                pacman.dir = Pacman::States::RIGHT;
            }
            current_frame = 4;
            sf::IntRect pacmanTextureRect(current_frame * 16, 0, 16, 16);
            pacman.charSprite.setTextureRect(pacmanTextureRect);
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