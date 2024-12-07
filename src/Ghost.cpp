
#include "Ghost.hpp"
Ghost::Ghost(sf::Texture &texture, Type type) { // Use member initializer list
    charSprite.setTexture(texture);
    charSprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
    speed = 99;
}
double Ghost::align(double x) {
    return round(x / 16.0) * 16.0;
}
bool Ghost::empty(int x, int y, GameMap gameMap){
    x /= 16; y /= 16;
    return gameMap.mapData[y][x] == ' ';
}
void Ghost::followPath(GameMap gameMap, double x, double px, double y, double py, double deltaTime){
    if(dir == Direction::STILL){
        if(empty(x, y - 16, gameMap) && py < y){
            dir = Direction::UP;
        }else if(empty(x - 16, y, gameMap) && px < x){
            dir = Direction::LEFT;
        }else if(empty(x, y + 16, gameMap) && py > y){
            dir = Direction::DOWN;
        }else if(empty(x + 16, y, gameMap) && px > x){
            dir = Direction::RIGHT;
        }
    }
    if(dir == Direction::UP){
        if(empty((int)x,(int)y - speed * deltaTime, gameMap)){
            charSprite.setPosition(x, y - speed * deltaTime);
        }else{
            charSprite.setPosition(x, (int)y/16 * 16);
            dir = Direction::STILL;
        }
    }else if(dir == Direction::LEFT){
        if(empty((int)x - speed * deltaTime,(int)y, gameMap)){
            charSprite.setPosition(x - speed * deltaTime, y);
        }else{
            charSprite.setPosition((int)x/16 * 16, y);
            dir = Direction::STILL;
        }
    }else if(dir == Direction::DOWN){
        if(empty((int)x,(int)y + 16 + speed * deltaTime, gameMap)){
            charSprite.setPosition(x, y + speed * deltaTime);
        }else{
            charSprite.setPosition(x, align(y));
            dir = Direction::STILL;
        }
    }else if(dir == Direction::RIGHT){
        if(empty((int)x + 16 + speed * deltaTime,(int)y, gameMap)){
            charSprite.setPosition(x + speed * deltaTime, y);
        }else{
            charSprite.setPosition(align(x), y);
            dir = Direction::STILL;
        }
    }
}
