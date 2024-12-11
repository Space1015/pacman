#include "SFX.hpp"

using namespace std;

SFX::SFX () {
    waka.openFromFile("Resources/sfx/waka.wav");
    intro.openFromFile("Resources/sfx/intro.wav");
    end.openFromFile("Resources/sfx/end.wav");
    siren.openFromFile("Resources/sfx/siren.wav");
    fruit.openFromFile("Resources/sfx/fruit.wav");
    ghostscared.openFromFile("Resources/sfx/ghostscared.wav");
    ghost2base.openFromFile("Resources/sfx/ghost2base.wav");
    death.openFromFile("Resources/sfx/death.wav");
    eatghost.openFromFile("Resources/sfx/eatghost.wav");
}