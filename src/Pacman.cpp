#include "Pacman.hpp"
#include "GameMap.hpp"
Pacman::Pacman() : dir(States::STILL) { // Use member initializer list
    charTexture.loadFromFile("Resources/pacman.png");
    if (!charTexture.loadFromFile("Resources/pacman.png")) {
        return;
    }
    charSprite.setTexture(charTexture);
    dupe.setTexture(charTexture);
    charSprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
    dupe.setTextureRect(sf::IntRect(0, 0, 16, 16));
    charSprite.setPosition(216, 320);
}
double Pacman::posx(){
    return charSprite.getPosition().x;
}
double Pacman::posy(){
    return charSprite.getPosition().y;
}
char Pacman::empty(int x, int y, GameMap gameMap){
    x /= 16; y /= 16;
    return gameMap.mapData[y][x] == ' ';
}
double Pacman::mod(double x){
    return (int)x % 16 + x - (int) x;
}
double Pacman::align(double x) {
    return round(x / 16.0) * 16.0;
}
void Pacman::move(GameMap gameMap, double deltaTime, int speed, int current_frame){
    sf::IntRect pacmanTextureRect(current_frame * 16, 0, 16, 16);
    charSprite.setTextureRect(pacmanTextureRect);
    if (dir == Pacman::States::UP) {
        if (empty((int)posx(), (int)(posy() - deltaTime * speed), gameMap)) {
            charSprite.setPosition(align(posx()), posy() - deltaTime * speed);
        } else {
            charSprite.setPosition(align(posx()), (int)posy() / 16 * 16);
            dir = Pacman::States::STILL;
        }
    } else if (dir == Pacman::States::LEFT) {
        if (posx() - deltaTime * speed < 0) {
            charSprite.move(28 * 16, 0);
        }
        if (posx() > 27 * 16) {
            charSprite.move(-deltaTime * speed, 0);
            dupe.setPosition(posx() - 28 * 16, 17 * 16);
        } else if (empty((int)(posx() - deltaTime * speed), (int)posy(), gameMap)) {
            charSprite.setPosition(posx() - deltaTime * speed, align(posy()));
        } else {
            charSprite.setPosition((int)posx() / 16 * 16, align(posy()));
            dir = Pacman::States::STILL;
        }
    } else if (dir == Pacman::States::DOWN) {
        if (empty((int)posx(), (int)(posy() + 16 + deltaTime * speed), gameMap)) {
            charSprite.setPosition(align(posx()), posy() + deltaTime * speed);
        } else {
            charSprite.setPosition(align(posx()), align(posy()));
            dir = Pacman::States::STILL;
        }
    } else if (dir == Pacman::States::RIGHT) {
        if (posx() + deltaTime * speed > 27 * 16) {
            charSprite.move(-28 * 16, 0);
        }
        if (posx() < 0) {
            charSprite.move(deltaTime * speed, 0);
            dupe.setPosition(posx() + 28 * 16, 17 * 16);
        } else if (empty((int)(posx() + 16 + deltaTime * speed), (int)posy(), gameMap)) {
            charSprite.setPosition(posx() + deltaTime * speed, align(posy()));
        } else {
            charSprite.setPosition(align(posx()), align(posy()));
            dir = Pacman::States::STILL;
        }
    }
}

