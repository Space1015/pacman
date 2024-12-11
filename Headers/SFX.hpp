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
    sf::Music waka;
    sf::Music siren;
    sf::Music fruit;
    sf::Music ghostscared;
    sf::Music ghost2base;
    sf::Music death;
    sf::Music eatghost;
};