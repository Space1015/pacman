#pragma once

#include <SFML/Audio.hpp>

using namespace std;

class SFX 
{
    enum class State{
        START,
        END,
        IN_PROGRESS
    };
    public:
        SFX();
    sf::Music intro;
    sf::Music end;
    sf::SoundBuffer waka;
    sf::SoundBuffer siren1;
    sf::SoundBuffer siren2;
    sf::SoundBuffer fruit;
    sf::SoundBuffer ghostscared;
    sf::SoundBuffer ghost2base;
    sf::Music death;
    sf::SoundBuffer eatghost;
};