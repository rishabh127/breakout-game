/**
*   ball.h
*/

#ifndef BALL_H
#define BALL_H

#include "entity.h"


class Ball : public Entity
{

    Vector<float> *dir;		// direction
    float radius;			// ball radius
    float speed;			// paddle x speed

  public:

    Ball(float radius, Color *c);

    ~Ball();

    void setDir(Vector<float> *dir);
    void setDir(float x, float y);
    Vector<float> *getDir();

    void setRadius(float radius);
    float getRadius();

    void setSpeed(float speed);
    void incSpeed(float inc);
    float getSpeed();

    bool collide(Entity *e);

};


#endif
