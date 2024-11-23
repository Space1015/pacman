#include "Pacman.hpp"
Pacman::Pacman(){
    charTexture.loadFromFile("Resources/pacman.png");
    charSprite.setTexture(charTexture);
    charSprite.setPosition(32*13+16,32*19+16);
    States dir = States::STILL;
}
