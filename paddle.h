/**
*   paddle.h
*/

#ifndef PADDLE_H
#define PADDLE_H

#include "entity.h"


class Paddle : public Entity
{

	float speed;			// paddle x speed

  public:
    
     Paddle(float w, float h, Color *c);
    ~Paddle();

    void setSpeed(float speed);
    void incSpeed(float inc);
    float getSpeed();

};


#endif
