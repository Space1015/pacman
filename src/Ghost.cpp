#include <Ghost.hpp>
Ghost::Ghost(sf::Texture &texture, Type type) { // Use member initializer list
    charSprite.setTexture(texture);
    charSprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
    speed = 99;
}
double Ghost::posx(){
    return charSprite.getPosition().x;
}
double Ghost::posy(){
    return charSprite.getPosition().y;
}
char Ghost::empty(int x, int y, GameMap gameMap){
    x /= 16; y /= 16;
    return gameMap.mapData[y][x] == ' ';
}
double Ghost::mod(double x){
    return (int)x % 16 + x - (int) x;
}
double Ghost::align(double x) {
    return round(x / 16.0) * 16.0;
}
void Ghost::followPath(GameMap gameMap, double x, double y, float deltaTime){
    //moves in current direction
    //if encounters a wall, find the new direction (cannot go in opposite direction)
    bool deadEnd = true;
    if (dir == Direction::UP || dir == Direction::DOWN) {
        if (posx() > x) {
            if (empty((int)posx() - 16, (int)posy(), gameMap)) {
                dir = Direction::LEFT;
                deadEnd = false;
            }
        } else if (posx() > x) {
            if (empty((int)posx() + 16, (int)posy(), gameMap)) {
                dir = Direction::RIGHT;
                deadEnd = false;
            }
        }
    } else {
        if (posy() > y) {
            if (empty((int)posx(), (int)posy() - 16, gameMap)) {
                dir = Direction::UP;
                deadEnd = false;
            }
        } else if (posy() < y) {
            if (empty((int)posx(), (int)posy() + 16, gameMap)) {
                dir = Direction::DOWN;
                deadEnd = false;
            }
        }
    }
    if (deadEnd) {
        randomMove(gameMap);
    }
    //note: basic game down but still need to add the power up pellet with the ghost animation sequence where pacman can be eaten
    // although basic game isn't down until the eating dots code evelyn writes
    if (dir == Ghost::Direction::UP) {
        charSprite.setPosition(align(posx()), posy() - deltaTime * speed);
    } else if (dir == Ghost::Direction::LEFT) {
        charSprite.setPosition(align(posx()), posy() + deltaTime * speed);
    } else if (dir == Ghost::Direction::RIGHT) {
        charSprite.setPosition(posx() + deltaTime * speed, align(posy()));
    } else if (dir == Ghost::Direction::DOWN) {
        charSprite.setPosition(align(posx()), posy() + deltaTime * speed);
    }
}
void Ghost::randomMove(GameMap gameMap) {
    //randomly choose a direction
    //move in that direction
    bool foundViableDir = false;
    while (!foundViableDir) {
        int random = rand() % 4;
        if (random == 0 && empty((int)posx(), (int)posy() - 16, gameMap)) {
            dir = Direction::UP;
            foundViableDir = true;
        } else if (random == 1 && empty((int)posx(), (int)posy() + 16, gameMap)) {
            dir = Direction::DOWN;
            foundViableDir = true;
        } else if (random == 2 && empty((int)posx() - 16, (int)posy(), gameMap)) {
            dir = Direction::LEFT;
            foundViableDir = true;
        } else if (random == 3 && empty((int)posx() + 16, (int)posy(), gameMap)) {
            dir = Direction::RIGHT;
            foundViableDir = true;
        }
    }
}