#include "Global.hpp"

bool empty(int x, int y, GameMap gameMap){
    x /= 16; y /= 16;
    return gameMap.mapData[y][x] == ' ';
}
bool empty(int x, int y, GameMap gameMap){
    return gameMap.mapData[y][x] == ' ';
}
double mod(double x){
    return fmod(x, 16.0);
}
double align(double x) {
    return round(x / 16.0) * 16.0;
}