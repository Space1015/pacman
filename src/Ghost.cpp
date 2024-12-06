#include <Ghost.hpp>
Ghost::Ghost(sf::Texture &texture, Type type) { // Use member initializer list
    charSprite.setTexture(texture);
    charSprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
    speed = 50;
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
void Ghost::followPath(GameMap gameMap, double x, double y, float deltaTime, float &elapsedTime){
    //moves in current direction
    //if encounters a wall, find the new direction (cannot go in opposite direction)

    elapsedTime += deltaTime;
    switchDir(gameMap, x, y, elapsedTime);
    //note: basic game down but still need to add the power up pellet with the ghost animation sequence where pacman can be eaten
    // although basic game isn't down until the eating dots code evelyn writes
    if (dir == Ghost::Direction::UP) {
        charSprite.setPosition(align(posx()), posy() - deltaTime * speed);
    } else if (dir == Ghost::Direction::LEFT) {
        charSprite.setPosition(align(posx() + deltaTime * speed), posy());
    } else if (dir == Ghost::Direction::RIGHT) {
        charSprite.setPosition(posx() + deltaTime * speed, align(posy()));
    } else if (dir == Ghost::Direction::DOWN) {
        charSprite.setPosition(align(posx()), posy() + deltaTime * speed);
    }
}
/**
 *  @param GameMap gameMap
 *  @return void 
 *  randomly choose a direction, move in that direction
 */
void Ghost::randomMove(GameMap gameMap) {
    // bool foundViableDir = false;
    // while (!foundViableDir) {
    //     int random = rand() % 4;
    //     if (random == 0 && empty((int)posx()+8, (int)posy() - 16  - (mod(posy()) == 0 ? 1: 0), gameMap) && abs(align(posx()) - posx()) < 2) {
    //         dir = Direction::UP;
    //         foundViableDir = true;
    //     } else if (random == 1 && empty((int)posx()+8, (int)posy() + 16  + (mod(posy()) == 0 ? 1: 0), gameMap) && abs(align(posx()) - posx()) < 2) {
    //         dir = Direction::DOWN;
    //         foundViableDir = true;
    //     } else if (random == 2 && empty((int)posx() - 16  - (mod(posx()) == 0 ? 1: 0), (int)posy()+8, gameMap) && abs(align(posy()) - posy()) < 2) {
    //         dir = Direction::LEFT;
    //         foundViableDir = true;
    //     } else if (random == 3 && empty((int)posx() + 16 +(mod(posx()) == 0 ? 1: 0), (int)posy()+8, gameMap) && abs(align(posy()) - posy()) < 2) {
    //         dir = Direction::RIGHT;
    //         foundViableDir = true;
    //     }
    // }
    if (empty((int)posx()+8, (int)posy() - 16  - (mod(posy()) == 0 ? 1: 0), gameMap) && abs(align(posx()) - posx()) < 2) {
        dir = Direction::UP;
    } else if (empty((int)posx()+8, (int)posy() + 16  + (mod(posy()) == 0 ? 1: 0), gameMap) && abs(align(posx()) - posx()) < 2) {
        dir = Direction::DOWN;
    } else if (empty((int)posx() - 16  - (mod(posx()) == 0 ? 1: 0), (int)posy()+8, gameMap) && abs(align(posy()) - posy()) < 2) {
        dir = Direction::LEFT;
    } else if (empty((int)posx() + 16 +(mod(posx()) == 0 ? 1: 0), (int)posy()+8, gameMap) && abs(align(posy()) - posy()) < 2) {
        dir = Direction::RIGHT;
    }
}
void Ghost::switchDir(GameMap gameMap, double x, double y, float elapsedTime) {
    bool deadEnd = true;
    if (dir == Direction::UP || dir == Direction::DOWN) {
        if (posx() >= x ) {
            if (empty((int)posx() - 16  - (mod(posx()) == 0 ? 1: 0), (int)posy()+8, gameMap) && abs(align(posy()) - posy()) < 2) {
                dir = Direction::LEFT;
                deadEnd = false;
            }
        } else if (posx() < x) {
            if (empty((int)posx() + 16 +(mod(posx()) == 0 ? 1: 0), (int)posy()+8, gameMap) && abs(align(posy()) - posy()) < 2) {
                dir = Direction::RIGHT;
                deadEnd = false;
            }
        }
    } else if (dir == Direction::LEFT || dir == Direction::RIGHT) {
        if (posy() <= y) {
            if (empty((int)posx()+8, (int)posy() - 16  - (mod(posy()) == 0 ? 1: 0), gameMap) && abs(align(posx()) - posx()) < 2) {
                dir = Direction::UP;
                deadEnd = false;
            }
        } else if (posy() > y) {
            if (empty((int)posx()+8, (int)posy() + 16  + (mod(posy()) == 0 ? 1: 0), gameMap) && abs(align(posx()) - posx()) < 2) {
                dir = Direction::DOWN;
                deadEnd = false;
            }
        }
    } else {
        if (dir == Ghost::Direction::UP) {
            if (empty((int)posx()+8, (int)posy() - 16  - (mod(posy()) == 0 ? 1: 0), gameMap) && abs(align(posx()) - posx()) < 2) {
                deadEnd = false;
            }
        } else if (dir == Ghost::Direction::LEFT) {
            if (empty((int)posx() - 16  - (mod(posx()) == 0 ? 1: 0), (int)posy()+8, gameMap) && abs(align(posy()) - posy()) < 2) {
                deadEnd = false;
            }
        } else if (dir == Ghost::Direction::RIGHT) {
            if (empty((int)posx() + 16 +(mod(posx()) == 0 ? 1: 0), (int)posy()+8, gameMap) && abs(align(posy()) - posy()) < 2) {
                deadEnd = false;
            }
        } else if (dir == Ghost::Direction::DOWN) {
            if (empty((int)posx()+8, (int)posy() + 16  + (mod(posy()) == 0 ? 1: 0), gameMap) && abs(align(posx()) - posx()) < 2) {
                deadEnd = false;
            }
        }
    }
    if (deadEnd) {
        randomMove(gameMap);
    }
}