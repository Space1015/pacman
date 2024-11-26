#include "Pacman.hpp"
Pacman::Pacman() : dir(States::STILL) { // Use member initializer list
    charTexture.loadFromFile("Resources/pacman.png");
    if (!charTexture.loadFromFile("Resources/pacman.png")) {
        return;
    }
    charSprite.setTexture(charTexture);
    charSprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
    charSprite.setPosition(216, 320);
}

