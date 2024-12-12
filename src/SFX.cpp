#include "SFX.hpp"

using namespace std;

SFX::SFX () {
    waka.loadFromFile("Resources/sfx/waka.wav");
    intro.openFromFile("Resources/sfx/intro.wav");
    end.openFromFile("Resources/sfx/end.wav");
    siren1.loadFromFile("Resources/sfx/siren1.wav");
    siren2.loadFromFile("Resources/sfx/siren2.wav");
    fruit.loadFromFile("Resources/sfx/fruit.wav");
    ghostscared.loadFromFile("Resources/sfx/ghostscared.wav");
    ghost2base.loadFromFile("Resources/sfx/ghost2base.wav");
    death.openFromFile("Resources/sfx/death.wav");
    eatghost.loadFromFile("Resources/sfx/eatghost.wav");
}