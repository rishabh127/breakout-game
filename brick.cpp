/**
*   brick.cpp
*/

#include "brick.h"


Brick::Brick(int life, int w, int h, Color *c) {
    this->life = life;
    this->w = w;
    this->h = h;
    this->color = c;
    pos = new Vector<int>();
}

void Brick::setLife(int life) {
    this->life = life;
}

int Brick::getLife() {
    return this->life;
}

void Brick::setW(int w) {
    this->w = w;
}

int Brick::getW() {
    return this->w;
}

void Brick::setH(int h) {
    this->h = h;
}

int Brick::getH() {
    return this->h;
}

void Brick::setPos(Vector<int> *pos) {
    this->pos = pos;
}

void Brick::setPos(int x, int y) {
    this->pos->set(x, y);
}

Vector<int> *Brick::getPos() {
    return this->pos;
}

void Brick::setColor(Color *color) {
    this->color = color;
}

Color *Brick::getColor() {
    return this->color;
}

