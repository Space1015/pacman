#include <SFML/Graphics.hpp>
#include <filesystem>
#include <iostream>
#include <GameMap.hpp>
#include <Pacman.hpp>
#include <Ghost.hpp>
using namespace std;
#define kP(x) sf::Keyboard::isKeyPressed(x)
int main()
{
    auto window = sf::RenderWindow({448u, 576u}, "Pacman");
    window.setFramerateLimit(60);

    sf::Texture clydeTexture;
    clydeTexture.loadFromFile("Resources/clyde.png");
    if (!clydeTexture.loadFromFile("Resources/clyde.png")) 
    {
        return -1;
    }
    sf::Texture pinkyTexture;
    pinkyTexture.loadFromFile("Resources/pinky.png");
    if (!pinkyTexture.loadFromFile("Resources/pinky.png")) 
    {
        return -1;
    }
    sf::Texture inkyTexture;
    inkyTexture.loadFromFile("Resources/inky.png");
    if (!inkyTexture.loadFromFile("Resources/inky.png"))
    {
        return -1;
    }
    sf::Texture blinkyTexture;
    blinkyTexture.loadFromFile("Resources/blinky.png");
    if (!blinkyTexture.loadFromFile("Resources/blinky.png")) 
    {
        return -1;
    }

    GameMap gameMap;
    Pacman pacman;
    Ghost blinky(blinkyTexture, Ghost::Type::BLINKY);
    blinky.dir = Ghost::Direction::LEFT;
    blinky.charSprite.setPosition(216, 320-3*32);
    blinky.charSprite.setPosition(216, 224);
    const float ANIMATION_FRAME_DURATION = 0.1f;

    sf::Clock clock;
    sf::Time elapsed;
    float elapsedTime = 0;
    
    vector<bool> direction(4);
    float animation_timer = 0.0f;
    int current_frame = 0;
    const int TOTAL_FRAMES = 8;
    
    while (window.isOpen())
    {
        //pacman animation
        pacman.dupe.setPosition(-100,-100);
        float deltaTime = clock.restart().asSeconds();
        animation_timer += deltaTime;
        if (animation_timer >= ANIMATION_FRAME_DURATION) 
        {
            animation_timer = 0.0f;
            current_frame += 1 + (current_frame % 2) * -2;
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
        if(kP(sf::Keyboard::W) || kP(sf::Keyboard::Up))
        {
            direction[0] = true;
        }else if(kP(sf::Keyboard::A) || kP(sf::Keyboard::Left))
        {
            direction[1] = true;
        }else if(kP(sf::Keyboard::S) || kP(sf::Keyboard::Down))
        {
            direction[2] = true;
        }else if(kP(sf::Keyboard::D) || kP(sf::Keyboard::Right))
        {
            direction[3] = true;
        }
        current_frame = pacman.move(gameMap, deltaTime, current_frame, direction);
        blinky.followPath(gameMap, blinky.charSprite.getPosition().x, pacman.charSprite.getPosition().x, blinky.charSprite.getPosition().y, pacman.charSprite.getPosition().y, deltaTime);
        direction = {false, false, false, false};
        window.clear();
        gameMap.displayMap(window, pacman.charSprite, pacman.dupe, blinky.charSprite);
        window.display();
    }
}