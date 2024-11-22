#include "Pacman.hpp"
Pacman::Pacman(){
    charTexture.loadFromFile("Resources/pacman.png");
    charSprite.setTexture(charTexture);
    charSprite.setPosition(300,300);
    enum class States{STILL, UP, DOWN, LEFT, RIGHT};
}
