/**
*   paddle.h
*/

#ifndef PADDLE_H
#define PADDLE_H

#include "vector.h"
#include "color.h"


class Paddle
{
    int w;              // width, in pixels
    int h;              // height, in pixels
    Vector<float> *pos; // position
    Color *color;       // RGB color
    //TODO xspeed

  public:
    
    Paddle(int w, int h, Color *c);
    ~Paddle();

    void setW(int w);
    int getW();
    void setH(int h);
    int getH();
    void setPos(Vector<float> *pos);
    void setPos(float x, float y);
    Vector<float> *getPos();
    void setColor(Color *c);
    Color *getColor();
};


#endif
