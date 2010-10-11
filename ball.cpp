/**
 *   ball.cpp
 */

#include "ball.h"

Ball::Ball(float radius, Color *c) :
	Entity(radius, radius, c) {
	this->dir = new Vector<float> ();
	this->radius = radius;
	this->speed = 0.0;
}

Ball::~Ball() {
	delete this->dir;
}

void Ball::setDir(Vector<float> *dir) {
	this->dir = dir;
}

void Ball::setDir(float x, float y) {
	this->dir->set(x, y);
}

Vector<float> *Ball::getDir() {
	return this->dir;
}

void Ball::setRadius(float radius) {
	this->radius = radius;
}

float Ball::getRadius() {
	return this->radius;
}

void Ball::setSpeed(float speed) {
	this->speed = speed;
}

void Ball::incSpeed(float inc) {
	this->speed += inc;
}

float Ball::getSpeed() {
	return this->speed;
}

/*bool Ball::collide(Entity *e) {
	float eX = e->getPos()->getX();
	float eY = e->getPos()->getY();
	float eW = e->getW();
	float eH = e->getH();

	// horizontal collision
	float xDiff = this->getPos()->getX() - eX;
	if (xDiff > 0) { // ball is right
		if (xDiff > radius + this->getW()) {
			return false;
		}
	} else { // ball is left
		if (xDiff > radius) {
			return false;
		}
	}

	float yDiff = this->getPos()->getY() - eY;
	if (yDiff > 0) { // ball is upper
		if (yDiff > radius + this->getH()) {
			return false;
		}
	} else { // ball is down
		if (yDiff > radius) {
			return false;
		}
	}

	// vertical collision
	return true;
}

*/
