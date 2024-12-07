#include "Pellet.hpp"

using namespace std;

Pellet::Pellet(int x, int y, PelletType type)
    : position(x, y), type(type), isEaten(false) {}

pair<int, int> Pellet::getPosition() const
{
    return position;
}

PelletType Pellet::getType() const
{
    return type;
}

bool Pellet::getIsEaten() const
{
    return isEaten;
}

void Pellet::setPosition(int x, int y)
{
    position = {x, y};
}

void Pellet::setType(PelletType newType)
{
    type = newType;
}


void Pellet::eat()
{
    isEaten = true;
}
