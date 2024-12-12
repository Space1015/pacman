#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <filesystem>
#include <iostream>
#include <GameMap.hpp>
#include <Pacman.hpp>
#include <Ghost.hpp>
#include <SFX.hpp>
#include <PelletManager.hpp>

using namespace std;
#define kP(x) sf::Keyboard::isKeyPressed(x)
int main()
{
    auto window = sf::RenderWindow({448u, 576u}, "Pacman");
    window.setFramerateLimit(30);

    sf::Texture clydeTexture;
    clydeTexture.loadFromFile("Resources/clyde.png");
    sf::Texture pinkyTexture;
    pinkyTexture.loadFromFile("Resources/pinky.png");
    sf::Texture inkyTexture;
    inkyTexture.loadFromFile("Resources/inky.png");
    sf::Texture blinkyTexture;
    blinkyTexture.loadFromFile("Resources/blinky.png");

    sf::Sound sound;
    sf::Text text;
    sf::Font font;
    font.loadFromFile("Resources/pacman.ttf");
    text.setPosition(0,0);
    text.setCharacterSize(16);
    text.setFillColor(sf::Color::White);
    text.setFont(font);
    text.setFillColor(sf::Color::White);

    sound.setVolume(30.f);
    SFX playlist;
    playlist.intro.play();
    playlist.siren.setLoop(true);
    playlist.waka.setLoop(true);
    playlist.waka.setVolume(15.f);

    GameMap gameMap;
    Pacman pacman;
    PelletManager pellet(gameMap);
    Ghost blinky(blinkyTexture, Ghost::Type::BLINKY);
    blinky.charSprite.setPosition(216, 224);
    Ghost pinky(pinkyTexture, Ghost::Type::PINKY);
    pinky.charSprite.setPosition(224, 216);
    Ghost inky(inkyTexture, Ghost::Type::INKY);
    pinky.charSprite.setPosition(200, 224);
    Ghost clyde(clydeTexture, Ghost::Type::CLYDE);
    pinky.charSprite.setPosition(224, 200);
    const float ANIMATION_FRAME_DURATION = 0.1f;

    sf::Clock clock;
    sf::Time elapsed;
    float elapsedTime = 0;
    
    text.setString(to_string(pellet.score));

    vector<bool> direction(4);
    float animation_timer = 0.0f;
    int current_frame = 0;
    const int TOTAL_FRAMES = 8;
    gameMap.displayMap(window, pacman.charSprite, pacman.dupe, blinky.charSprite, pellet.pelletMap, pellet.charSprite, text);
    window.display();

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
        
        for (auto event = sf::Event(); window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        //wait for start music to finish
        while (playlist.intro.getStatus()==sf::Music::Playing) {
            sf::sleep(sf::milliseconds(100));
            playlist.waka.play();
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
        pellet.score += pellet.addScore(pacman.charSprite.getPosition().x, pacman.charSprite.getPosition().y);
        text.setString(to_string(pellet.score));


        if(blinky.state == Ghost::State::SCATTER){
            blinky.move(gameMap, blinky.gTC(gameMap, 16, 64),deltaTime);
            blinky.timer -= deltaTime;
            if((blinky.charSprite.getPosition().x == 16 && blinky.charSprite.getPosition().y == 64) || blinky.timer <= 0){
                blinky.timer = 20;
                blinky.state = Ghost::State::NORMAL;
                playlist.waka.stop();
                playlist.siren.play();
            }
            //just copy same code for rest like pinky.move(gameMap, blinky.gTC(gameMap, 432, 64),deltaTime);
        }else if(blinky.state == Ghost::State::NORMAL){
            blinky.move(gameMap, blinky.gTC(gameMap, pacman.charSprite.getPosition().x, pacman.charSprite.getPosition().y),deltaTime);
            blinky.timer -= deltaTime;
            if(blinky.timer <= 0){
                blinky.timer = 10;
                blinky.state = Ghost::State::SCATTER;
                playlist.waka.play();
                playlist.siren.stop();
            }
        }
        direction = {false, false, false, false};
        window.clear();
        gameMap.displayMap(window, pacman.charSprite, pacman.dupe, blinky.charSprite, pellet.pelletMap, pellet.charSprite, text);
        window.display();
        if(blinky.charSprite.getGlobalBounds().intersects(pacman.charSprite.getGlobalBounds())){
            playlist.siren.stop();
            playlist.waka.stop();
            playlist.death.play();
            while (playlist.death.getStatus() == sf::Sound::Playing) {
                sf::sleep(sf::milliseconds(10));
            }
            sf::sleep(sf::milliseconds(100));
            break; 
        }
    }
}