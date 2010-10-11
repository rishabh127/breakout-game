/**
*   brick.cpp
*/

#include "brick.h"


Brick::Brick(int life, float w, float h, Color *c) : Entity(w, h, c) {
    this->life = life;
}

void Brick::setLife(int life) {
    this->life = life;
}

int Brick::getLife() {
    return this->life;
}

void Brick::decLife() {
	this->life--;
}
