#include "Ghost.hpp"
Ghost::Ghost(sf::Texture &texture, Type type) { // Use member initializer list
    charSprite.setTexture(texture);
    charSprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
    speed = 99;
}
double Ghost::align(double x) {
    return round(x / 16.0) * 16.0;
}
void followPath(double x, double y){
    //moves in current direction
    //if encounters a wall, find the new direction (cannot go in opposite direction)
}
