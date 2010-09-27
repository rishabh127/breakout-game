/**
*   paddle.h
*/

#ifndef PADDLE_H
#define PADDLE_H

#include "vector.h"
#include "color.h"


class Paddle
{
    float w;              	// width, in pixels
    float h;              	// height, in pixels
    Vector<float> *pos;		// position
    Color *color;       	// RGB color
    float speed;			// paddle x speed

  public:
    
    Paddle(float w, float h, Color *c);
    ~Paddle();

    void setW(float w);
    float getW();
    void setH(float h);
    float getH();
    void setPos(Vector<float> *pos);
    void setPos(float x, float y);
    Vector<float> *getPos();
    void setColor(Color *c);
    Color *getColor();
    void setSpeed(float speed);
    void incSpeed(float inc);
    float getSpeed();
};


#endif
