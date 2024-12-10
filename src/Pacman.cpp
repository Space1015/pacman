#include "Pacman.hpp"
#include "GameMap.hpp"
Pacman::Pacman() : dir(States::STILL) { // Use member initializer list
    speed = 88;
    charTexture.loadFromFile("Resources/pacman.png");
    if (!charTexture.loadFromFile("Resources/pacman.png")) {
        return;
    }
    charSprite.setTexture(charTexture);
    dupe.setTexture(charTexture);
    charSprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
    dupe.setTextureRect(sf::IntRect(0, 0, 16, 16));
    charSprite.setPosition(216, 320);
    dupe.setPosition(-100,-100);
}
double Pacman::posx(){
    return charSprite.getPosition().x;
}
double Pacman::posy(){
    return charSprite.getPosition().y;
}
bool Pacman::empty(int x, int y, GameMap gameMap){
    x /= 16; y /= 16;
    return gameMap.mapData[y][x] == ' ';
}
double Pacman::mod(double x){
    return (int)x % 16 + x - (int) x;
}
double Pacman::align(double x) {
    return round(x / 16.0) * 16.0;
}
int Pacman::move(GameMap gameMap, double deltaTime, int current_frame, vector<bool> direction){
    if(direction[0]){
        if(empty((int)posx() + 8,(int)posy() - (mod(posy()) == 0 ? 1: 0), gameMap) && abs(align(posx()) - posx()) < 2){
            dir = Pacman::States::UP;
        }
    }else if(direction[1]){
        if((int)posx() == 0){
            dir = Pacman::States::LEFT;
        }else if(empty((int)posx() - (mod(posx()) == 0 ? 1: 0),(int)posy() + 8, gameMap) && abs(align(posy()) - posy()) < 2){
            dir = Pacman::States::LEFT;
        }
    }else if(direction[2]){
        if(empty((int)posx() + 8,(int)posy() + 16 + (mod(posy()) == 0 ? 1: 0), gameMap) && abs(align(posx()) - posx()) < 2){
            dir = Pacman::States::DOWN;
        }
    }else if(direction[3]){
        if(posx() - 27 * 16 > 0){
            dir = Pacman::States::RIGHT;
        }else if(empty((int)posx() + 16 + (mod(posx()) == 0 ? 1: 0),(int)posy() + 8, gameMap) && abs(align(posy()) - posy()) < 2){
            dir = Pacman::States::RIGHT;
        }
    }
    
    if (dir == Pacman::States::UP) {
        if(current_frame != 3) current_frame = 2;
        if (empty((int)posx(), (int)(posy() - deltaTime * speed), gameMap)) {
            charSprite.setPosition(align(posx()), posy() - deltaTime * speed);
        } else {
            charSprite.setPosition(align(posx()), (int)posy() / 16 * 16);
            dir = Pacman::States::STILL;
        }
    } else if (dir == Pacman::States::LEFT) {
        if(current_frame != 1) current_frame = 0;
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
        if(current_frame != 7)current_frame = 6;
        if (empty((int)posx(), (int)(posy() + 16 + deltaTime * speed), gameMap)) {
            charSprite.setPosition(align(posx()), posy() + deltaTime * speed);
        } else {
            charSprite.setPosition(align(posx()), align(posy()));
            dir = Pacman::States::STILL;
        }
    } else if (dir == Pacman::States::RIGHT) {
        if(current_frame != 5) current_frame = 4;
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
    sf::IntRect pacmanTextureRect(current_frame * 16, 0, 16, 16);
    charSprite.setTextureRect(pacmanTextureRect);
    dupe.setTextureRect(pacmanTextureRect);
    return current_frame;
}

