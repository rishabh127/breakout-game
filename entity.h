/*
 * entity.h
 *
 *  Created on: Oct 2, 2010
 *      Author: lucmir
 */

#ifndef ENTITY_H
#define ENTITY_H

#include "vector.h"
#include "color.h"


class Entity
{
    Vector<float> *pos;		// position
    Color *color;       	// RGB color
    float w;				// width, in pixels
    float h;				// height, in pixels

  public:

    Entity(float w, float h, Color *c);

    ~Entity();

    void setPos(float x, float y);
    void setPos(Vector<float> *pos);
	Vector<float> *getPos();

	void setColor(Color *c);
	Color *getColor();

	void setW(float w);
	float getW();

	void setH(float h);
	float getH();

	bool collide(Entity *e);

};


#endif
