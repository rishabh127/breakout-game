/**
*   ball.h
*/

#ifndef BALL_H
#define BALL_H

#include "vector.h"
#include "color.h"


class Ball
{

    Vector<float> *pos;		// position
    Vector<float> *dir		// direction
    Color *color;       	// RGB color
    int radius;				// ball readius
    float speed;			// paddle x speed

  public:

    Ball();
    Ball(int radius, Color *c);
    ~Ball();



};


#endif
