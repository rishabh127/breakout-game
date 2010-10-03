/**
*   brick.cpp
*/

#include "brick.h"


Brick::Brick(int life, int w, int h, Color *c) : Entity(w, h, c) {
    this->life = life;
}

void Brick::setLife(int life) {
    this->life = life;
}

int Brick::getLife() {
    return this->life;
}
