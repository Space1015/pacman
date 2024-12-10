#include "SFX.hpp"

using namespace std;

SFX::SFX () {
    waka.loadFromFile("Resources/sfx/waka.wav");
    intro.openFromFile("Resources/sfx/intro.wav");
    end.openFromFile("Resources/sfx/end.wav");
    siren.loadFromFile("Resources/sfx/siren.wav");
    fruit.loadFromFile("Resources/sfx/fruit.wav");
    ghostscared.loadFromFile("Resources/sfx/ghostscared.wav");
    ghost2base.loadFromFile("Resources/sfx/ghost2base.wav");
    death.loadFromFile("Resources/sfx/death.wav");
    eatghost.loadFromFile("Resources/sfx/eatghost.wav");
}