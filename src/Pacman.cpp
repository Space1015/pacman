#include "Pacman.hpp"
Pacman::Pacman(){
    charTexture.loadFromFile("Resources/pacman.png");
    charSprite.setTexture(charTexture);
    charSprite.setPosition(0,32*4);
    States dir = States::STILL;
}
