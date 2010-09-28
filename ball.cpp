/**
*   ball.cpp
*/

#include "ball.h"

Ball::Ball(int radius, Color *c) {
    this->color = c;
    this->pos = new Vector<float>();
    this->dir = new Vector<float>();
    this->radius = radius;
    this->speed = 0.0;
}

Ball::~Ball() {
	delete this->pos;
	delete this->dir;
    delete this->color;
}
