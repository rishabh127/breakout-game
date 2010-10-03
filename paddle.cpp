/**
*   paddle.cpp
*/

#include "paddle.h"


Paddle::Paddle(float w, float h, Color *c) : Entity(w, h, c) {
    this->speed = 0.0;
}

Paddle::~Paddle() {
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

