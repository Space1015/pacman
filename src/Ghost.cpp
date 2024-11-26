#include "Ghost.hpp"
Ghost::Ghost(sf::Texture &texture) : dir(States::STILL) { // Use member initializer list
    charSprite.setTexture(texture);
    charSprite.setPosition(216, 320);
}