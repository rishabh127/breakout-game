/*
 * entity.cpp
 *
 *  Created on: Oct 2, 2010
 *      Author: lucmir
 */

#include "entity.h"


Entity::Entity(float w, float h, Color *c) {
	this->w = w;
	this->h = h;
    this->color = c;
    this->pos = new Vector<float>();
}

Entity::~Entity() {
	delete this->pos;
    delete this->color;
}

void Entity::setPos(Vector<float> *pos) {
    this->pos = pos;
}

void Entity::setPos(float x, float y) {
    this->pos->set(x, y);
}

Vector<float> *Entity::getPos() {
    return this->pos;
}

void Entity::setColor(Color *color) {
    this->color = color;
}

Color *Entity::getColor() {
    return this->color;
}

void Entity::setW(float w) {
	this->w = w;
}

float Entity::getW() {
	return this->w;
}

void Entity::setH(float h) {
	this->h = h;
}

float Entity::getH() {
	return this->h;
}

bool Entity::collide(Entity *e) {

	bool collide = false;

	if ( ( (pos->getY() - h <= e->pos->getY() + e->h)
			&& (pos->getY() + h >= e->pos->getY()) )
			|| ( (pos->getY() + h >= e->pos->getY()) && (pos->getY() - h <= e->pos->getY() + e->h) )  ) {
		float maxH = pos->getX() + w;
		float minH = pos->getX() - w;
		if ( (maxH >= e->getPos()->getX()) && (maxH <= e->getPos()->getX() + e->getW()) ) {
			collide = true;
		} else if ( (minH >= e->getPos()->getX()) && (minH <= e->getPos()->getX() + e->getW()) ) {
			collide = true;
		}
	}

	return collide;
}
