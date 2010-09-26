/**
*   brick.h
*/

#ifndef BRICK_H
#define BRICK_H

#include "vector.h"
#include "color.h"


class Brick
{
    int life;           // in hits
    int w;              // width, in pixels
    int h;              // height, in pixels
    Vector<int> *pos;   // position
    Color *color;       // RGB color
    
  public:
    
    Brick(int life, int w, int h, Color *c);

    void setLife(int life);
    int getLife();
    void setW(int w);
    int getW();
    void setH(int h);
    int getH();
    void setPos(Vector<int> *pos);
    void setPos(int x, int y);
    Vector<int> *getPos();
    void setColor(Color *c);
    Color *getColor();

};


#endif
