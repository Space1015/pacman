#include "Pacman.hpp"
Pacman::Pacman() : dir(States::STILL) { // Use member initializer list
    charTexture.loadFromFile("Resources/pacman.png");
    charSprite.setTexture(charTexture);
    charSprite.setPosition(216, 320);
}

