/**
*   paddle.cpp
*/

#include "paddle.h"


Paddle::Paddle(float w, float h, Color *c) {
    this->w = w;
    this->h = h;
    this->color = c;
    pos = new Vector<float>();
    this->speed = 0.0;
}

Paddle::~Paddle() {
    delete this->color;
    delete this->pos;
}

void Paddle::setW(float w) {
    this->w = w;
}

float Paddle::getW() {
    return this->w;
}

void Paddle::setH(float h) {
    this->h = h;
}

float Paddle::getH() {
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

void Paddle::setSpeed(float speed) {
	this->speed = speed;
}

void Paddle::incSpeed(float inc) {
	this->speed += inc;
}

float Paddle::getSpeed() {
	return this->speed;
}

