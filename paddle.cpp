/**
*   paddle.cpp
*/

#include "paddle.h"


Paddle::Paddle(int w, int h, Color *c) {
    this->w = w;
    this->h = h;
    this->color = c;
    pos = new Vector<float>();
}

Paddle::~Paddle() {
    delete this->color;
    delete this->pos;
}

void Paddle::setW(int w) {
    this->w = w;
}

int Paddle::getW() {
    return this->w;
}

void Paddle::setH(int h) {
    this->h = h;
}

int Paddle::getH() {
    return this->h;
}

void Paddle::setPos(Vector<float> *pos) {
    this->pos = pos;
}

void Paddle::setPos(float x, float y) {
    this->pos->set(x, y);
}

Vector<float> *Paddle::getPos() {
    return this->pos;
}

void Paddle::setColor(Color *color) {
    this->color = color;
}

Color *Paddle::getColor() {
    return this->color;
}

